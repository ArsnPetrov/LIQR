//#pragma once
//#include <rtl-sdr.h>
//#include <pthread.h>
//#include <memory.h>
//
//class Receiver
//{
//	pthread_t thread;
//
//public:
//	unsigned char* buffer;
//	int buffer_length;
//
//	rtlsdr_dev_t* device;
//
//	Receiver(rtlsdr_dev_t *device, int buf_len);
//
//	void _update(unsigned char* buf, uint32_t len);
//	void listen();
//
//	int get_buf_size();
//
//	void add_inheritor();
//};
//
