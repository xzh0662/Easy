/*
 * TcpClient.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#include "TcpClient.h"
#include "Connection.h"

#include <stdio.h>
#include <event2/bufferevent.h>


using namespace Easy;

TcpClient::TcpClient(void)
	: conn_(NULL)
{

}

TcpClient::~TcpClient()
{
	this->stop();
}

int TcpClient::stop(void)
{
	if (this->conn_ != NULL)
	{
//		this->handleClosed()
		delete this->conn_;
		this->conn_ = NULL;
	}
	return 0;
}


int TcpClient::connect(const InetAddr& serverAddr)
{
	if (this->conn_ == NULL)
	{
		this->conn_ = new Connection();
		if (this->conn_->init(-1, this))
		{
			delete this->conn_;
			return -1;
		}
	}

	int ret = bufferevent_socket_connect(this->conn_->bevent(),//
			(struct sockaddr *)&serverAddr.addr_,//
			sizeof(serverAddr.addr_));

	return ret;
}

int TcpClient::receive(int fd, Buffer *buffer)
{
	return 0;
}

void TcpClient::handleClosed(int fd)
{
	delete this->conn_;
	this->conn_ = NULL;

	printf("TcpClient::handleClosed fd = %d\n", fd);
}

void TcpClient::handleConnected(void)
{
	printf("TcpClient::handleConnected\n");
}

int TcpClient::sendMessage(int fd, Buffer *buffer)
{
	if (this->conn_ == NULL)
	{
		return -1;
	}
	return this->conn_->send(buffer);
}
