#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Print.h"
#include "Random.h"
#include "PLL.h"

struct Character1{
	int character;
	int arr[1];
};
struct Character2{
	int character;
	int arr[2];
};
struct Character3{
	int character;
	int arr[3];
};
struct Character4{
	int character;
	int arr[4];
};
typedef struct Character1 Alphabet1;
typedef struct Character2 Alphabet2;
typedef struct Character3 Alphabet3;
typedef struct Character4 Alphabet4;

Alphabet1 Letter1[2]={
	{0x45,{4}},
	{0x54,{8}}
};
Alphabet2 Letter2[4]={
	{0x41,{4,8}},
	{0x49,{4,4}},
	{0x4E,{8,4}},
	{0x4D,{8,8}}
	
};
Alphabet3 Letter3[8]={
	{0x44,{8,4,4}},
	{0x4B,{8,4,8}},
	{0x4F,{8,8,8}},
	{0x52,{4,8,4}},
	{0x53,{4,4,4}},
	{0x55,{4,4,8}},
	{0x57,{4,8,8}},
	{0x47,{8,8,4}}
};
Alphabet4 Letter4[12]={
	{0x42,{8,4,4,4}},
	{0x43,{8,4,8,4}},
	{0x46,{4,4,8,4}},
	{0x48,{4,4,4,4}},
	{0x4A,{4,8,8,8}},
	{0x4C,{4,8,4,4}},
	{0x50,{4,8,8,4}},
	{0x51,{8,8,4,8}},
	{0x56,{4,4,4,8}},
	{0x58,{8,4,4,8}},
	{0x59,{8,4,8,8}},
	{0x5A,{8,8,4,4}}
};

void Switches_Init()
{
	SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | 0x10;
	volatile int nop;
	 nop++;
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_DIR_R &= 0x00;
	
}

void Ligths_Init()
{
	SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | 0x02;
	volatile int nop;
	 nop++;
	GPIO_PORTB_DEN_R |= 0x0F;
	GPIO_PORTB_DIR_R |= 0x0F;
}

int statusPORTE()
{
	
	int status = GPIO_PORTE_DATA_R;
	return status;
	
}

int MorsetoLetter()
{
	int track[]={0,0,0,0};
	int index = 0;
	int current = statusPORTE();
	while(current != 1)
	{
		if(current != 0)
		{
			track[index] = current;
			index++;
		}
		int current = statusPORTE();
		
	}
	if(index==1){}
	
}


int main(){
}
