/***********************************************
	Function: boot
***********************************************/
boot()
{
	
	...	// init h/w, init SP
			// set PSR  <== disable interrupt
			// copy data from ROM to RAM
			// clear BSS
			// ...
	...
	
	sys_main() ;  // call
		
}


/***********************************************
	ISRs
***********************************************/
_interrupt_ ISR1()
{
	...
	send_message(main_task_ID) ;
}

_interrupt_ ISR2()
{
	...	
	send_message(main_task_ID) ;
}


/***********************************************
	Function:
***********************************************/
unsigned char stack1[1024] ;
unsigned char stack2[1024] ;
unsigned char stack3[1024] ;

sys_main()
{
	... // init system
			// init FS
			// init_malloc
			...
	
	create_task(main_task,PRI_HIGH,stack1,...) ;
	create_task(idle_task,PRI_LOW,stack2,...) ;
	create_task(AP_task,PRI_MID,stact3,...) ;
	
	sys_start() ;
	
	// never ho back
}

int A ;

/***********************************************
	Function: main_task
***********************************************/
void main_task()
{
	int B = 10;
	while(1)
	{
		if(get_message())
		{
			process_message() ;
			wakeup(AP_task_ID) ;
			A = 10 ;
		}
		else
			sleep() ;
		
	}
	
}


/***********************************************
	Function: idle_task
***********************************************/
void idle_task()
{
	int B = 20;
	while(1)
	{
		if(A==10)
			...
			
		goto_power_saving_mode() ;
		wakeup(main_task_ID) ;
	}
	
}

/***********************************************
	Function: AP_task
***********************************************/
void AP_task()
{
	while(1)
	{
		if(get_message())
		{
			process_message() ;
		}
		else
			sleep(10) ;
		
	}	
	
}


