/*
 * TcpServer.h
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "InetAddr.h"
#include <map>
#include "EventMonitor.h"

struct evconnlistener;

namespace Easy
{

class Buffer;
class Connection;

class TcpServer : public EventMonitor
{
	typedef std::map<int, Connection*> ConnMap;
public:
	TcpServer(void);

	virtual ~TcpServer(void);

	virtual int stop(void);

	virtual int listen(const InetAddr& addr);
	virtual int send(int fd, Buffer *buffer);
	virtual int receive(int fd, Buffer *buffer);
	virtual void handleClosed(int fd);

	virtual int handleListener(int fd);

	static void listenerCallback(struct evconnlistener *listener, //
			int fd, //
			struct sockaddr *sa, //
			int socklen, //
			void *data);

protected:
	Connection* findConnection(int fd);

private:
	struct evconnlistener *listener_;

	ConnMap conn_map_;
};


}



#endif /* TCPSERVER_H_ */
