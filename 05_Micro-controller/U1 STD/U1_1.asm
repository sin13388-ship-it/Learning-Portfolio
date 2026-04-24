; PROGRAM : U1_1_1.ASM            		By Steven                    
; FUNCTION: LED SCANNING DEMO PROGRAM   2017.0407      		  
#INCLUDE    HT66F2390.INC 
;=================================================================================
MY_DATA    .SECTION			'DATA'      ;== DATA SECTION == 
DEL1    DB       ?                  	;DELAY LOOP COUNT 1 
DEL2    DB       ?                  	;DELAY LOOP COUNT 2 
DEL3	DB   	 ?        				;DELAY LOOP COUNT 3 
;========================================================================================
LED_PORT  	EQU    PF        			;DEFINE LED_PORT 
LED_PORTC  	EQU    PFC        			;DEFINE LED_PORT CONTROL REG.  
MY_CODE    .SECTION	 at 0	'CODE'     	;== PROGRAM SECTION, 重置向量(RESET VECTOR)                 	
MAIN: 
		MOV		A,10101111B				;關閉WDT
		MOV		WDTC,A
		CLR		LED_PORTC          		;規劃PORT為輸出屬性 
		SET		LED_PORT           		;設置PORT輸出 11111111B
		CLR		C                  		;清除C旗標(STATUS.0) 
RIGHT:             
		RRC		LED_PORT        		;PORT右旋 
		MOV 	A,100        			;延遲100*1mS 
		CALL	DELAY               	
		SZ  	LED_PORT.0          	;是否PORT之LSB=0? 
		JMP		RIGHT               	;否. 繼續右旋. 
LEFT:   
		RLC     LED_PORT    			;PORT左旋 
		MOV		A,200         			;延遲 200*1mS 
		CALL	DELAY               	
		SZ		LED_PORT.7          	;是否PORT之MSB=0?? 
		JMP		LEFT                	;否. 繼續左旋. 
		JMP		RIGHT               	;重新開始右旋. 
;========================================================================================
; PROC	: DELAY
; FUNC	: DEALY ABOUT ACC*1mS @fSYS=8MHz  (1998xACC)+2 Cycles!
; PARA	: ACC : DELAY FACTOR
; REG	: DEL1,DEL2,DEL3
;======================================================================================== 
DELAY  	PROC
		MOV		DEL1,A					;SET DEL1 COUNTER	
DEL_1:  MOV		A,3		        	                   	
        MOV		DEL2,A					;SET DEL2 COUNTER 
DEL_2:	MOV		A,220
		MOV		DEL3,A					;SET DEL3 COUNTER
DEL_3:  SDZ		DEL3                  	;DEL3 DOWN COUNT
        JMP		DEL_3                      
        SDZ		DEL2                  	;DEL2 DOWN COUNT
        JMP		DEL_2                   
		SDZ		DEL1					;DEL1 DOWN COUNT
		JMP		DEL_1
        RET
DELAY	ENDP