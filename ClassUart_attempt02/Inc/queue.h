#ifndef QUEUE_H_
#define QUEUE_H__

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define QUEUE_MAX_SIZE	(256)

#ifdef __cplusplus
class Queue {
public:
	Queue();
	bool IsBuffer_Full();
	bool IsBuffer_Empty();
	bool Buffer_Write(uint8_t item);
	bool Buffer_Read(uint8_t* item);


private:
	uint8_t head=0;
	uint8_t tail=0;
	bool full = false; //a flag to judge if buffer is full or not. if fill, full_=1;
	uint8_t* buffer[QUEUE_MAX_SIZE]; //Store the queue in this array
	uint8_t size();

};
#endif
#endif
