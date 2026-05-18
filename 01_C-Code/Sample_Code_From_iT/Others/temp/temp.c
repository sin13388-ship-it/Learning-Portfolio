

item.title  ==> strcpy(item.title ,"xxx") ;

item.title[0] = 'a' ;
item.title = 1234 ;  xxx



struct book {           
    char title[41];
    char author[31];
    float value;
} ;

typedef struct book BOOKS ;



typedef struct book {           
    char title[41];
    char author[31];
    float value;
} BOOKS;


struct names {                      
    char first[LEN];
    char last[LEN];
} ;

struct guy {
		struct names handle;           // nested structure
    char favfood[LEN];
    char job[LEN];
    float income;
} ;

    him++;               /* point to the next structure */
    
    him = &(fellow[1]) ;
    
   
   printf("him->favfood is %s:  him->handle.last is %s\n",
         him->favfood, (him->handle).last);    
         
         fellow[i].favfood



















person2 = person1 ;

==> memcpy((unsigned char *)(&person2),(unsigned char *)(&person1),
					sizeof(struct nameect)) ;

strcpy(person2.fname,person1.fname,) ;
strcpy(person2.lname,person1.lname,) ;
..









struct book 
{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
    
    char * string ;

    //struct book xxx ;
        
    struct book * next;
} ;   

struct book A ;
struct book B ;

A.next = &B ;

(A.next)->value = 10 ;  ==> B.value = 10 ;











enum new_type {AA,BB,CC,DD} ;

enum {AAA=100,BBB,CCC,DDD,EEE} ;
==>
#define AAA 0
#define BBB 1
#define CCC 2
#define DDD 3
#define EEE 4






























































































