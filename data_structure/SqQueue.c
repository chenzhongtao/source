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

#define MAXQSIZE 100

//ѭ���б�  
typedef struct  
{   
    QElemType * base;
    int front;  
    int rear;  
}SqQueue;  
  
Status InitQueue(SqQueue *Q)  
{  
    Q->base = (QElemType *)malloc(MAXQSIZE*sizeof(QElemType));  
    if(!Q->base) exit(ERROR); 
    Q->front = Q->rear = 0; //��ʼʱͷβΪ0
    return OK; 
}//InitQueue  
  
Status DestroyQueue(SqQueue *Q)  
{  
    if(!Q) return ERROR;
    free(Q->base);
    Q->base = NULL;
    Q->front = Q->rear = 0;
    return OK;
}  
  
bool IsEmpty(SqQueue Q)  
{  
    if(Q.front == Q.rear)  //ͷβ���ʱΪ��
        return TRUE;  
    return FALSE;  
}//isEmpty  

Status QueueLength(SqQueue Q) 
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue *Q, QElemType e)  
{  
    if((Q->rear + 1) % MAXQSIZE == Q->front) return ERROR;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXQSIZE; //��βָ��Ľڵ�ʼ��û�����ݣ�����ֻ�ܱ���MAXQSIZE-1������
    return OK;  
} 
  
Status DEQueue(SqQueue *Q, QElemType *e)  
{  
    if(IsEmpty(*Q))  
    {  
        return ERROR;
    }  
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXQSIZE; 
    return OK;  
} 
  
  
Status PrintQueue(SqQueue Q)  
{   
    int i;
    for (i=0;(Q.front + i) % MAXQSIZE != Q.rear; i++)  
    {  
        printf("%d   ", Q.base[i]);  
    } 
    printf("\n"); 
    return OK;  
}  

//���Ե������е������� 
int main() 
{ 
    SqQueue s; 
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

