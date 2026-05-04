# Data Structure 練習筆記
## Stack
- FILO特性
### 說明
- 通常包含以下幾個Flag 和 function :
    - flags: 
        - is_empty: return index== initial_index
        - is_full: return index==stack_size
    - functions:
        - intialize: 初始化堆疊，將index設為指定的初始值
        - pop: 取出元素
        - push: 放入元素
        - peek: 只看，不pop
- 結構(Array) :

    可以用一個Array 和 top index表示

    ~~~c

    struct stack_S{
        int Data[stack_size];
        int top;
    }

    typedef struct stack_s stack;

    ~~~
## LinkedList
### 說明
- Node :

    Linked-list 是一個資料結構，每個點被稱為節點Node。通常Node會包含 :
    1. 一個Data
    2. 一個pointer 指向下一個Node
   ~~~c
   //節點資料結構定義範例
   struct node {
    int data;
    struct node *next;
   };
   typedef struct node Node;
   ~~~    
- Linked-List :
    由Node組成的的串列，包含一個Head:
    ~~~ c
    struct link_list{
        Node *head;
    };

    ~~~

