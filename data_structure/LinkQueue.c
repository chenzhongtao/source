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
    //��ʼʱ��ͷ��βָ��ͬһ���ڵ�(������һ��û�õĽڵ㣬�������ݣ��൱��ͷ�ڵ�)
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
    p->next = NULL;//��ֹ����Ұָ��  
    Q->rear->next = p;  
    Q->rear = p;//q->rearָ���β  
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
    if(Q->rear == p) Q->rear = Q->front; //β�ڵ�ָ��ͷ�ڵ�
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

//���Ե������е������� 
int main() 
{ 
    LinkQueue s; 
    int x; 
    //����������������0������������ջ��Ȼ�����γ�ջ����ӡ 
    InitQueue(&s); 
    printf("Is empty: %d\n",IsEmpty(s));
    printf("the length is: %d\n",QueueLength(s));
    printf("�������˳��:   1   2   3 \n"); 
	EnQueue(&s,1); 
	EnQueue(&s,2); 
	EnQueue(&s,3);
 	printf("the top is : %d\n",x);
 	printf("Is empty: %d\n",IsEmpty(s));
 	printf("the length is: %d\n",QueueLength(s));
    printf("\n�˳����н��:"); 
    while(!IsEmpty(s)) { 
        DEQueue(&s,&x); 
        printf("%4d",x); 
    }
	printf("\nIs empty: %d\n",IsEmpty(s)); 
     
     
    //------------------------------------- 
    // TODO (#1#): �������Գ���  
     
    //------------------------------------- 
     
    DestroyQueue(&s); //����ջ  
        
    return 0; 
}

