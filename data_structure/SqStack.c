#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define OK 1
#define ok 1
#define ERROR 0
#define error 0
#define INFEASIBLE -1
 
typedef int ElemType;
typedef int Status; 
typedef int bool; 


/////////////////////////////////////////////////////////// 
//顺序栈的存储结构定义  
#define STACK_INIT_SIZE 100 /* 存储空间初始分配容量 */ 
#define STACKINCREMENT 10 /* 存储空间分配的增量 */ 
typedef struct { 
    ElemType *base; //在构造栈之前和销毁栈之后，base为NULL 
    ElemType *top; //栈顶指针 
    int stacksize; //当前已分配的存储空间(元素个数)  
} SqStack; 
/////////////////////////////////////////////////////////// 
//顺序栈的基本操作声明 
//构造一个空栈S  
Status InitStack(SqStack *S); 
//销毁栈S  
Status DestroyStack(SqStack *S); 
//将栈S清空  
Status ClearStack(SqStack *S); 
//若栈S为空返回TRUE，否则FALSE  
Status StackEmpty(SqStack S); 
//返回栈S中的元素个数 
int    StackLength(SqStack S); 
//用e返回栈顶元素 
//    前提：栈S存在且不空  
Status GetTop(SqStack S, ElemType *e); 
//元素e入栈S  
Status Push(SqStack *S, ElemType e); 
//S出栈用e返回出栈元素  
//    前提：栈S存在且不空  
Status Pop(SqStack *S, ElemType *e); 
 
/////////////////////////////////////////////////////////// 
//顺序栈的基本操作的实现 
 
//构造一个空栈S  
Status InitStack(SqStack *S) 
{ 
    // TODO (#1#): 构造一个空栈S 
    S->base=(ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType)); 
    if(!S->base) exit(ERROR); 
    S->top=S->base; 
    S->stacksize=STACK_INIT_SIZE; 
    return OK; 
    //------------------------------------- 
} 
 
//销毁栈S  
Status DestroyStack(SqStack *S) 
{ 
    // TODO (#1#):销毁栈S，相当于清空栈  
    free(S->base); 
    S->base=NULL; 
    return OK; 
    //------------------------------------- 
} 
 
//将栈S清空  
Status ClearStack(SqStack *S) 
{ 
    // TODO (#1#): 将栈S清空，释放所有结点 
    ElemType e; 
    while(Pop(S,&e)!=ERROR); 
    return OK; 
    //------------------------------------- 
} 
 
//若栈S为空返回TRUE，否则FALSE  
Status StackEmpty(SqStack S) 
{ 
    // TODO (#1#): 若栈S为空返回TRUE，否则FALSE 
    if(S.top==S.base) 
        return OK; 
    return ERROR; 
    //------------------------------------- 
} 
 
//返回栈S中的元素个数 
int    StackLength(SqStack S) 
{ 
    // TODO (#1#): 返回栈S中的元素个数 
    return S.top-S.base; 
    //------------------------------------- 
} 
 
//用e返回栈顶元素 
//    前提：栈S存在且不空  
Status GetTop(SqStack S, ElemType *e) 
{ 
    // TODO (#1#):若栈S不空，则用e返回栈顶元素 
    if(S.top ==S.base) 
        return ERROR; 
    *e=*(S.top-1); 
    return OK; 
    //------------------------------------- 
} 
 
//元素e入栈S  
Status Push(SqStack *S, ElemType e) 
{ 
    // TODO (#1#): 插入元素e作为新的栈顶  
    if(S->top-S->base>=S->stacksize) 
    { 
        S->base=(ElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(ElemType)); 
        if(!S->base)exit(ERROR); 
        S->top=S->base+S->stacksize; 
        S->stacksize+=STACKINCREMENT; 
    } 
    *S->top++=e; 
    //*S->top=e; 
    //S->top++; 
    return OK; 
    //------------------------------------- 
} 
 
//S出栈用e返回出栈元素  
//    前提：栈S存在且不空  
Status Pop(SqStack *S, ElemType *e) 
{ 
    // TODO (#1#):若栈S不空，则删除栈顶元素用e返回 
    if(S->top==S->base)  
    return ERROR; 
    *e=*--S->top; 
    return OK; 
    //------------------------------------- 
} 


//测试顺序栈的主程序 
int main() 
{ 
    SqStack s; 
    int x; 
    //输入若干正整数以0结束，依次入栈，然后依次出栈并打印 
    InitStack(&s); 
     
    printf("进栈顺序:   1   2   3 "); 
	Push(&s,1); 
	Push(&s,2); 
	Push(&s,3); 
     
    printf("\n出栈结果:"); 
    while(!StackEmpty(s)) { 
        Pop(&s,&x); 
        printf("%4d",x); 
    } 
     
     
    //------------------------------------- 
    // TODO (#1#): 其它测试程序  
     
    //------------------------------------- 
     
    DestroyStack(&s); //销毁栈  
     
    system("PAUSE");     
    return 0; 
} 

