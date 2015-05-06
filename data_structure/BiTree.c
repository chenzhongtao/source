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
 
//�������ṹ�� 
typedef struct BiTNode{
    Elemtype data;    
    struct BiTNode *lchild, *rchild;          
}BiTNode, *BiTree;

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

/*
Status InOrderTraverse(BiTree T, Status (*Visit)(ElemType)) {  
  // �㷨6.2
  // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
  // �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
  stack S;
  BiTree p;
  InitStack(S);  Push(S, T);  // ��ָ���ջ
  while (!StackEmpty(S)) {
    while (GetTop(S, p) && p) Push(S, p->lchild);  // �����ߵ���ͷ
    Pop(S, p);                // ��ָ����ջ
    if (!StackEmpty(S)) {     // ���ʽ�㣬����һ��
      Pop(S, p);  
      if (!Visit(p->data)) return ERROR;
      Push(S, p->rchild);
    }
  }
  return OK;
} // InOrderTraverse

Status InOrderTraverse2(BiTree T, Status (*Visit)(ElemType)) {  
  // �㷨6.3
  // ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
  // �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
  stack S;
  BiTree p;
  InitStack(S);  p = T;
  while (p || !StackEmpty(S)) {
    if (p) { Push(S, p);  p = p->lchild; }  // �ǿ�ָ���ջ���������
    else {       // �ϲ�ָ����ջ����������ָ��㣬�����ҽ�
      Pop(S, p);  
      if (!Visit(p->data)) return ERROR;
      p = p->rchild;
    }
  }
  return OK;
} // InOrderTraverse
*/

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

int main()
{
    BiTree T;
    CreateBiTree(&T);
}
                           

