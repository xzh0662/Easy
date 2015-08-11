/*
 * Connection.h
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_


struct bufferevent;

namespace Easy
{
class EventMonitor;
class Buffer;

class Connection
{

public:
	Connection(void);

	virtual ~Connection(void);

	virtual int init(int fd, //
			EventMonitor *owner, bool isClient = false);

	bufferevent* bevent(void);

	virtual void handleConnected(void);
	virtual void handleRead(void);
	virtual void handleClosed(void);

	virtual int send(const Buffer *buf);

	int fd(void);

	static void readCallback(bufferevent *bev, void *data);
	static void writeCallback(bufferevent *bev, void *data);
	static void eventCallback(bufferevent *bev, short events, void *data);

protected:

	bufferevent *bevent_;
	EventMonitor *owner_;
	int fd_;
};


}

#endif /* CONNECTION_H_ */
