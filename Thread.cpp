/*
 * Thread.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: root
 */


#include "Thread.h"
#include "EventMonitor.h"
#include <event2/event.h>

using namespace Easy;

Thread::Thread(void)
	: start_loop_(NULL),//
	  loop_ptr_(NULL),//
	  tid_(0), //
	  thread_index_(-1)
{

}

Thread::~Thread(void)
{

}

void* Thread::threadCallback(void *arg)
{
	Thread* thread = (Thread*)arg;

	thread->runStartLoop();

	return NULL;
}

int Thread::threadIndex(int index/* = -1*/)
{
	if (index >= 0)
	{
		this->thread_index_ = index;
	}

	return this->thread_index_;
}

int Thread::start(void)
{
	if (pthread_create(&this->tid_, NULL, threadCallback, (void*)this) != 0)
	{
		return -1;
	}

	return 0;
}

int Thread::wait(void)
{
	return pthread_join(this->tid_, NULL);
}

int Thread::runStartLoop(void)
{
	if (this->start_loop_ == NULL)
	{
		return -1;
	}

	if (this->loop_ptr_ == NULL)
	{
		return -1;
	}

	return this->start_loop_(this->loop_ptr_);
}

EventBaseThread::EventBaseThread(void)
	: base_(NULL),//
	  close_sec_(0)
{
	this->loop_ptr_ = this;
	this->start_loop_ = EventBaseThread::startSignalLoop;
}

EventBaseThread::~EventBaseThread(void)
{
	for (SignalEventSet::iterator iter = this->sig_set_.begin();//
			iter != this->sig_set_.end(); ++iter)
	{
		event_del(*iter);
	}

	if (this->base_ != NULL)
	{
		event_base_free(this->base_);
		this->base_ = NULL;
	}
}

event_base *EventBaseThread::eventBase(void)
{
	if (this->base_ == NULL)
	{
		this->base_ = event_base_new();
	}

	return this->base_;
}

void EventBaseThread::closeSec(int sec)
{
	this->close_sec_ = sec;
}

int EventBaseThread::signalCallBack(int sig)
{
	timeval *pTm = NULL;
	if (this->close_sec_ > 0)
	{
		timeval tm;
		tm.tv_sec = this->close_sec_;
		tm.tv_usec = 0;
		pTm = &tm;
	}

	return event_base_loopexit(this->base_, pTm);
}

void EventBaseThread::registeSignal(int sig)
{
	event* ev = evsignal_new(this->eventBase(), sig, eventCallback, (void* )this);
	if (!ev || event_add(ev, NULL) < 0)
	{
		event_del(ev);
		printf("error add sig = %d \n", sig);
	}
	this->sig_set_.insert(ev);
}

int EventBaseThread::startSignalLoop(void)
{
	return event_base_dispatch(this->eventBase());
}

void EventBaseThread::eventCallback(int fd, short which, void *arg)
{
	EventBaseThread* thread = (EventBaseThread*)arg;

	thread->signalCallBack(fd);

}

int EventBaseThread::startSignalLoop(void *arg)
{
	EventBaseThread* thread = (EventBaseThread*)arg;
	return thread->startSignalLoop();
}
