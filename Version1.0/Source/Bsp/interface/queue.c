#include <string.h>
#include "queue.h"

static void data_mv_next(DataTypedef *pdata, uint8_t **p)
{
	if(*p < pdata->end)
		(*p)++;
	else
		*p = pdata->begin;
}

void data_push(DataTypedef *pdata, uint8_t dr)
{
	if(pdata->back == 0)
		pdata->front = pdata->back = pdata->begin;
	else
	{
		data_mv_next(pdata, &pdata->back);
		if(pdata->back == pdata->front)
			data_mv_next(pdata, &pdata->front);
	}
	*pdata->back = dr;
}

static int16_t data_read(DataTypedef *pdata, uint8_t *data, uint16_t len)
{
	int16_t i, bytes = 0;
	if(pdata->length(pdata) >= len)
	{
		for(i=0; i<len; i++)
		{
			data[bytes++] = *pdata->front;
			if(pdata->front == pdata->back)
			{
				pdata->front = 0;
				pdata->back = 0;
				break;
			}
			else
			{
				data_mv_next(pdata, &pdata->front);
			}			
		}
	}
	return bytes;
}

static void data_comeback(DataTypedef *pdata, uint8_t cnt)
{
	if(pdata->length(pdata) < cnt)
		pdata->clear(pdata);
	else
	{
		uint16_t num = pdata->back - pdata->begin + 1;
		if(num >= cnt)
			memset(pdata->back-num+1, 0x00, num);
		else
		{
			memset(pdata->begin, 0x00, num);
			num = cnt - num;
			memset(pdata->end-num+1, 0x00, num);
		}
	}
}

static uint16_t data_length(DataTypedef *pdata)
{
	uint16_t len;
	if(pdata->front == 0)
		len = 0;
	else if(pdata->back >= pdata->front)
		len = pdata->back - pdata->front + 1;
	else
		len = pdata->end - pdata->begin - (pdata->front - pdata->back) + 2;
	return len;
}

static void data_clear(DataTypedef *pdata)
{
	uint16_t num = pdata->end - pdata->begin + 1;
	memset(pdata->begin, 0x00, num);
	pdata->front = 0;
	pdata->back = 0;
}

void data_init(DataTypedef *pdata, uint8_t *data, uint16_t size)
{
	pdata->begin = data;
	pdata->end = data + size - 1;
	pdata->front = 0;
	pdata->back = 0;
	pdata->begin[size - 1] = '\0';
	
	pdata->push = data_push;
	pdata->read = data_read;
	pdata->clear = data_clear;
	pdata->comeback = data_comeback;
	pdata->length = data_length;
}
