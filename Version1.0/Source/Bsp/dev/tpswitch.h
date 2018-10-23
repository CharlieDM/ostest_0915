#ifndef __TPSWITCH_H
#define __TPSWITCH_H
#include "sys.h"

#define ADDITIONAL_TP_OFF	0x00
#define ADDITIONAL_TP1		0x01
#define ADDITIONAL_TP2		0x02
#define ADDITIONAL_TP3		0x04
#define ADDITIONAL_TP4		0x08
#define ADDITIONAL_TP5		0x10
#define ADDITIONAL_TP6		0x20
#define ADDITIONAL_TP7		0x40
#define ADDITIONAL_TP8		0x80

typedef enum
{
	TPA = 0,  
	TPB,
	ADDITIONAL_TP,
} TP_TYPE;


void switch_testpoint(TP_TYPE tp_type , uint16_t point)

#endif

