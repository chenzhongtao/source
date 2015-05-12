#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ok 1
#define ERROR 0
#define error 0

typedef int Status;
typedef int bool; 

typedef char Elemtype;

//�������ṹ�� 
typedef struct BiTNode{
    Elemtype data;    
    struct BiTNode *lchild, *rchild;          
}BiTNode, *BiTree;

//��������ڵ�  
typedef struct LNode  
{  
 Elemtype data;    //������  
 struct LNode * next; //ָ����  
}LNode, * LinkList;    //LNODE�ȼ���struct LNode, PNODE�ȼ���struct LNode *  

//˳��ջ�Ĵ洢�ṹ����  
#define STACK_INIT_SIZE 100 /* �洢�ռ��ʼ�������� */ 
#define STACKINCREMENT 10 /* �洢�ռ��������� */ 

typedef BiTree SSElemType; 

typedef struct { 
    SSElemType *base; //�ڹ���ջ֮ǰ������ջ֮��baseΪNULL 
    SSElemType *top; //ջ��ָ�� 
    int stacksize; //��ǰ�ѷ���Ĵ洢�ռ�(Ԫ�ظ���)  
} SqStack; 

//˳��ջ�Ļ���������ʵ��
Status InitStack(SqStack *S);  
Status DestroyStack(SqStack *S); 
Status ClearStack(SqStack *S); 
Status StackEmpty(SqStack S); 
int    StackLength(SqStack S);  
Status GetTop(SqStack S, SSElemType *e);  
Status Push(SqStack *S, SSElemType e); 
Status Pop(SqStack *S, SSElemType *e); 
 
//���еĴ洢�ṹ����
typedef BiTree QElemType;    

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
//���еĻ���������ʵ��
Status InitQueue(LinkQueue *Q);
Status DestroyQueue(LinkQueue *Q);
bool   IsEmpty(LinkQueue Q);
int    QueueLength(LinkQueue Q) ;
Status EnQueue(LinkQueue *Q, QElemType e); 
Status DEQueue(LinkQueue *Q, QElemType *e); 



Status Visit(Elemtype data)
{
    printf("%c ",data);
}

Status PreOrderTraverse( BiTree T, Status(*Visit)(Elemtype) ) {
   // �㷨6.1
   // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
   // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
   // ��򵥵�Visit�����ǣ�
   //     Status PrintElement( ElemType e ) {  // ���Ԫ��e��ֵ
   //        printf( e );  // ʵ��ʱ�����ϸ�ʽ��
   //        return OK;
   //     }
   // ����ʵ����PreOrderTraverse(T, PrintElement);
   if (T) {
      if (Visit(T->data))
         if (PreOrderTraverse(T->lchild, Visit))
            if (PreOrderTraverse(T->rchild, Visit)) return OK;
      return ERROR;
   } else return OK;
} // PreOrderTraverse

Status InOrderTraverse( BiTree T, Status(*Visit)(Elemtype) ) {
   // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
   // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��

   if (T) {
     if (InOrderTraverse(T->lchild, Visit))
        if (Visit(T->data))
            if (InOrderTraverse(T->rchild, Visit)) return OK;
      return ERROR;
   } else return OK;
} // InOrderTraverse

Status PostOrderTraverse( BiTree T, Status(*Visit)(Elemtype) ) {
   // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
   // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��

   if (T) {
     if (PostOrderTraverse(T->lchild, Visit))
        if (PostOrderTraverse(T->rchild, Visit)) 
            if (Visit(T->data)) return OK;
      return ERROR;
   } else return OK;
} // PostOrderTraverse

Status InOrderTraverse2(BiTree T, Status (*Visit)(Elemtype)) {  
  // �㷨6.2
  // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
  // �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
  SqStack S;
  BiTree p;
  InitStack(&S);  Push(&S, T);  // ��ָ���ջ
  while (!StackEmpty(S)) {
    while (GetTop(S, &p) && p) Push(&S, p->lchild);  // �����ߵ���ͷ
    Pop(&S, &p);                // ��ָ����ջ
    if (!StackEmpty(S)) {     // ���ʽ�㣬����һ��
      Pop(&S, &p);  
      if (!Visit(p->data)) return ERROR;
      Push(&S, p->rchild);
    }
  }
  return OK;
} // InOrderTraverse


