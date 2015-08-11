/*
 * EventMonitor.h
 *
 *  Created on: Aug 10, 2015
 *      Author: root
 */

#ifndef EVENTMONITOR_H_
#define EVENTMONITOR_H_

struct event_base;

namespace Easy
{

class Buffer;

class EventMonitor
{
public:
	EventMonitor(void);
	virtual ~EventMonitor(void);

	virtual int send(int fd, Buffer *buffer) = 0;
	virtual int receive(int fd, Buffer *buffer) = 0;
	virtual void handleClosed(int fd) = 0;
	virtual void handleConnected(int fd){};

	event_base* eventBase(void);
	void eventBase(event_base* base);

private:
	event_base* event_base_;
};

}

#endif /* EVENTMONITOR_H_ */
