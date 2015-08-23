/*
 * Buffer.h
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <event2/buffer.h>
#include <string>

namespace Easy
{

#define BUFFER_NORMAL_SIZE 1024

enum Endian
{
	little_endian = 1,
	big_endian = 2
};

class Buffer
{//暂时不支持线程安全
	friend class Connection;
public:
	Buffer(int endian = little_endian);
	~Buffer(void);

	size_t Length(void) const;

	Buffer & operator <<(const char c);
	Buffer & operator <<(const unsigned char c);
	Buffer & operator <<(const bool val);
	Buffer & operator <<(const int &val);
	Buffer & operator <<(const long int &val);
	Buffer & operator <<(const long long int &val);
	Buffer & operator <<(const unsigned int &val);
	Buffer & operator <<(const char *cstr);
	Buffer & operator <<(const std::string &ss);
	Buffer & operator <<(const short &val);
	Buffer & operator <<(const unsigned short &val);
	Buffer & operator <<(const double &val);

	Buffer & operator >>(char &c);
	Buffer & operator >>(unsigned char &c);
	Buffer & operator >>(bool &val);
	Buffer & operator >>(int &val);
	Buffer & operator >>(long int &val);
	Buffer & operator >>(long long int &val);
	Buffer & operator >>(unsigned int &val);
	Buffer & operator >>(char *&cstr);
	Buffer & operator >>(std::string &ss);
	Buffer & operator >>(short &val);
	Buffer & operator >>(unsigned short &val);
	Buffer & operator >>(double &val);

	Buffer & operator =(const Buffer &buffer);

	void addBeginInt(const int &val);
	void addBeginShort(const short &val);

	int expand(const int size);
	int move(Buffer *srcBuffer);

	char* readLine(size_t* outLen, int type = EVBUFFER_EOL_CRLF);
	int deleteLineEnd(int type = EVBUFFER_EOL_CRLF);

	int addData(const void *data, size_t len);
	int removeData(void *data, size_t len);



	evbuffer * evb(void);

private:
	struct evbuffer *evb_;
	int endian_;
};

#define BUFFER_NEW_ACTION(BUFFER, SIZE, ACTION)	\
	do {	\
		BUFFER = new Easy::Buffer();	\
		if (BUFFER->expand(SIZE)){ACTION;}	\
	}while(0)	\

#define BUFFER_NEW(BUFFER, SIZE) \
	BUFFER_NEW_ACTION(BUFFER, SIZE, return)	\

#define BUFFER_NEW_RETURN(BUFFER, SIZE, RETURN) \
	BUFFER_NEW_ACTION(BUFFER, SIZE, return RETURN)	\

}

#endif /* BUFFER_H_ */
