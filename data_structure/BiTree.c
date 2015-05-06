#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ok 1
#define ERROR 0
#define error 0

typedef char Elemtype;
typedef int Status;
 
//二叉树结构体 
typedef struct BiTNode{
    Elemtype data;    
    struct BiTNode *lchild, *rchild;          
}BiTNode, *BiTree;

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

/*
Status InOrderTraverse(BiTree T, Status (*Visit)(ElemType)) {  
  // 算法6.2
  // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。
  // 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
  stack S;
  BiTree p;
  InitStack(S);  Push(S, T);  // 根指针进栈
  while (!StackEmpty(S)) {
    while (GetTop(S, p) && p) Push(S, p->lchild);  // 向左走到尽头
    Pop(S, p);                // 空指针退栈
    if (!StackEmpty(S)) {     // 访问结点，向右一步
      Pop(S, p);  
      if (!Visit(p->data)) return ERROR;
      Push(S, p->rchild);
    }
  }
  return OK;
} // InOrderTraverse

Status InOrderTraverse2(BiTree T, Status (*Visit)(ElemType)) {  
  // 算法6.3
  // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。
  // 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
  stack S;
  BiTree p;
  InitStack(S);  p = T;
  while (p || !StackEmpty(S)) {
    if (p) { Push(S, p);  p = p->lchild; }  // 非空指针进栈，继续左进
    else {       // 上层指针退栈，访问其所指结点，再向右进
      Pop(S, p);  
      if (!Visit(p->data)) return ERROR;
      p = p->rchild;
    }
  }
  return OK;
} // InOrderTraverse
*/

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

int main()
{
    BiTree T;
    CreateBiTree(&T);
}
                           

