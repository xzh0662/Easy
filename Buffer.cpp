/*
 * Buffer.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#include "Buffer.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

using namespace Easy;

Buffer::Buffer(int endian/* = little_endian*/)
	: evb_(NULL),
	  endian_(endian)
{

	this->evb_ = evbuffer_new();

}

Buffer::~Buffer(void)
{
	//printf("Buffer::~Buffer\n");
	if (this->evb_ != NULL)
	{
		evbuffer_free(this->evb_);
	}
}

size_t Buffer::Length(void) const
{//返回evbuffer存储的字节数

	if (this->evb_ == NULL)
	{
		return 0;
	}

	return evbuffer_get_length(this->evb_);
}

Buffer & Buffer::operator <<(const char c)
{
	this->addData((void*)&c, sizeof(char));

	return *this;
}

Buffer & Buffer::operator <<(const unsigned char c)
{
	this->addData((void*)&c, sizeof(unsigned char));

	return *this;
}

Buffer & Buffer::operator <<(const bool val)
{
	this->addData((void*)&val, sizeof(bool));

	return *this;
}

Buffer & Buffer::operator <<(const int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(int); i++)
		{
			this->addData((void*)(&val + sizeof(int) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->addData((void*)&val, sizeof(int));
	}
	return *this;
}

Buffer & Buffer::operator <<(const long int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(long int); i++)
		{
			this->addData((void*)(&val + sizeof(long int) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->addData((void*)&val, sizeof(long int));
	}
	return *this;
}

Buffer & Buffer::operator <<(const long long int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(long long int); i++)
		{
			this->addData((void*)(&val + sizeof(long long int) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->addData((void*)&val, sizeof(long long int));
	}
	return *this;
}

Buffer & Buffer::operator <<(const unsigned int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(unsigned int); i++)
		{
			this->addData((void*)(&val + sizeof(unsigned int) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->addData((void*)&val, sizeof(unsigned int));
	}
	return *this;
}

Buffer & Buffer::operator <<(const char *cstr)
{
	short length = strlen(cstr);

	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			this->addData((void*)(&length + sizeof(short) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->addData((void*) &length, sizeof(short));
	}

	this->addData((void*)cstr, length + 1);

	return *this;
}

Buffer & Buffer::operator <<(const std::string &ss)
{
	short length = ss.length();

	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			this->addData((void*)(&length + sizeof(short) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->addData((void*) &length, sizeof(short));
	}

	this->addData((void*)ss.c_str(), length);

	return *this;
}

Buffer & Buffer::operator <<(const short &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			this->addData((void*)(&val + sizeof(short) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->addData((void*) &val, sizeof(short));
	}

	return *this;
}

Buffer & Buffer::operator <<(const unsigned short &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(unsigned short); i++)
		{
			this->addData((void*)(&val + sizeof(unsigned short) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->addData((void*) &val, sizeof(unsigned short));
	}

	return *this;
}

Buffer & Buffer::operator <<(const double &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(double); i++)
		{
			this->addData((void*)(&val + sizeof(double) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->addData((void*) &val, sizeof(double));
	}

	return *this;
}

Buffer & Buffer::operator >>(char &c)
{
	this->removeData((void*)&c, sizeof(char));

	return *this;
}

Buffer & Buffer::operator >>(unsigned char &c)
{
	this->removeData((void*)&c, sizeof(unsigned char));

	return *this;
}

Buffer & Buffer::operator >>(bool &val)
{
	this->removeData((void*)&val, sizeof(bool));

	return *this;
}

Buffer & Buffer::operator >>(int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(int); i++)
		{
			this->removeData((void*)(&val + sizeof(int) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*)&val, sizeof(int));
	}

	return *this;
}

Buffer & Buffer::operator >>(long int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(int); i++)
		{
			this->removeData((void*)(&val + sizeof(long int) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*)&val, sizeof(long int));
	}

	return *this;
}

Buffer & Buffer::operator >>(long long int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(int); i++)
		{
			this->removeData((void*)(&val + sizeof(long long int) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*)&val, sizeof(long long int));
	}

	return *this;
}

Buffer & Buffer::operator >>(unsigned int &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(unsigned int); i++)
		{
			this->removeData((void*)(&val + sizeof(unsigned int) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*)&val, sizeof(unsigned int));
	}

	return *this;
}

Buffer & Buffer::operator >>(char *&cstr)
{
	short length = 0;

	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			this->removeData((void*)(&length + sizeof(short) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->removeData((void*) &length, sizeof(short));
	}

	if (length <= 0)
	{
		return *this;
	}

	this->removeData((void*) cstr, length + 1);

	return *this;
}

Buffer & Buffer::operator >>(std::string &ss)
{
	short length = 0;

	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			this->removeData((void*)(&length + sizeof(short) - i - 1),
					sizeof(char));
		}
	}
	else
	{
		this->removeData((void*) &length, sizeof(short));
	}

	if (length <= 0)
	{
		return *this;
	}

	ss.resize(length);
	this->removeData((void*) ss.c_str(), length);

	return *this;
}

Buffer & Buffer::operator >>(short &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			this->removeData((void*)(&val + sizeof(short) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*) &val, sizeof(short));
	}

	return *this;
}

Buffer & Buffer::operator >>(unsigned short &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(unsigned short); i++)
		{
			this->removeData((void*)(&val + sizeof(unsigned short) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*) &val, sizeof(unsigned short));
	}

	return *this;
}

Buffer & Buffer::operator >>(double &val)
{
	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(double); i++)
		{
			this->removeData((void*)(&val + sizeof(double) - i - 1), sizeof(char));
		}
	}
	else
	{
		this->removeData((void*) &val, sizeof(double));
	}

	return *this;
}

