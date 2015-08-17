#include <stdio.h>  
#include <stdlib.h>  

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define OK 1
#define ok 1
#define ERROR 0
#define error 0

typedef int QElemType;  
typedef int Status; 
typedef int bool;  

typedef struct QNode  
{  
    QElemType data;  
    struct QNode *next;  
}QNode, *QueuePtr;  
  
typedef struct  
{  
    QueuePtr front;  
    QueuePtr rear;  
}LinkQueue;

  
Status InitQueue(LinkQueue *Q)  
{  
    //初始时队头队尾指向同一个节点(分配了一个没用的节点，不放数据，相当于头节点)
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));  
    if(!Q->front) exit(ERROR);  
    Q->front->next = NULL;
    return OK; 
}//InitQueue  
  
Status DestroyQueue(LinkQueue *Q)  
{  
    while(Q->front)  
    {  
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }  
}  
  
bool IsEmpty(LinkQueue Q)  
{  
    if(Q.front == Q.rear)  
        return TRUE;  
    return FALSE;  
}//isEmpty  

int QueueLength(LinkQueue Q) 
{
    QueuePtr p = Q.front;
    int i=0; 
    while(p->next)  
    {  	
    	i++;
        p = p->next;
    } 
	return i; 
}
  
Status EnQueue(LinkQueue *Q, QElemType e)  
{  
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));  
    if(!p)  exit(ERROR); 
    p->data = e;  
    p->next = NULL;//防止出现野指针  
    Q->rear->next = p;  
    Q->rear = p;//q->rear指向队尾  
    return OK;  
} 
  
Status DEQueue(LinkQueue *Q, QElemType *e)  
{  
    QueuePtr p;
    if(IsEmpty(*Q))  
    {  
        return ERROR;
    }  
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p) Q->rear = Q->front; //尾节点指向头节点
    free(p);   
    return OK;  
} 
  
  
Status PrintQueue(LinkQueue *Q)  
{  
    QueuePtr p = Q->front;    
    while(p)  
    {  
        printf("%d   ", p->data);  
        p = p->next;  
    } 
    printf("\n"); 
    return OK;  
} 

//测试单链队列的主程序 
int main() 
{ 
    LinkQueue s; 
    int x; 
    //输入若干正整数以0结束，依次入栈，然后依次出栈并打印 
    InitQueue(&s); 
    printf("Is empty: %d\n",IsEmpty(s));
    printf("the length is: %d\n",QueueLength(s));
    printf("进入队列顺序:   1   2   3 \n"); 
	EnQueue(&s,1); 
	EnQueue(&s,2); 
	EnQueue(&s,3);
 	printf("the top is : %d\n",x);
 	printf("Is empty: %d\n",IsEmpty(s));
 	printf("the length is: %d\n",QueueLength(s));
    printf("\n退出队列结果:"); 
    while(!IsEmpty(s)) { 
        DEQueue(&s,&x); 
        printf("%4d",x); 
    }
	printf("\nIs empty: %d\n",IsEmpty(s)); 
     
     
    //------------------------------------- 
    // TODO (#1#): 其它测试程序  
     
    //------------------------------------- 
     
    DestroyQueue(&s); //销毁栈  
        
    return 0; 
}

