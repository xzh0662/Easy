/*
 * TcpServer.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#include <event2/event.h>
#include <event2/listener.h>
#include "TcpServer.h"
#include "Connection.h"

using namespace Easy;


TcpServer::TcpServer(void)
	: listener_(NULL)
{
	this->conn_map_.clear();
}

TcpServer::~TcpServer(void)
{

}

void TcpServer::listenerCallback(struct evconnlistener *listener, //
		int fd, //
		struct sockaddr *sa, //
		int socklen, //
		void *data)
{
	TcpServer *server = (TcpServer*)data;
	server->handleListener(fd);
}

int TcpServer::stop(void)
{
	if (this->listener_ != NULL)
	{
		evconnlistener_free(this->listener_);
		this->listener_ = NULL;
	}

	return 0;
}

int TcpServer::listen(const InetAddr& addr)
{
	unsigned flags = LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE;
	this->listener_ = evconnlistener_new_bind(this->eventBase(), //
			listenerCallback, //
			(void*) this, //
			flags, //
			-1, //
			(struct sockaddr *) &addr.addr_, //
			sizeof(addr.addr_));

	if (this->listener_ == NULL)
	{
		return -1;
	}

	return 0;
}

int TcpServer::send(int fd, Buffer *buffer)
{
	Connection* conn = this->findConnection(fd);
	if (conn == NULL)
	{
		return -1;
	}

	return conn->send(buffer);
}

int TcpServer::receive(int fd, Buffer *buffer)
{
	Connection* conn = this->findConnection(fd);
	if (conn == NULL)
	{
		return -1;
	}

	return 0;
}

void TcpServer::handleClosed(int fd)
{
	this->conn_map_.erase(fd);
}

int TcpServer::handleListener(int fd)
{//event_base 线程调用
	Connection *conn = new Connection();
	conn->init(fd, this);

	this->conn_map_[fd] = conn;

	return 0;
}

Connection* TcpServer::findConnection(int fd)
{
	ConnMap::iterator iter = this->conn_map_.find(fd);
	if (iter == this->conn_map_.end())
	{
		return NULL;
	}

	return iter->second;
}
