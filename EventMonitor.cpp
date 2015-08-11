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

event_base* EventMonitor::eventBase(void)
{
	return this->event_base_;
}

void EventMonitor::eventBase(event_base* base)
{
	this->event_base_ = base;
}
