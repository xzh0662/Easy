/*
 * Connection.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */
#include <stdio.h>//printf
#include <event2/event.h>
#include <event2/bufferevent.h>

#include "Connection.h"
#include "EventMonitor.h"
#include "Buffer.h"

using namespace Easy;

Connection::Connection(void)
	  : bevent_(NULL),//
		owner_(NULL),//
		fd_(-1)
{
}

Connection::~Connection(void)
{
	printf("~Connection\n");
}

int Connection::init(int fd, //
		EventMonitor *owner, bool isClient/* = false*/)
{
	if (this->bevent_ != NULL || owner == NULL)
	{
		return -1;
	}

	int options = BEV_OPT_CLOSE_ON_FREE;
	int newFd = isClient ? -1 : fd;
	this->bevent_ = bufferevent_socket_new(owner->eventBase(), newFd, options);
	if (!this->bevent_)
	{
		printf("Error constructing bufferevent!\n");

		return -1;
	}
	else
	{
		bufferevent_setcb(this->bevent_, readCallback, NULL, eventCallback, (void*) this);
		bufferevent_enable(this->bevent_, EV_READ);

		this->owner_ = owner;
		this->fd_ = fd;
	}

	return 0;
}

bufferevent* Connection::bevent(void)
{
	return this->bevent_;
}

void Connection::handleConnected(void)
{
	printf("connection connected\n");
	this->owner_->handleConnected(this->fd_);
}

void Connection::handleRead(void)
{
	if (this->bevent_ == NULL)
	{
		return;
	}

	Buffer *buffer = new Buffer();
	int ret = bufferevent_read_buffer(this->bevent_, buffer->evb_);
	if (ret != 0)
	{
		return;
	}

	this->owner_->receive(this->fd_, buffer);
	delete buffer;
}

void Connection::handleClosed(void)
{
	printf("connection close\n");

	this->owner_->handleClosed(this->fd_);

	//这将自动close套接字和free读写缓冲区
	bufferevent_free(this->bevent_);
}

int Connection::send(const Buffer *buf)
{
	if (this->bevent_ == NULL)
	{
		return -1;
	}

	return bufferevent_write_buffer(this->bevent_, buf->evb_);
}

int Connection::fd(void)
{
	return this->fd_;
}

void Connection::readCallback(bufferevent *bev, void *data)
{
	Connection *conn = (Connection*)data;
	conn->handleRead();
}

void Connection::writeCallback(bufferevent *bev, void *data)
{
	//暂时没有处理
}

void Connection::eventCallback(bufferevent *bev, short events, void *data)
{
	Connection *conn = (Connection*)data;

//	if (events & BEV_EVENT_EOF)
//	{
//		conn->handleClosed();
//	}
	if(events & BEV_EVENT_CONNECTED)
	{
		conn->handleConnected();
		return;
	}
//	else if (events & BEV_EVENT_ERROR)
//	{
//		printf("some other error\n");
//	}

	printf("eventCallback events %d", events);

	conn->handleClosed();
}



