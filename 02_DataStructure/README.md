# Data Structure 練習筆記
## Contents

- [Demo Code List](#demo-code-list)
- [Stack](#stack)
- [LinkedList](#linkedlist)
- [Queue](#queue)
- [Tree](#tree)
- [Hash Table](#hash-table)




## Demo Code List
|Project Name|Topic|Description|Review date|
|------------|-----|-----------|-----------|
|stack_a|Stack|使用Array 實現Stack|5/2|
|linklist|Linked-List|節點與串列的實現|5/3~5/5|
|linkedlist4student|Linked-List|Homework|5/9|
|queue_a|queue|佇列，使用陣列的方式來實現|5/10|
|queue_L|queue|佇列，使用linked-list的方式來實現|5/10|
|Sorted linked list 4 student|linked-list|implement linked-list with sorting|5/11|
|Double linked list 4 student|linked-list|implement a double linked-list |5/12|
|BinaryTree4Student|Tree|使用linked-list來實現Tree|5/16|
|HashTable|Hash table|使用linked-list來實現Hash table|5/18-|



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
- 變種 :
    - 雙向 linked-list
        - 除了有next 外還有一個 prev
        ```c
        struct node 
        {
            int data;
            struct node *next;
            struct node *prev; 
        };
        ``` 

- 課程提供的Linked-list方法 (link-list) :
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
- 


### Linked-List Homework
#### Sorted linked list
- 實作一個在insert節點的時候會順便sorting的方法
> - 使用升序排序
> - 實作 void llist_insert_with_sorting(LinkList * linklist, Node *newNode) 
- 步驟解說:
    - 宣告一個node 為prev, 用於儲存滿足條件的前一個節點
    - 因為是升序排列，要找到比newNode 小的前一個節點
    - 如果prev=NULL， 表示從頭到尾都沒有，直接insert 在head
```c
/*******************************************
	Method :llist_insert_with_sorting
*******************************************/
// Insert with sorting
void llist_insert_with_sorting(LinkList * linklist, Node *newNode) 
{ 	
	Node *cur;
	Node *prev;
	cur=linklist->head;
	prev=NULL;
	if(newNode==NULL) return;
	//Ascending order
	while(cur !=NULL && (cur->data <= newNode->data)){
		prev=cur;
		cur=cur->next;
	}	
	if (prev==NULL){
		llist_insert_in_front(linklist, newNode);
	}else
	{
		llist_insert(linklist,prev,newNode);
	}
}
```

## Queue
### 說明
- Queue 具有First-in-Frist-Out (FIFO)的特性
- Queue 具有兩個開口且各司其職 :
    - 資料的刪除在Front執行，稱之為dequeue
    - 資料的加入在rear執行，稱之為enqueue
- 配套方法:
    - 基本方法 :
        - dequeue
        - enqueue
    - 支援方法 :
        - size
        - isEmpty
- 變種:
    - Circular queue :
    線性的佇列會發生明明前面的資料已經空了，卻仍然占住空間。可以用circular queue 改善
    - 如何判斷佇烈已空和已滿?
        - is empty : queue.front == queue.rear
        - is full : queue.front == (queue.rear+1) % Maxqueue

## Tree
### 說明
- 樹的種類 :
樹分成無序數即有序數兩種:
    - 無序樹 : 樹中的任意節點沒有順序，又被稱為自由樹 
    - 有序樹 : 樹中的任意節點的子節點之間有順序關係    
        - 二元樹 : 每個節點最多包含兩個子樹
            - Full binary tree :每一個節點的左右子分支都有節點
            - complete binary tree : 最後一層沒有滿

            ||Full Binary Tree|Complete Binary Tree|
            |-|---|---|
            |總節點|k=2^h -1| 2^(h-1) < k <2^h-1|
            |樹高 h|log2(k+1)|log2(k)+1|

        - 紅黑樹 :
            - 紅黑樹是一種自平衡二元搜尋樹，可在最壞情況下保持搜尋、插入、刪除為 O(log n)
            - 每個節點都有一個顏色屬性：紅或黑
            - 資料結構特性：
                1. 節點為紅或黑
                2. 根節點必須為黑
                3. 所有葉節點(NIL節點)為黑
                4. 紅節點的子節點必須為黑（不能連續兩個紅節點）
                5. 從任一節點到其所有後代葉節點的黑色節點數量相同
            - 這些規則保證了樹的高度是 O(log n)，避免了在最壞情況下退化成鏈狀結構
            - 常見應用：
                - C++ STL 的 `std::map`、`std::set`
                - 作業系統排程或記憶體管理中的平衡搜尋
        - B 樹 :
            - B 樹是一種平衡多路搜尋樹，常用於資料庫與檔案系統的磁碟資料結構
            - 每個節點可以有多個子節點，節點內保存多個鍵值
            - 特性規則：
                1. 每個節點最多有 `m` 個子節點、最少有 `⌈m/2⌉` 個子節點（根節點例外）
                2. 每個非葉節點有 `k-1` 個鍵值和 `k` 個子節點，`⌈m/2⌉ - 1 <= k <= m-1`
                3. 所有葉節點具有相同深度
                4. 節點內鍵值按排序順序儲存
            - B 樹適合用於磁碟 I/O 優化，因為一個節點可以包含大量鍵值，減少讀寫次數
        - B+ 樹 :
            - B+ 樹是 B 樹的變種，所有資料值只保存在葉節點，內部節點僅做索引
            - 葉節點之間用指標串連，支援範圍查詢和順序遍歷效率高
            - 特性規則：
                1. 所有值都存在葉節點，內部節點只保存索引鍵
                2. 內部節點只需儲存子樹範圍邊界，鍵值可重複於不同分支
                3. 葉節點依然保持同一深度
                4. 葉節點通常形成一個有序鏈結列表
            - 常見應用：資料庫索引、檔案系統和任何需要高效範圍查詢的儲存系統
### Binary Tree 的組成
1. 節點
    - 包含left、right 兩個sub-trees
    - sub-trees 都是 binary tree
2. 節點 example:
    
    ```c
    struct t_node {
        void *item;
        struct t_node *right;
        struct t_node *left;
    };
    ```
    - break down :

        ```struct t_node { ... };```

        This declares a structure named t_node. Each instance of this struct represents one node in the tree.
        
        ```void *item;```

        Stores the data/value held by this node.
        void * is a generic pointer — it can point to any data type (an int, a char, another struct, etc.). This makes the node flexible and reusable for any kind of data.

        ```struct t_node *right;```

        A pointer to this node's right child node.
        It points to another struct t_node, which is how the tree links together.

        ```struct t_node *left;```

        A pointer to this node's left child node.
        Same idea as right, but for the left branch.

        ---

        ```Why Self-Referencing?```
        
        Notice that t_node contains pointers to itself (struct t_node *right/left). This is called a self-referential struct — it's the standard technique for building linked data structures like trees and linked lists in C.

    - Code example: Typecasting a ```void*```
    
    ```c
    #include <stdio.h>
    #include <stdlib.h>

    struct t_node {
        void *item;
        struct t_node *right;
        struct t_node *left;
    };

    int main() {
        // 1. Allocate memory for a node
        struct t_node *root = malloc(sizeof(struct t_node));
        
        // 2. Allocate memory for an integer and assign a value
        int *data = malloc(sizeof(int));
        *data = 42;
        
        // 3. Store the integer pointer inside the void* item
        root->item = data; 
        root->left = NULL;
        root->right = NULL;

        // ==========================================
        // HOW TO USE IT (Typecasting & Dereferencing)
        // ==========================================
        
        // Step-by-step approach:
        int *stored_ptr = (int *)root->item; // 1. Cast void* to int*
        int value1 = *stored_ptr;            // 2. Dereference to get the value
        
        // All-in-one approach (most common in C):
        int value2 = *(int *)(root->item);

        printf("Value via step-by-step: %d\n", value1);
        printf("Value via all-in-one: %d\n", value2);

        // Clean up memory
        free(data);
        free(root);
        return 0;
    }
    ```



## Hash Table

Hash table 的威力：用「空間換時間」，讓查找、插入、刪除的時間複雜度從 O(n) 降至平均 O(1)。

### 說明
- Hashing :

### Trace code
- 使用linked-list 定義一個Hash table

```c

struct hashtable 
{
       LinkList list[HASH_TABLE_ENTRY_NO] ;
};

typedef struct hashtable HashTable ;

```
- Linked-list 的結構會跟之前有些許的不同

```c
// Node definition add student
//
struct node 
{
			 int data ;
			 Student student;
       
       struct node *next;
};

typedef struct node Node ;

// using a node to represent a linke-list
//
struct linklist
{
	Node * head ;
} ;

typedef struct linklist LinkList ;

```
```c
// Student Structure
//
struct student 
{
       char name[MAX_NAME_SIZE];
       int age ;
       //...
};

typedef struct student Student ;

```
- 方法

    - `void hash_init(HashTable * hashTable)` :
        - 使用Linked-list 的方法initialize table 中的每一列元素
        - 關聯方法 `void llist_init(LinkList * linklist) `
    - `int hash_function(char * student_name)` :
        - 生成Hash值，作為Hash table 的 index
        - 作法:
            - 取得Student 的名稱，ASCII加總 Mod 32
    - `void hash_add_student(HashTable * hashTable, Student * student_info)` :
        - 關聯方法 `int hash_function(char * student_name)` : 取得Hash值
        - 關聯方法 `void llist_set_student_info(Node * node, Student * student_info)` : 先新增一個node
        - 關聯方法 `void llist_insert_in_front(LinkList * linklist, Node *newNode)` : 再把node 加到list的前面
    - `int hash_search(HashTable * hashTable, Student * toFind, Student * found)` :
        - 關聯方法 `int hash_function(char * student_name)` : 取得Hash值
        - 關聯方法 `Node * llist_search_student(LinkList * linklist, Student * student_info)`




