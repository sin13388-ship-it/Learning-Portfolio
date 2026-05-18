step1:
	towers(3, ．A・, ．C・, ．B・);    // move A to C by B

===============================================
step2:
	towers(2, ．A・, ．B・, ．C・);   // step 2-1  
4.	move #3 from A to C
	towers(2, ．B・, ．C・, ．A・); 	// step 4-1

===============================================
step2-1:
	towers(1, ．A・, ．C・, ．B・);   // step 3-1  
2.	move #2 to B
	towers(1, ．C・, ．B・, ．A・); 	// step 3-2

step3-1:
1.	move #1 from A to C

step3-2:
3.	move #1 from C to B
===============================================
step4-1:
	towers(1, ．B・, ．A・, ．C・);   // step 5-1  
6.	move #2 from B to C
	towers(1, ．A・, ．C・, ．B・); 	// step 5-2

step5-1:
5.	move #1 from B to A

step5-2:
7.	move #1 from A to C


