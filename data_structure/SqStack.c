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
//˳��ջ�Ĵ洢�ṹ����  
#define STACK_INIT_SIZE 100 /* �洢�ռ��ʼ�������� */ 
#define STACKINCREMENT 10 /* �洢�ռ��������� */ 
typedef struct { 
    ElemType *base; //�ڹ���ջ֮ǰ������ջ֮��baseΪNULL 
    ElemType *top; //ջ��ָ�� 
    int stacksize; //��ǰ�ѷ���Ĵ洢�ռ�(Ԫ�ظ���)  
} SqStack; 
/////////////////////////////////////////////////////////// 
//˳��ջ�Ļ����������� 
//����һ����ջS  
Status InitStack(SqStack *S); 
//����ջS  
Status DestroyStack(SqStack *S); 
//��ջS���  
Status ClearStack(SqStack *S); 
//��ջSΪ�շ���TRUE������FALSE  
Status StackEmpty(SqStack S); 
//����ջS�е�Ԫ�ظ��� 
int    StackLength(SqStack S); 
//��e����ջ��Ԫ�� 
//    ǰ�᣺ջS�����Ҳ���  
Status GetTop(SqStack S, ElemType *e); 
//Ԫ��e��ջS  
Status Push(SqStack *S, ElemType e); 
//S��ջ��e���س�ջԪ��  
//    ǰ�᣺ջS�����Ҳ���  
Status Pop(SqStack *S, ElemType *e); 
 
/////////////////////////////////////////////////////////// 
//˳��ջ�Ļ���������ʵ�� 
 
//����һ����ջS  
Status InitStack(SqStack *S) 
{ 
    // TODO (#1#): ����һ����ջS 
    S->base=(ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType)); 
    if(!S->base) exit(ERROR); 
    S->top=S->base; 
    S->stacksize=STACK_INIT_SIZE; 
    return OK; 
    //------------------------------------- 
} 
 
//����ջS  
Status DestroyStack(SqStack *S) 
{ 
    // TODO (#1#):����ջS���൱�����ջ  
    free(S->base); 
    S->base=NULL; 
    return OK; 
    //------------------------------------- 
} 
 
//��ջS���  
Status ClearStack(SqStack *S) 
{ 
    // TODO (#1#): ��ջS��գ��ͷ����н�� 
    ElemType e; 
    while(Pop(S,&e)!=ERROR); 
    return OK; 
    //------------------------------------- 
} 
 
//��ջSΪ�շ���TRUE������FALSE  
Status StackEmpty(SqStack S) 
{ 
    // TODO (#1#): ��ջSΪ�շ���TRUE������FALSE 
    if(S.top==S.base) 
        return OK; 
    return ERROR; 
    //------------------------------------- 
} 
 
//����ջS�е�Ԫ�ظ��� 
int    StackLength(SqStack S) 
{ 
    // TODO (#1#): ����ջS�е�Ԫ�ظ��� 
    return S.top-S.base; 
    //------------------------------------- 
} 
 
//��e����ջ��Ԫ�� 
//    ǰ�᣺ջS�����Ҳ���  
Status GetTop(SqStack S, ElemType *e) 
{ 
    // TODO (#1#):��ջS���գ�����e����ջ��Ԫ�� 
    if(S.top ==S.base) 
        return ERROR; 
    *e=*(S.top-1); 
    return OK; 
    //------------------------------------- 
} 
 
//Ԫ��e��ջS  
Status Push(SqStack *S, ElemType e) 
{ 
    // TODO (#1#): ����Ԫ��e��Ϊ�µ�ջ��  
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
 
//S��ջ��e���س�ջԪ��  
//    ǰ�᣺ջS�����Ҳ���  
Status Pop(SqStack *S, ElemType *e) 
{ 
    // TODO (#1#):��ջS���գ���ɾ��ջ��Ԫ����e���� 
    if(S->top==S->base)  
    return ERROR; 
    *e=*--S->top; 
    return OK; 
    //------------------------------------- 
} 


//����˳��ջ�������� 
int main() 
{ 
    SqStack s; 
    int x; 
    //����������������0������������ջ��Ȼ�����γ�ջ����ӡ 
    InitStack(&s); 
     
    printf("��ջ˳��:   1   2   3 "); 
	Push(&s,1); 
	Push(&s,2); 
	Push(&s,3); 
     
    printf("\n��ջ���:"); 
    while(!StackEmpty(s)) { 
        Pop(&s,&x); 
        printf("%4d",x); 
    } 
     
     
    //------------------------------------- 
    // TODO (#1#): �������Գ���  
     
    //------------------------------------- 
     
    DestroyStack(&s); //����ջ  
     
    system("PAUSE");     
    return 0; 
} 

