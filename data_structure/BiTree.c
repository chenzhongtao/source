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

//二叉树结构体 
typedef struct BiTNode{
    Elemtype data;    
    struct BiTNode *lchild, *rchild;          
}BiTNode, *BiTree;

//定义链表节点  
typedef struct LNode  
{  
 Elemtype data;    //数据域  
 struct LNode * next; //指针域  
}LNode, * LinkList;    //LNODE等价于struct LNode, PNODE等价于struct LNode *  

//顺序栈的存储结构定义  
#define STACK_INIT_SIZE 100 /* 存储空间初始分配容量 */ 
#define STACKINCREMENT 10 /* 存储空间分配的增量 */ 

typedef BiTree SSElemType; 

typedef struct { 
    SSElemType *base; //在构造栈之前和销毁栈之后，base为NULL 
    SSElemType *top; //栈顶指针 
    int stacksize; //当前已分配的存储空间(元素个数)  
} SqStack; 

//顺序栈的基本操作的实现
Status InitStack(SqStack *S);  
Status DestroyStack(SqStack *S); 
Status ClearStack(SqStack *S); 
Status StackEmpty(SqStack S); 
int    StackLength(SqStack S);  
Status GetTop(SqStack S, SSElemType *e);  
Status Push(SqStack *S, SSElemType e); 
Status Pop(SqStack *S, SSElemType *e); 
 
//队列的存储结构定义
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
//队列的基本操作的实现
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
   // 算法6.1
   // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
   // 先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
   // 最简单的Visit函数是：
   //     Status PrintElement( ElemType e ) {  // 输出元素e的值
   //        printf( e );  // 实用时，加上格式串
   //        return OK;
   //     }
   // 调用实例：PreOrderTraverse(T, PrintElement);
   if (T) {
      if (Visit(T->data))
         if (PreOrderTraverse(T->lchild, Visit))
            if (PreOrderTraverse(T->rchild, Visit)) return OK;
      return ERROR;
   } else return OK;
} // PreOrderTraverse

Status InOrderTraverse( BiTree T, Status(*Visit)(Elemtype) ) {
   // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
   // 中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。

   if (T) {
     if (InOrderTraverse(T->lchild, Visit))
        if (Visit(T->data))
            if (InOrderTraverse(T->rchild, Visit)) return OK;
      return ERROR;
   } else return OK;
} // InOrderTraverse

Status PostOrderTraverse( BiTree T, Status(*Visit)(Elemtype) ) {
   // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
   // 中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。

   if (T) {
     if (PostOrderTraverse(T->lchild, Visit))
        if (PostOrderTraverse(T->rchild, Visit)) 
            if (Visit(T->data)) return OK;
      return ERROR;
   } else return OK;
} // PostOrderTraverse

Status InOrderTraverse2(BiTree T, Status (*Visit)(Elemtype)) {  
  // 算法6.2
  // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。
  // 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
  SqStack S;
  BiTree p;
  InitStack(&S);  Push(&S, T);  // 根指针进栈
  while (!StackEmpty(S)) {
    while (GetTop(S, &p) && p) Push(&S, p->lchild);  // 向左走到尽头
    Pop(&S, &p);                // 空指针退栈
    if (!StackEmpty(S)) {     // 访问结点，向右一步
      Pop(&S, &p);  
      if (!Visit(p->data)) return ERROR;
      Push(&S, p->rchild);
    }
  }
  return OK;
} // InOrderTraverse


Status InOrderTraverse3(BiTree T, Status (*Visit)(Elemtype)) {  
  // 算法6.3
  // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。
  // 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
  SqStack S;
  BiTree p;
  InitStack(&S);  p = T;
  while (p || !StackEmpty(S)) {
    if (p) { Push(&S, p);  p = p->lchild; }  // 非空指针进栈，继续左进
    else {       // 上层指针退栈，访问其所指结点，再向右进
      Pop(&S, &p);  
      if (!Visit(p->data)) return ERROR;
      p = p->rchild;
    }
  }
  return OK;
} // InOrderTraverse

Status LevelOrderTraverse(BiTree T, Status (*Visit)(Elemtype)) {	//层次遍历
  BiTree p;
  LinkQueue Q;//循环队列，元素为结点指针，类型为pointer
  if(T==NULL) return;
  InitQueue(&Q);
  EnQueue(&Q, T);			//根结点入队
  while(!IsEmpty(Q)) {	//队列非空时
    DEQueue(&Q, &p);if (!Visit(p->data)) return ERROR;
		                    //出队，访问队头
    if(p->lchild!=NULL) EnQueue(&Q,p->lchild);
	                         //左孩子入队
    if(p->rchild!=NULL) EnQueue(&Q,p->rchild);
	                         //右孩子入队
  }
}