Buffer & Buffer::operator =(const Buffer &buffer)
{//clear this first

	evbuffer_drain(this->evb_, this->Length());

	size_t len = buffer.Length();
	void *data_copy = malloc(len);

	if (data_copy)
	{
		evbuffer_copyout(buffer.evb_, data_copy, len);
		this->addData(data_copy, len);
		free(data_copy);
	}

	return *this;
}

void Buffer::addBeginInt(const int &val)
{
	if (this->evb_ == NULL)
	{
		return;
	}

	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(int); i++)
		{
			evbuffer_prepend(this->evb_, (void*) (&val + sizeof(int) - i - 1), sizeof(char));
		}
	}
	else
	{
		evbuffer_prepend(this->evb_, (void*) &val, sizeof(int));
	}
}

void Buffer::addBeginShort(const short &val)
{
	if (this->evb_ == NULL)
	{
		return;
	}

	if (this->endian_ == big_endian)
	{
		for (size_t i = 0; i < sizeof(short); i++)
		{
			evbuffer_prepend(this->evb_, (void*) (&val + sizeof(short) - i - 1), sizeof(char));
		}
	}
	else
	{
		evbuffer_prepend(this->evb_, (void*) &val, sizeof(short));
	}
}

int Buffer::expand(const int size)
{//预留空间
	return evbuffer_expand(this->evb_, size);
}

int Buffer::move(Buffer *srcBuffer)
{
	return evbuffer_add_buffer(this->evb_, srcBuffer->evb_);
}

char* Buffer::readLine(size_t* outLen, int type/* = EVBUFFER_EOL_CRLF*/)
{ // must free return char*
	return evbuffer_readln(this->evb_, outLen, (evbuffer_eol_style)type);
}

int Buffer::deleteLineEnd(int type/* = EVBUFFER_EOL_CRLF*/)
{ // the end must in the first with this->evb_
	struct evbuffer_ptr it;
	size_t extra_drain;
	it = evbuffer_search_eol(this->evb_, NULL, &extra_drain, (evbuffer_eol_style)type);
	if (it.pos == 0)
	{
		evbuffer_drain(this->evb_, extra_drain);
		return 0;
	}
	return it.pos;
}

int Buffer::addData(const void *data, size_t len)
{
	if (this->evb_ == NULL)
	{
		return -1;
	}

	return evbuffer_add(this->evb_, data, len);
}

int Buffer::removeData(void *data, size_t len)
{
	if (this->evb_ == NULL)
	{
		return -1;
	}
	return evbuffer_remove(this->evb_, data, len);
}

evbuffer * Buffer::evb(void)
{
	return this->evb_;
}

