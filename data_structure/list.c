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
//定义链表节点  
typedef struct LNode  
{  
 ElemType data;    //数据域  
 struct LNode * next; //指针域  
}LNode, * LinkList;    //LNODE等价于struct LNode, PNODE等价于struct LNode *  
    

//LinkList *L 为指向指针的指针， 
void CreateList_L(LinkList *L, int n) {  // 算法2.11
  // 逆位序输入（随机产生）n个元素的值，建立带表头结点的单链线性表L 
  LinkList p;
  int i;
  (*L) = (LinkList)malloc(sizeof(LNode));
  (*L)->next = NULL;              // 先建立一个带头结点的单链表
  for (i=n; i>0; --i) {
    p = (LinkList)malloc(sizeof(LNode));  // 生成新结点
    p->data = rand();     // 改为一个随机生成的数字(200以内)
    p->next = (*L)->next;    (*L)->next = p;    // 插入到表头
  }
} // CreateList_L


Status GetElem_L(LinkList L,int i, ElemType *e) {  // 算法2.8
  // L为带头结点的单链表的头指针。
  // 当第i(i>=1)个元素存在时，其值赋给e并返回OK，否则返回ERROR
  LinkList p;
  p = L->next;   
  int j = 1;           // 初始化，p指向第一个结点，j为计数器
  while (p && j<i) {   // 顺指针向后查找，直到p指向第i个元素或p为空
    p = p->next;  ++j;
  }
  if ( !p || j>i ) return ERROR;  // 第i个元素不存在
  *e = p->data;   // 取第i个元素
  return OK;
} // GetElem_L

Status ListInsert_L(LinkList L, int i, ElemType e) {  // 算法2.9
  // 在带头结点的单链线性表L的第i个元素之前插入元素e
  LinkList p,s;
  p = L;   
  int j = 0;
  while (p && j < i-1) {  // 寻找第i-1个结点
    p = p->next;
    ++j;
  } 
  if (!p || j > i-1) return ERROR;      // i小于1或者大于表长
  s = (LinkList)malloc(sizeof(LNode));  // 生成新结点
  s->data = e;  s->next = p->next;      // 插入L中
  p->next = s;
  return OK;
} // LinstInsert_L

Status ListDelete_L(LinkList L, int i, ElemType *e) {  // 算法2.10
  // 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
  LinkList p,q;
  p = L;
  int j = 0;
  while (p->next && j < i-1) {  // 寻找第i个结点，并令p指向其前趋
    p = p->next;
    ++j;
  }
  if (!(p->next) || j > i-1) return ERROR;  // 删除位置不合理
  q = p->next;
  p->next = q->next;           // 删除并释放结点
  if (e != NULL)
  	*e = q->data;
  free(q);
  return OK;
} // ListDelete_L

Status LocatePos(LinkList L, int i, LinkList *h)
{
  LinkList p,s;
  p = L;   
  int j = 0;
  while (p && j < i) {  
    p = p->next;
    ++j;
  } 
  if (!p || j > i) return ERROR; 
  *h = p;
  return OK;
}

Status MakeNode(LinkList *s, ElemType e)
{
    LinkList p;
    p = (LinkList)malloc(sizeof(LNode));  // 生成新结点
    if (p == NULL)
        return ERROR;
    p->data = e;
    *s = p;
	return OK;   
}

Status InsFirst(LinkList h, LinkList s)
{
  if (h == NULL || s == NULL)
            return ERROR;
  s->next = h->next;      // 插入L中
  h->next = s;
  return OK;
}

Status DelFirst(LinkList h, LinkList *q)
{
  if (h == NULL || *q == NULL)
    return ERROR;
  if (h->next == NULL)
    printf("The list is empty \n");
    return ERROR;
  *q = h->next;
  h->next = h->next->next;
  return OK;
  
}


Status ListInsert_L_2(LinkList L, int i, ElemType e) {  // 算法2.20
  // 在带头结点的单链线性表L的第i个元素之前插入元素e
  LinkList h,s;
  if (!LocatePos(L, i-1, &h))   
    return ERROR;  // i值不合法
  if (!MakeNode(&s, e))
    return ERROR;  // 结点存储分配失败
  InsFirst(h, s);  // 对于从第i结点开始的链表，第i-1结点是它的头结点
  return OK;
}  // ListInsert_L_2

Status ListDelete_L_2(LinkList L, int i, ElemType *e) {  // 算法2.10
  // 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
  LinkList h,q;
  if (!LocatePos(L, i-1, &h))   
    return ERROR;  // i值不合法
  if (!DelFirst(h, &q)) //i-1个节点相当于头结点，i为首节点，这里为删除首结点
    return ERROR;
  if (e != NULL)
  	*e = q->data;
  free(q);
  return OK;
} // ListDelete_L_2



/*
Status MergeList_L(NLinkList &La, NLinkList &Lb, NLinkList &Lc, 
                 int (*compare)(ElemType, ElemType)) {  // 算法2.21
  // 已知单链线性表La和Lb的元素按值非递减排列。
  // 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列。
  NLink ha, hb;
  Position pa, pb, q;
  ElemType a, b;
  if (!InitList(Lc)) return ERROR;  // 存储空间分配失败
  ha = GetHead(La);      // ha和hb分别指向La和Lb的头结点
  hb = GetHead(Lb);
  pa = nextPos(La, ha);  // pa和pb分别指向La和Lb中当前结点
  pb = nextPos(Lb, hb);
  while (pa && pb) {     // La和Lb均非空
    a = GetCurElem(pa);  // a和b为两表中当前比较元素
    b = GetCurElem(pb);
    if ((*compare)(a, b)<=0) {  // a≤b
      DelFirst(ha, q);  Append(Lc, q);  pa = nextPos(La, pa);  
    } else {   // a＞b
      DelFirst(hb, q);  Append(Lc, q);  pb = nextPos(Lb, pb);  
    }
  } // while
  if (pa) Append(Lc, pa);        // 链接La中剩余结点
  else Append(Lc, pb);           // 链接Lb中剩余结点
  FreeNode(ha);   FreeNode(hb);  // 释放La和Lb的头结点
  return OK;
} // MergeList_L*/
                               
  
void TraverseLinkList(LinkList L)  
{  
 LinkList p = L->next;  
 while(NULL != p)  
 {  
  printf("%d  ", p->data);  
  p = p->next;  
 }  
 printf("\n");  
 return;  
}  
  
bool IsEmpty(LinkList L)  
{  
 if(NULL == L->next)  
  return true;  
 else  
  return false;  
}  
  
int GetLength(LinkList L)  
{  
 LinkList  p = L->next;   //指向首节点  
 int len = 0;     //记录链表长度的变量  
 while(NULL != p)  
 {  
  len++;  
  p = p->next;    //p指向下一结点  
 }  
 return len;  
}  
  

int main(void)  
{  
    LinkList list;
    CreateList_L(&list, 10);
    TraverseLinkList(list);
    printf("%d \n",GetLength(list));
    ListInsert_L_2(list, 3, 44);
    ListDelete_L_2(list, 5, NULL);
    TraverseLinkList(list);   
}  
