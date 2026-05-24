# Micro-Controller 學習筆記
## Unit 2
## Unit 3
### U3_1
- 使用Time Base 中斷服務達成7段顯示器跑馬燈顯示
- 例如: 0123 > 1234 > 2345 >....以此類推
    - TB0 中斷: 負責刷新Scancode、7段顯示器的顯示碼
    - TB1 中斷: 負責調整delay時間
- 如何實作:
    1. include 需要的庫
    ```c
        #include <HT66F2390.h>
        #include "MyType.h"
    ```
    2. 需要的I/O腳位名稱意義化(define)
    ```c
        #define	 SEGPort	_pg
        #define  SEGPortC	_pgc
        #define	 ScanPort	_pe
        #define	 ScanPortC	_pec
    ```
    3. 定義7段顯示器的pattern
    ```c
        const u8 SEG_TAB[] = {	   				//七段顯示碼建表區(共陰)
				0x3F,0x06,0x5B,0x4F,0x66,
			   	0x6D,0x7D,0x07,0x7F,0x67};
    ```

    4. 共用變數宣告(留意最佳化 volatile)
    ```c
        volatile u8 *ptr,ScanCode,Buffer[4];
        //ptr -> 指向buffer 的陣列
        //ScanCode -> 提供給I/O腳的scan 腳 8bits
        //Buffer[] -> 4位數對應要顯示的數字，儲存7段顯示器的pattern 
    ```
    5. 設定Clock for ISR
        TB0 Clock =fsys/4;
        TB0 Counter=8192;
        TB1 Clock =fsub;
        TB1 cOUNTER =32767;
    ```c
    	//設定Timebase 
        _psc0r=0x01; //fsys/4
        _tb0c=0x85; //8192
        _psc1r=0x02; //fsub
        _tb1c=0x87; //32767	
    ```
    6. 初始化Buffer
    ```c
        u8 i,j;
	    for(i=0; i<4;i++) Buffer[i]=0;
    ```
    7. Enable interrupt
    ```c
    	_emi=1; //Enable interrupt
	    _tb0e=1;
    ```
    8. 主邏輯，更新Buffer內部的數值
        即使沒有致能tb1e， tb1f 還是會生效
    ```c
        while(1){
            //跑馬燈內容
            for(i=3;i!=0;i--) Buffer[i]=Buffer[i-1];
            Buffer[0]=j++;
            if(j>=9) j=0;
            //TB1 as a delay
            while(!_tb1f);  
            _tb1f=0;		
	    }
    ```
    9. ISR 服務
    ```c
    DEFINE_ISR(ISR_TB0, 0x24)
        {
            //負責刷新Scancode、7段顯示器的碼

            SegPort = 0; //要先清除Segport避免鬼影
            ScanPort = ScanCode;
            SegPort = SEG_TAB[*ptr++];
            
            GCC_RL(ScanCode);
            if (ScanCode==0b00010000){
                //Reset	
                ScanCode=0b00000001;
                ptr=Buffer;
            }

        }
    ```




