#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct DataTypedef DataTypedef;
struct DataTypedef
{
	uint8_t* 	front;
	uint8_t* 	back;
	uint8_t* 	begin;
	uint8_t* 	end;
	void (*push)(DataTypedef*, uint8_t);
	int16_t (*read)(DataTypedef*,uint8_t*, uint16_t);
	void (*clear)(DataTypedef*);
	void (*comeback)(DataTypedef*, uint8_t);
	uint16_t (*length)(DataTypedef*);
};

void data_init(DataTypedef *pdata, uint8_t *buffer, uint16_t size);
void data_push(DataTypedef *pdata, uint8_t dr);
bool data_end_with(DataTypedef *pdata, char *str);
#endif
