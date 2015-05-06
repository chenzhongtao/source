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

//栈的操作是线性表的操作的特例

/////////////////////////////////////////////////////////// 
//链栈的存储结构定义  
typedef struct LNode { 
    ElemType data; 
    struct LNode *next; 
} LNode, *LinkList; 
 
typedef LinkList LinkStack; //链栈类型  
 
/////////////////////////////////////////////////////////// 
//链栈的基本操作声明 
 
//构造一个空栈S  
Status InitStack(LinkStack *S); 
//销毁栈S  
Status DestroyStack(LinkStack *S); 
//将栈S清空  
Status ClearStack(LinkStack *S); 
//若栈S为空返回TRUE，否则FALSE  
Status StackEmpty(LinkStack S); 
//返回栈S中的元素个数 
int    StackLength(LinkStack S); 
//用e返回栈顶元素 
//    前提：栈S存在且不空  
Status GetTop(LinkStack S, ElemType *e); 
//元素e入栈S  
Status Push(LinkStack *S, ElemType e); 
//S出栈用e返回出栈元素  
//    前提：栈S存在且不空  
Status Pop(LinkStack *S, ElemType *e); 
 
/////////////////////////////////////////////////////////// 
//链栈的基本操作的实现 
 
//构造一个空栈S  
Status InitStack(LinkStack *S) 
{ 
    // TODO (#1#): 构造一个空栈S，带头结点 
    (*S)=(LinkStack)malloc(sizeof(LNode));  //新建头结点 
    if(!(*S)) return ERROR; 
    (*S)->next=NULL; 
    return OK; 
    //------------------------------------- 
} 
 
//销毁栈S  
Status DestroyStack(LinkStack *S) 
{ 
    // TODO (#1#):销毁栈S，相当于清空栈 
    LinkStack p; 
    while(*S) 
    { 
       p=(*S)->next; 
       free(*S); 
       *S=p; 
    } 
    return OK; 
    //------------------------------------- 
} 
 
//将栈S清空  
Status ClearStack(LinkStack *S) 
{ 
    // TODO (#1#): 将栈S清空，释放所有结点 
    LinkStack p,q; 
    p=(*S)->next; 
    while(p) 
    { 
       q=p->next; 
       free(p); 
       p=q; 
    } 
    (*S)->next=NULL; 
    return OK; 
    //------------------------------------- 
} 
 
//若栈S为空返回TRUE，否则FALSE  
Status StackEmpty(LinkStack S) 
{ 
    // TODO (#1#): 若栈S为空返回TRUE，否则FALSE 
    if(S->next==NULL) 
    return 1; 
    else 
        return 0; 
    //------------------------------------- 
} 
 
//返回栈S中的元素个数 
int  StackLength(LinkStack S) 
{ 
    // TODO (#1#): 返回栈S中的元素个数 
    LinkStack p; 
    int x=0; 
    p=S->next; 
    while(p!=NULL) 
    { 
       x++; 
       p=p->next; 
    } 
    return x; 
    //------------------------------------- 
} 
 
//用e返回栈顶元素 
//    前提：栈S存在且不空  
Status GetTop(LinkStack S, ElemType *e) 
{ 
    // TODO (#1#):若栈S不空，则用e返回栈顶元素 
    if(S->next==NULL) exit(ERROR); 
    *e=S->next->data; 
    return OK; 
    //------------------------------------- 
} 
 
//元素e入栈S  
Status Push(LinkStack *S, ElemType e) 
{ 
    // TODO (#1#): 插入元素e作为新的栈顶  头插法 
    LinkStack p; 
    p=(LinkStack)malloc(sizeof(LNode)); 
    if(!p)exit(ERROR); 
    p->data=e; 
    p->next=NULL; 
    p->next=(*S)->next; 
    (*S)->next=p; 
    return OK; 
    //------------------------------------- 
} 
 
//S出栈用e返回出栈元素  
//前提：栈S存在且不空  
Status Pop(LinkStack *S, ElemType *e) 
{ 
    // TODO (#1#):若栈S不空，则删除栈顶元素用e返回  
    LinkStack p;
    if((*S)->next==NULL) return ERROR; 
	p = (*S)->next; 
	*e=p->data; 
    (*S)->next=p->next;
    free(p);
    return OK; 
    //------------------------------------- 
} 


//测试链栈的主程序 
int main() 
{ 
    LinkStack s; 
    int x; 
    //输入若干正整数以0结束，依次入栈，然后依次出栈并打印 
    InitStack(&s); 
    printf("Is empty: %d\n",StackEmpty(s));
    printf("the length is: %d\n",StackLength(s));
    printf("进栈顺序:   1   2   3 \n"); 
	Push(&s,1); 
	Push(&s,2); 
	Push(&s,3);
	GetTop(s, &x);
 	printf("the top is : %d\n",x);
 	printf("Is empty: %d\n",StackEmpty(s));
 	printf("the length is: %d\n",StackLength(s));
    printf("\n出栈结果:"); 
    while(!StackEmpty(s)) { 
        Pop(&s,&x); 
        printf("%4d",x); 
    }
	printf("\nIs empty: %d\n",StackEmpty(s)); 
     
     
    //------------------------------------- 
    // TODO (#1#): 其它测试程序  
     
    //------------------------------------- 
     
    DestroyStack(&s); //销毁栈  
        
    return 0; 
} 

