# Data Structure 練習筆記
## Demo Code List
|Project Name|Topic|Description|Review date|
|------------|-----|-----------|-----------|
|stack_a|Stack|使用Array 實現Stack|5/2|
|linklist|Linked-List|節點與串列的實現|5/3~5/5|



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

    Linked-list 是一個資料結構，是一種線性序列，但並不是按縣性的順序存放資料。
    Linked-list 用數個節點(Node)串接而成。通常Node會包含 :
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
    只要用一個節點(Head)來描述即可:
    ~~~ c
    struct link_list{
        Node *head;
    };
    ~~~

- 課程提供的Linked-list方法 :
    - Initialize :
        - 把list 裡的head設為null
    - Generate new node:
        - 和CPU 要一塊記憶體(malloc)，回傳null表示失敗
    - Insert
        - 從head insert 
        - 從rear insert 
        - 從特定Node insert
    - Delete
        - 記得要free
    - Traval
        - 取得每個節點的元素
    - Concat
        - 串接兩個linked-list

## Stack using linked-list

