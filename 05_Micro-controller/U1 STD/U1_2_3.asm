;PROGRAM : U1_2_3.ASM 								2017.0413
;FUNCTION: 7 SEGMENT LED DEMO PROGRAM(LMOV/ITABRDL) By Steven   
#INCLUDE  HT66F2390.INC 
;========================================================================================
MY_DATA    .SECTION  'DATA'         	;== DATA SECTION == 
DEL1      	DB  	?       			;DELAY LOOP COUNT 1 
DEL2      	DB   	?       			;DELAY LOOP COUNT 2 
DEL3	    DB  	?       			;DELAY LOOP COUNT 3 
RAMBANK 2  	MY_DATA1					;指定MY_DATA1為RAM Section 2
MY_DATA1    .SECTION  'DATA'         	;== DATA SECTION == 
COUNT   	DB  	? 
;========================================================================================
SEG_PORT 	EQU  	PG   				;DEFINE 7-SEGMENT LED PORT 
SEG_PORTC  	EQU    	PGC     			;DEFINE SEG_PORT CONTROL REG. 
MY_CODE  .SECTION  AT 0  'CODE'     	;== PROGRAM SECTION , 重置向量(RESET VECTOR) 
		MOV		A,0ABh					;關閉WDT
		MOV		WDTC,A
		CLR    	SEG_PORT				;設置輸出Low
		CLR    	SEG_PORTC      			;規劃PORT為輸出屬性
MAIN:         
		MOV    	A,LOW  (TAB_7_SEG-1) 
		MOV  	TBLP,A    				;取得建表起始位址(Low-byte)  
		MOV    	A,10 
		LMOV   	COUNT,A      			;設定迴圈次數 
LOOP: 
		ITABRDL	SEG_PORT     			;取得建表資料，並將Low-byte送至SEG_PORT 
		MOV  	A,TBLH   				;取得High-byte資料 
		CALL    DELAY    				;延遲ACC*10ms 
		LSDZ    COUNT      				;(COUNT=COUNT-1)是否為0?
		JMP  	LOOP    				;否，迴圈繼續 
		JMP  	MAIN    				;是，重新執行
;========================================================================================
; PROC	: DELAY
; FUNC	: DEALY ABOUT ACC*10mS @fSYS=8MHz
; PARA	: ACC : DELAY FACTOR
; REG	: DEL1,DEL2,DEL3
;======================================================================================== 
DELAY	PROC
		MOV		DEL1,A					;SET DEL1 COUNTER	
DEL_1:  MOV		A,30		        	                   	
		MOV		DEL2,A					;SET DEL2 COUNTER 
DEL_2:	MOV		A,220
		MOV		DEL3,A					;SET DEL3 COUNTER
DEL_3:	SDZ		DEL3                  	;DEL3 DOWN COUNT
		JMP		DEL_3                      
		SDZ		DEL2                  	;DEL2 DOWN COUNT
		JMP		DEL_2                   
		SDZ		DEL1					;DEL1 DOWN COUNT
		JMP		DEL_1
		RET
DELAY	ENDP
ROMBANK 7  		TABLE					;指定為ROM BANK 7
TABLE  .SECTION 	'CODE'     			;== PROGRAM SECTION
		ORG   	01F00h 					;Last Page
TAB_7_SEG: 
		DC      (20 SHL 8)+03Fh  		;共陰極七段顯示器(0~9)顯示碼建表區
		DC    	(30 SHL 8)+006h  		;High-byte為延遲時間常數
		DC    	(40 SHL 8)+05Bh  		;Low-byte為七段顯示器顯示碼
		DC     	(50 SHL 8)+04Fh  		
		DC     	(60 SHL 8)+066h 
		DC    	(70 SHL 8)+06Dh 
		DC     	(80 SHL 8)+07Dh
		DC     	(90 SHL 8)+007h 
		DC     	(100 SHL 8)+07Fh 
		DC     	(110 SHL 8)+067h 
		END 