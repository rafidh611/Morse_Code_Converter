Counter EQU 0	 
Divisor  EQU 0
	
    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    PRESERVE8
  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec


    PUSH {R4-R10,LR}
	SUB SP,#4
	MOV R5,#10
	MOV R7,#1
	MOV R3,#0
	ADD R2,R0,#0
	
loop
    ADD R3,R3,#1
	STR R3,[SP,#Counter]
	UDIV R1,R0,R7
	LDR R6,[SP,#Counter] ;binding variable keeps track of cycles
	CMP R1,#10
	BLO loop2
	MUL R7,R7,R5
	B loop

   
loop2
   CMP R6,#0
   BEQ Out
   UDIV R0,R0,R7
   ADD R0,R0,#0x30
   PUSH {R0,R5,R2,R7,R6,R1}
   BL ST7735_OutChar
   POP {R0,R5,R2,R7,R6,R1}
   SUB R0,R0,#0x30
   MUL R1,R0,R7
   SUB R0,R2,R1
   UDIV R7,R7,R5
   ADD R2,R0,#0
   SUB R6,R6,#1
   B loop2
   
Out

   
   
   
   ADD SP,#4
   POP {R4-R10,PC}
	
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
    PUSH {R4-R10,LR}
	SUB SP,#4
	MOV R5,#100 ;dont use again
	MOV R3,#0  ;dont use again
	MOV R1,#1000
    STR R5,[SP,#Divisor] ;binding keeps track of divisor (100,10,1)
	
	ADD R6,R0,#0
	UDIV R1,R0,R1
	CMP R1,#1
	BHS nonvalid
	
    UDIV R0,R0,R5
	ADD R0,R0,#0x30
	PUSH {R0,R1}
	BL ST7735_OutChar
	POP {R0,R1}
	SUB R0,R0,#0x30
	MUL R1,R0,R5
	SUB R0,R6,R1
	ADD R6,R0,#0
	LDR R5,[SP,#Divisor]
	MOV R2,#10
	UDIV R5,R5,R2
	STR R5,[SP,#Divisor]
	
	MOV R0,#0
	ADD R0,R0,#0x2E
	PUSH {R0,R5}
	BL ST7735_OutChar
	POP {R0,R5}
	ADD R0,R6,#0
	
	UDIV R0,R0,R5
	ADD R0,R0,#0x30
	PUSH {R0,R5}
	BL ST7735_OutChar
	POP {R0,R5}
	SUB R0,R0,#0x30
	MUL R1,R0,R5
	SUB R0,R6,R1
	
	PUSH {R0,R1}
	ADD R0,R0,#0x30
	BL ST7735_OutChar
	POP {R0,R1}
	B done
	

	
nonvalid
    MOV R0,#0
    ADD R0,R0,#0x2A
	BL ST7735_OutChar
	MOV R0,#0
	ADD R0,R0,#0x2E
	BL ST7735_OutChar
	MOV R0,#0
	ADD R0,R0,#0x2A
	BL ST7735_OutChar
	MOV R0,#0
	ADD R0,R0,#0x2A
	BL ST7735_OutChar
done	
	ADD SP,#4
	POP {R4-R10,LR}
	 
     BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
