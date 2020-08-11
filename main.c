#include <iostream>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Print.h"
#include "PLL.h"

char inputString[30];

void ClearString()
{
	for(int i=0;i<30;i++)
	{
		inputString[i]=0;
	}
}

int StringLength()
{
	int count=0;
	for(int i=0;i<30;i++)
	{
		if(inputString[i]!=0)
		{
			count++;
		}
	}
	return count;
}
	
struct Character1{
	char letter;
	int character;
	int arr[1];
};
struct Character2{
	char letter;
	int character;
	int arr[2];
};
struct Character3{
	char letter;
	int character;
	int arr[3];
};
struct Character4{
	char letter;
	int character;
	int arr[4];
};
typedef struct Character1 Alphabet1;
typedef struct Character2 Alphabet2;
typedef struct Character3 Alphabet3;
typedef struct Character4 Alphabet4;

Alphabet1 Letter1[2]={
	{'E',0x45,{4}},
	{'T',0x54,{8}}
};
Alphabet2 Letter2[4]={
	{'A',0x41,{4,8}},
	{'I',0x49,{4,4}},
	{'N',0x4E,{8,4}},
	{'M',0x4D,{8,8}}
	
};
Alphabet3 Letter3[8]={
	{'D',0x44,{8,4,4}},
	{'K',0x4B,{8,4,8}},
	{'O',0x4F,{8,8,8}},
	{'R',0x52,{4,8,4}},
	{'S',0x53,{4,4,4}},
	{'U',0x55,{4,4,8}},
	{'W',0x57,{4,8,8}},
	{'G',0x47,{8,8,4}}
};
Alphabet4 Letter4[12]={
	{'B',0x42,{8,4,4,4}},
	{'C',0x43,{8,4,8,4}},
	{'F',0x46,{4,4,8,4}},
	{'H',0x48,{4,4,4,4}},
	{'J',0x4A,{4,8,8,8}},
	{'L',0x4C,{4,8,4,4}},
	{'P',0x50,{4,8,8,4}},
	{'Q',0x51,{8,8,4,8}},
	{'V',0x56,{4,4,4,8}},
	{'X',0x58,{8,4,4,8}},
	{'Y',0x59,{8,4,8,8}},
	{'Z',0x5A,{8,8,4,4}}
};

void Switches_Init()
{
	SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | 0x10;
	volatile int nop;
	 nop++;
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_DIR_R &= 0x00;
	
}

void Lights_Init()
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
	if(index==1)
	{
		for(int i=0;i<2;i++)
		{
			if(Letter1[i].arr[0]==track[0])
			{
				return Letter1[i].character;
				break;
				
			}
		}
	}
	if(index==2)
	{
		for(int i=0;i<4;i++)
		{
			if(Letter2[i].arr[0]==track[0])
			{
				if(Letter2[i].arr[1]==track[1])
				{
					return Letter2[i].character;
					break;
				}
			}
		}
	}
	if(index==3)
	{
		for(int i=0;i<8;i++)
		{
			if(Letter3[i].arr[0]==track[0])
			{
				if(Letter3[i].arr[1]==track[1])
				{
					if(Letter3[i].arr[2]==track[2])
					{
						return Letter3[i].character;
					  break;
					}
				}
			}
		}
	}
	if(index==4)
	{
		for(int i=0;i<12;i++)
		{
			if(Letter4[i].arr[0]==track[0])
			{
				if(Letter4[i].arr[1]==track[1])
				{
					if(Letter4[i].arr[2]==track[2])
					{
						if(Letter4[i].arr[3]==track[3])
						{
							return Letter4[i].character;
					    break;
						}
					}
				}
			}
		}
	}
	
}

void LettertoMorse(int number)
{
	
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(inputString[i]==Letter1[j].letter)
			{
				GPIO_PORTB_DATA_R = Letter1[j].arr[0];
				volatile int nop;
	      nop++;
				GPIO_PORTB_DATA_R=0;
			}
		}
		for(int j=0;j<4;j++)
		{
			if(inputString[i]==Letter2[j].letter)
			{
				GPIO_PORTB_DATA_R = Letter2[j].arr[0];
				volatile int nop;
	      nop++;
				GPIO_PORTB_DATA_R=0;
				GPIO_PORTB_DATA_R= Letter2[j].arr[1];
				volatile int bnop;
	      bnop++;
				GPIO_PORTB_DATA_R=0;
			}
		}
		for(int j=0;j<8;j++)
		{
			if(inputString[i]==Letter3[j].letter)
			{
				GPIO_PORTB_DATA_R = Letter3[j].arr[0];
				volatile int nop;
	      nop++;
				GPIO_PORTB_DATA_R=0;
				GPIO_PORTB_DATA_R= Letter3[j].arr[1];
				volatile int bnop;
	      bnop++;
				GPIO_PORTB_DATA_R=0;
				GPIO_PORTB_DATA_R= Letter3[j].arr[2];
				volatile int dbnop;
	      dbnop++;
				GPIO_PORTB_DATA_R=0;
			}
		}
		for(int j=0;j<12;j++)
		{
			if(inputString[i]==Letter4[j].letter)
			{
				GPIO_PORTB_DATA_R = Letter4[j].arr[0];
				volatile int nop;
	      nop++;
				GPIO_PORTB_DATA_R=0;
				GPIO_PORTB_DATA_R= Letter4[j].arr[1];
				volatile int bnop;
	      bnop++;
				GPIO_PORTB_DATA_R=0;
				GPIO_PORTB_DATA_R= Letter4[j].arr[2];
				volatile int dbnop;
	      dbnop++;
				GPIO_PORTB_DATA_R=0;
				GPIO_PORTB_DATA_R= Letter4[i].arr[3];
				volatile int gdbnop;
	      gdbnop++;
				GPIO_PORTB_DATA_R=0;
			}
		}
		
	}
	
}


int main()
{
	ClearString();
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(0x0000); 
	ST7735_SetCursor(0,0);
	Switches_Init();
	Lights_Init();
	int input;
	while(1)
	{
		printf("If you want Morse to Word input 0 or 1 if vice versa:\n");
		scanf("%d",&input);
		if(input==0)
		{
			int status=0;
			while(status!=1)
			{
				int letter = MorsetoLetter();
				LCD_OutDec(letter);
				status=statusPORTE();
				
			}
		}
		else
		{
			int status=0;
			while(status!=1)
				
			{
			
			  printf("Type what you want to covert to Morse:\n");
			  fgets(inputString, sizeof(inputString), stdin);
			  int length = StringLength();
			  LettertoMorse(length);
				status=statusPORTE();
			}
			
		}
		
	}
}
