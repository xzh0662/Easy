/*
 * EventMonitor.cpp
 *
 *  Created on: Aug 10, 2015
 *      Author: root
 */
#include "EventMonitor.h"
#include "Buffer.h"

using namespace Easy;

EventMonitor::EventMonitor(void)
	: event_base_(NULL)
{

}
EventMonitor::~EventMonitor(void)
{

}

void EventMonitor::handleRead(int fd, Buffer *buffer)
{
	this->receive(fd, buffer);
}

int EventMonitor::send(int fd, Buffer *buffer)
{
	this->sendMessage(fd, buffer);
	return 0;
}

event_base* EventMonitor::eventBase(void)
{
	return this->event_base_;
}

void EventMonitor::eventBase(event_base* base)
{
	this->event_base_ = base;
}