Status InOrderTraverse3(BiTree T, Status (*Visit)(Elemtype)) {  
  // �㷨6.3
  // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
  // �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
  SqStack S;
  BiTree p;
  InitStack(&S);  p = T;
  while (p || !StackEmpty(S)) {
    if (p) { Push(&S, p);  p = p->lchild; }  // �ǿ�ָ���ջ���������
    else {       // �ϲ�ָ����ջ����������ָ��㣬�����ҽ�
      Pop(&S, &p);  
      if (!Visit(p->data)) return ERROR;
      p = p->rchild;
    }
  }
  return OK;
} // InOrderTraverse

Status LevelOrderTraverse(BiTree T, Status (*Visit)(Elemtype)) {	//��α���
  BiTree p;
  LinkQueue Q;//ѭ�����У�Ԫ��Ϊ���ָ�룬����Ϊpointer
  if(T==NULL) return;
  InitQueue(&Q);
  EnQueue(&Q, T);			//��������
  while(!IsEmpty(Q)) {	//���зǿ�ʱ
    DEQueue(&Q, &p);if (!Visit(p->data)) return ERROR;
		                    //���ӣ����ʶ�ͷ
    if(p->lchild!=NULL) EnQueue(&Q,p->lchild);
	                         //�������
    if(p->rchild!=NULL) EnQueue(&Q,p->rchild);
	                         //�Һ������
  }
}


