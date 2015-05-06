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

//ջ�Ĳ��������Ա�Ĳ���������

/////////////////////////////////////////////////////////// 
//��ջ�Ĵ洢�ṹ����  
typedef struct LNode { 
    ElemType data; 
    struct LNode *next; 
} LNode, *LinkList; 
 
typedef LinkList LinkStack; //��ջ����  
 
/////////////////////////////////////////////////////////// 
//��ջ�Ļ����������� 
 
//����һ����ջS  
Status InitStack(LinkStack *S); 
//����ջS  
Status DestroyStack(LinkStack *S); 
//��ջS���  
Status ClearStack(LinkStack *S); 
//��ջSΪ�շ���TRUE������FALSE  
Status StackEmpty(LinkStack S); 
//����ջS�е�Ԫ�ظ��� 
int    StackLength(LinkStack S); 
//��e����ջ��Ԫ�� 
//    ǰ�᣺ջS�����Ҳ���  
Status GetTop(LinkStack S, ElemType *e); 
//Ԫ��e��ջS  
Status Push(LinkStack *S, ElemType e); 
//S��ջ��e���س�ջԪ��  
//    ǰ�᣺ջS�����Ҳ���  
Status Pop(LinkStack *S, ElemType *e); 
 
/////////////////////////////////////////////////////////// 
//��ջ�Ļ���������ʵ�� 
 
//����һ����ջS  
Status InitStack(LinkStack *S) 
{ 
    // TODO (#1#): ����һ����ջS����ͷ��� 
    (*S)=(LinkStack)malloc(sizeof(LNode));  //�½�ͷ��� 
    if(!(*S)) return ERROR; 
    (*S)->next=NULL; 
    return OK; 
    //------------------------------------- 
} 
 
//����ջS  
Status DestroyStack(LinkStack *S) 
{ 
    // TODO (#1#):����ջS���൱�����ջ 
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
 
//��ջS���  
Status ClearStack(LinkStack *S) 
{ 
    // TODO (#1#): ��ջS��գ��ͷ����н�� 
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
 
//��ջSΪ�շ���TRUE������FALSE  
Status StackEmpty(LinkStack S) 
{ 
    // TODO (#1#): ��ջSΪ�շ���TRUE������FALSE 
    if(S->next==NULL) 
    return 1; 
    else 
        return 0; 
    //------------------------------------- 
} 
 
//����ջS�е�Ԫ�ظ��� 
int  StackLength(LinkStack S) 
{ 
    // TODO (#1#): ����ջS�е�Ԫ�ظ��� 
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
 
//��e����ջ��Ԫ�� 
//    ǰ�᣺ջS�����Ҳ���  
Status GetTop(LinkStack S, ElemType *e) 
{ 
    // TODO (#1#):��ջS���գ�����e����ջ��Ԫ�� 
    if(S->next==NULL) exit(ERROR); 
    *e=S->next->data; 
    return OK; 
    //------------------------------------- 
} 
 
//Ԫ��e��ջS  
Status Push(LinkStack *S, ElemType e) 
{ 
    // TODO (#1#): ����Ԫ��e��Ϊ�µ�ջ��  ͷ�巨 
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
 
//S��ջ��e���س�ջԪ��  
//ǰ�᣺ջS�����Ҳ���  
Status Pop(LinkStack *S, ElemType *e) 
{ 
    // TODO (#1#):��ջS���գ���ɾ��ջ��Ԫ����e����  
    LinkStack p;
    if((*S)->next==NULL) return ERROR; 
	p = (*S)->next; 
	*e=p->data; 
    (*S)->next=p->next;
    free(p);
    return OK; 
    //------------------------------------- 
} 


//������ջ�������� 
int main() 
{ 
    LinkStack s; 
    int x; 
    //����������������0������������ջ��Ȼ�����γ�ջ����ӡ 
    InitStack(&s); 
    printf("Is empty: %d\n",StackEmpty(s));
    printf("the length is: %d\n",StackLength(s));
    printf("��ջ˳��:   1   2   3 \n"); 
	Push(&s,1); 
	Push(&s,2); 
	Push(&s,3);
	GetTop(s, &x);
 	printf("the top is : %d\n",x);
 	printf("Is empty: %d\n",StackEmpty(s));
 	printf("the length is: %d\n",StackLength(s));
    printf("\n��ջ���:"); 
    while(!StackEmpty(s)) { 
        Pop(&s,&x); 
        printf("%4d",x); 
    }
	printf("\nIs empty: %d\n",StackEmpty(s)); 
     
     
    //------------------------------------- 
    // TODO (#1#): �������Գ���  
     
    //------------------------------------- 
     
    DestroyStack(&s); //����ջ  
        
    return 0; 
} 

