/*
 * TcpClient.h
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "EventMonitor.h"
#include "InetAddr.h"

namespace Easy
{

class Buffer;
class Connection;

class TcpClient : public EventMonitor
{
public:
	TcpClient(void);

	virtual ~TcpClient();

	virtual int stop(void);

	virtual int connect(const InetAddr& serverAddr);
	virtual int send(int fd, Buffer *buffer);
	virtual int receive(int fd, Buffer *buffer);
	virtual void handleClosed(int fd);
	virtual void handleConnected(void);

private:
	Connection *conn_;
};

}

#endif /* TCPCLIENT_H_ */
