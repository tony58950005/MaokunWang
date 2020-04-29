#ifndef QUEUE_H_
#define QUEUE_H__

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
class Queue {
public:
	Queue(){};
	bool IsBuffer_Full();
	bool IsBuffer_Empty();
	void Buffer_Write(Queue item);
	void Buffer_Read();
private:
	size_t head=0;
	size_t tail=0;
	const size_t max_size_;
	bool full_ =0;//a flag to judge if buffer is full or not. if fill, full_=1;


};
#endif
#endif
