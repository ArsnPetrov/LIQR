#include "Receiver.h"

void rtlsdr_callback(unsigned char* buf, uint32_t len, void* ctx)
{
	((Receiver*)ctx)->_update(buf, len);
}

static void* ReceiverUpdate(void* arg)
{
	rtlsdr_read_async(((Receiver*)arg)->device, rtlsdr_callback, arg, 0, ((Receiver*)arg)->get_buf_size());

	return 0;
}

Receiver::Receiver(rtlsdr_dev_t *dev, int buf_len)
{
	device = dev;
	buffer_length = buf_len;
	buffer = new unsigned char[buf_len];
}

int Receiver::get_buf_size()
{
	return buffer_length;
}

void Receiver::listen()
{
	pthread_create(&thread, 0, ReceiverUpdate, this);
}

void Receiver::_update(unsigned char* buf, uint32_t len)
{
	memcpy(buffer, buf, len);
}