BiTree CreateBiTree(BiTree *T) {  // �㷨6.4
  // �������������������н���ֵ��һ���ַ������ո��ַ���ʾ������
  // ������������ʾ�Ķ�����T��
  char ch;
  scanf("%c",&ch);
  if (ch=='#') *T = NULL;
  else {
    if (!(*T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
    (*T)->data = ch;              // ���ɸ����
    CreateBiTree(&((*T)->lchild));   // ����������
    CreateBiTree(&((*T)->rchild));   // ����������
  }
  return *T;
} // CreateBiTree

BiTree CreateBiTree2(char Pre[],int ps,int pe,
             char In[],int is,int ie) {//����������򽨶�����
   BiTree t;
   int i;
   if(ps>pe || is>ie) return NULL;
   t = (BiTNode *)malloc(sizeof(BiTNode)); //���ɸ����
   t->data=Pre[ps];
   i=is;
   while(In[i]!=Pre[ps]) i++;	//Ѱ�����������и���λ��i
   t->lchild=CreateBiTree2(Pre,ps+1,ps+i-is,In,is,i-1);//����������
   t->rchild=CreateBiTree2(Pre,ps+i-is+1,pe,In,i+1,ie);//����������
   return t;
}

//��Ҷ�ӽڵ���: ���㴦��(����)�������ǰ�����Ҷ�ӣ���Ҷ������1
int num=0;		//numΪҶ������ȫ��������ʼ��Ϊ0
void leaf(BiTree t) {
  if(t==NULL) return;	//����ʲô������
  if(t->lchild==NULL && t->rchild==NULL) num++; //���ʸ�����ΪҶ�ӣ���Ҷ����+1
  leaf(t->lchild);	//�������������ۼ����е�Ҷ����
  leaf(t->rchild);	//�������������ۼ����е�Ҷ����
}

//�ݹ鴦��Ҷ������������������������Ҷ����֮�ͣ�������������������
//���Ƕ�����������Ҷ�����ݹ����
int leaf2(BiTree t) {	//Ҷ����ͨ������ֵ����
  int L,R;
  if(t==NULL) return 0;//������Ҷ��Ϊ0
  if(t->lchild==NULL && t->rchild==NULL)
    return 1;		//����ֻ��һ���㣬����Ҷ��
  L=leaf2(t->lchild);//����������Ҷ����(����������)
  R=leaf2(t->rchild);//����������Ҷ����(����������)
  return L+R; 	//Ҷ����=��������Ҷ����֮��(���ʸ�)
}

//�ж϶������Ƿ����н���ŵĶ��������ַ��� 
//���㴦��(����)������һ�����������н�㣬һ������ĳ����
//����������Ҫ�󣬾Ͳ��ضԺ���������б����� 
int detect(BiTree t) {
  int x;
  if(t==NULL) return 1;	//����
  if(t->data<'0'|| t->data>'9')return 0;//���ʸ������������ַ����������������
  x=detect(t->lchild); 
  if(x==0) return 0; //��������������Ϊ�٣����������������
  x=detect(t->rchild); //����������
  return x;            //�����������������
}

//�ݹ鴦����������������ַ�����ǰ����϶�Ϊ�٣����أ�����
//��ǰ��������������������������ͬ����
int detect2(BiTree t) {
  if(t==NULL) return 1;	//��Ϊ������������(��)
  if(t->data<'0'||t->data>'9') return 0;//���ʸ��������������ַ��򷵻ؼ�
  return detect2(t->lchild) && detect2(t->rchild);//����������������ͬ����
}

//�ж����ö������Ƿ�ȼۣ���Ҫô��Ϊ�գ�Ҫô����ͬ��
//�����������ֱ�ȼۡ� 
int same(BiTree t1,BiTree t2) {
  if(t1==NULL && t2==NULL) return 1;//ͬʱΪ����
  if(t1==NULL || t2==NULL) return 0;//һ��Ϊ�գ���һ���ǿ�
  if(t1->data!=t2->data) return 0;  //�������
  return same(t1->lchild,t2->lchild)
    && same(t1->rchild,t2->rchild);//����������������ͬ����
}

//�����ĳ��ָ���ڵ��·��
LinkList path(BiTree t1,Elemtype data) {
    LinkList l;
    LinkList child;
    if(t1==NULL ) return NULL;
    if(t1->data == data) 
    {
        l= (LinkList)malloc(sizeof(LNode)); 
        l->next = NULL;
        l->data = data;
        return l;
    }
    if ((child = path(t1->lchild, data)) != NULL)
    {
        l= (LinkList)malloc(sizeof(LNode)); 
        l->next = child;
        l->data = t1->data;
        return l;
    }
    else if ((child = path(t1->rchild, data)) != NULL)
    {
        l= (LinkList)malloc(sizeof(LNode)); 
        l->next = child;
        l->data = t1->data;
        return l;
    }
    else
        return NULL;
}

int main()
{
    /*
    
                A
               /
              B
             / \
            C   D
               / \
              E   F
               \
                G
    */
    BiTree T;
    char *Pre = "ABCDEGF";
    char *In = "CBEGDFA";
    char *Post = "CGEFDBA";
    T = CreateBiTree2(Pre, 0, 6, In, 0, 6);
    PreOrderTraverse(T, Visit);
    printf("\n");
    InOrderTraverse(T, Visit);
    printf("\n");
    InOrderTraverse2(T, Visit);
    printf("\n");
    InOrderTraverse3(T, Visit);
    printf("\n");
    PostOrderTraverse(T, Visit);
    printf("\n");
    LevelOrderTraverse(T, Visit);
    printf("\n");

    LinkList l = path(T,'E');
    while(NULL != l)  
    {  
        printf("%c  ", l->data);  
        l = l->next;  
    }  
    printf("\n"); 
}




//����һ����ջS  
Status InitStack(SqStack *S) 
{ 
    // TODO (#1#): ����һ����ջS 
    S->base=(SSElemType*)malloc(STACK_INIT_SIZE * sizeof(SSElemType)); 
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
    SSElemType e; 
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
Status GetTop(SqStack S, SSElemType *e) 
{ 
    // TODO (#1#):��ջS���գ�����e����ջ��Ԫ�� 
    if(S.top ==S.base) 
        return ERROR; 
    *e=*(S.top-1); 
    return OK; 
    //------------------------------------- 
} 
 
//Ԫ��e��ջS  
Status Push(SqStack *S, SSElemType e) 
{ 
    // TODO (#1#): ����Ԫ��e��Ϊ�µ�ջ��  
    if(S->top-S->base>=S->stacksize) 
    { 
        S->base=(SSElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SSElemType)); 
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
Status Pop(SqStack *S, SSElemType *e) 
{ 
    // TODO (#1#):��ջS���գ���ɾ��ջ��Ԫ����e���� 
    if(S->top==S->base)  
    return ERROR; 
    *e=*--S->top; 
    return OK; 
    //------------------------------------- 
}
 
Status InitQueue(LinkQueue *Q)  
{  
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
    if(Q->rear == p) Q->rear = Q->front; 
    free(p);   
    return OK;  
} 
  
                          