BiTree CreateBiTree(BiTree *T) {  // 算法6.4
  // 按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
  // 构造二叉链表表示的二叉树T。
  char ch;
  scanf("%c",&ch);
  if (ch=='#') *T = NULL;
  else {
    if (!(*T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
    (*T)->data = ch;              // 生成根结点
    CreateBiTree(&((*T)->lchild));   // 构造左子树
    CreateBiTree(&((*T)->rchild));   // 构造右子树
  }
  return *T;
} // CreateBiTree

BiTree CreateBiTree2(char Pre[],int ps,int pe,
             char In[],int is,int ie) {//由先序和中序建二叉树
   BiTree t;
   int i;
   if(ps>pe || is>ie) return NULL;
   t = (BiTNode *)malloc(sizeof(BiTNode)); //生成根结点
   t->data=Pre[ps];
   i=is;
   while(In[i]!=Pre[ps]) i++;	//寻找中序序列中根的位置i
   t->lchild=CreateBiTree2(Pre,ps+1,ps+i-is,In,is,i-1);//生成左子树
   t->rchild=CreateBiTree2(Pre,ps+i-is+1,pe,In,i+1,ie);//生成右子树
   return t;
}

//求叶子节点数: 逐结点处理(遍历)：如果当前结点是叶子，则叶子数加1
int num=0;		//num为叶子数，全局量，初始化为0
void leaf(BiTree t) {
  if(t==NULL) return;	//空树什么都不做
  if(t->lchild==NULL && t->rchild==NULL) num++; //访问根：若为叶子，则叶子数+1
  leaf(t->lchild);	//访问左子树：累计其中的叶子数
  leaf(t->rchild);	//访问右子树：累计其中的叶子数
}

//递归处理：叶子数等于左子树和右子树的叶子数之和，左子树和右子树本身
//又是二叉树，求其叶子数递归进行
int leaf2(BiTree t) {	//叶子数通过函数值返回
  int L,R;
  if(t==NULL) return 0;//空树的叶子为0
  if(t->lchild==NULL && t->rchild==NULL)
    return 1;		//树中只有一个点，就是叶子
  L=leaf2(t->lchild);//求左子树的叶子数(访问左子树)
  R=leaf2(t->rchild);//求右子树的叶子数(访问右子树)
  return L+R; 	//叶子数=左右子树叶子数之和(访问根)
}

//判断二叉树是否所有结点存放的都是数字字符。 
//逐结点处理(遍历)：但不一定遍历完所有结点，一旦发现某个点
//或子树不合要求，就不必对后继子树进行遍历。 
int detect(BiTree t) {
  int x;
  if(t==NULL) return 1;	//空树
  if(t->data<'0'|| t->data>'9')return 0;//访问根：若非数字字符，则跳过子树检查
  x=detect(t->lchild); 
  if(x==0) return 0; //遍历左子树，若为假，则跳过右子树检查
  x=detect(t->rchild); //遍历右子树
  return x;            //最后结果由右子树决定
}

//递归处理：如果根不是数字字符，则当前结果肯定为假，返回；否则
//当前结果由左子树和右子树的情况共同决定
int detect2(BiTree t) {
  if(t==NULL) return 1;	//认为空树符合条件(真)
  if(t->data<'0'||t->data>'9') return 0;//访问根：若不是数字字符则返回假
  return detect2(t->lchild) && detect2(t->rchild);//左子树和右子树共同决定
}

//判断两棵二叉树是否等价，即要么都为空；要么根相同，
//且左右子树分别等价。 
int same(BiTree t1,BiTree t2) {
  if(t1==NULL && t2==NULL) return 1;//同时为空树
  if(t1==NULL || t2==NULL) return 0;//一个为空，另一个非空
  if(t1->data!=t2->data) return 0;  //根不相等
  return same(t1->lchild,t2->lchild)
    && same(t1->rchild,t2->rchild);//左子树和右子树共同决定
}

//求根到某个指定节点的路径
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




//构造一个空栈S  
Status InitStack(SqStack *S) 
{ 
    // TODO (#1#): 构造一个空栈S 
    S->base=(SSElemType*)malloc(STACK_INIT_SIZE * sizeof(SSElemType)); 
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
    SSElemType e; 
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
Status GetTop(SqStack S, SSElemType *e) 
{ 
    // TODO (#1#):若栈S不空，则用e返回栈顶元素 
    if(S.top ==S.base) 
        return ERROR; 
    *e=*(S.top-1); 
    return OK; 
    //------------------------------------- 
} 
 
//元素e入栈S  
Status Push(SqStack *S, SSElemType e) 
{ 
    // TODO (#1#): 插入元素e作为新的栈顶  
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
 
//S出栈用e返回出栈元素  
//    前提：栈S存在且不空  
Status Pop(SqStack *S, SSElemType *e) 
{ 
    // TODO (#1#):若栈S不空，则删除栈顶元素用e返回 
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
    if(Q->rear == p) Q->rear = Q->front; 
    free(p);   
    return OK;  
} 
  
                          

