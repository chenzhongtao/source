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
//��������ڵ�  
typedef struct LNode  
{  
 ElemType data;    //������  
 struct LNode * next; //ָ����  
}LNode, * LinkList;    //LNODE�ȼ���struct LNode, PNODE�ȼ���struct LNode *  
    

//LinkList *L Ϊָ��ָ���ָ�룬 
void CreateList_L(LinkList *L, int n) {  // �㷨2.11
  // ��λ�����루���������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L 
  LinkList p;
  int i;
  (*L) = (LinkList)malloc(sizeof(LNode));
  (*L)->next = NULL;              // �Ƚ���һ����ͷ���ĵ�����
  for (i=n; i>0; --i) {
    p = (LinkList)malloc(sizeof(LNode));  // �����½��
    p->data = rand();     // ��Ϊһ��������ɵ�����(200����)
    p->next = (*L)->next;    (*L)->next = p;    // ���뵽��ͷ
  }
} // CreateList_L


Status GetElem_L(LinkList L,int i, ElemType *e) {  // �㷨2.8
  // LΪ��ͷ���ĵ������ͷָ�롣
  // ����i(i>=1)��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
  LinkList p;
  p = L->next;   
  int j = 1;           // ��ʼ����pָ���һ����㣬jΪ������
  while (p && j<i) {   // ˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
    p = p->next;  ++j;
  }
  if ( !p || j>i ) return ERROR;  // ��i��Ԫ�ز�����
  *e = p->data;   // ȡ��i��Ԫ��
  return OK;
} // GetElem_L

Status ListInsert_L(LinkList L, int i, ElemType e) {  // �㷨2.9
  // �ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
  LinkList p,s;
  p = L;   
  int j = 0;
  while (p && j < i-1) {  // Ѱ�ҵ�i-1�����
    p = p->next;
    ++j;
  } 
  if (!p || j > i-1) return ERROR;      // iС��1���ߴ��ڱ�
  s = (LinkList)malloc(sizeof(LNode));  // �����½��
  s->data = e;  s->next = p->next;      // ����L��
  p->next = s;
  return OK;
} // LinstInsert_L

Status ListDelete_L(LinkList L, int i, ElemType *e) {  // �㷨2.10
  // �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
  LinkList p,q;
  p = L;
  int j = 0;
  while (p->next && j < i-1) {  // Ѱ�ҵ�i����㣬����pָ����ǰ��
    p = p->next;
    ++j;
  }
  if (!(p->next) || j > i-1) return ERROR;  // ɾ��λ�ò�����
  q = p->next;
  p->next = q->next;           // ɾ�����ͷŽ��
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
    p = (LinkList)malloc(sizeof(LNode));  // �����½��
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
  s->next = h->next;      // ����L��
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


Status ListInsert_L_2(LinkList L, int i, ElemType e) {  // �㷨2.20
  // �ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
  LinkList h,s;
  if (!LocatePos(L, i-1, &h))   
    return ERROR;  // iֵ���Ϸ�
  if (!MakeNode(&s, e))
    return ERROR;  // ���洢����ʧ��
  InsFirst(h, s);  // ���ڴӵ�i��㿪ʼ��������i-1���������ͷ���
  return OK;
}  // ListInsert_L_2

Status ListDelete_L_2(LinkList L, int i, ElemType *e) {  // �㷨2.10
  // �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
  LinkList h,q;
  if (!LocatePos(L, i-1, &h))   
    return ERROR;  // iֵ���Ϸ�
  if (!DelFirst(h, &q)) //i-1���ڵ��൱��ͷ��㣬iΪ�׽ڵ㣬����Ϊɾ���׽��
    return ERROR;
  if (e != NULL)
  	*e = q->data;
  free(q);
  return OK;
} // ListDelete_L_2



/*
Status MergeList_L(NLinkList &La, NLinkList &Lb, NLinkList &Lc, 
                 int (*compare)(ElemType, ElemType)) {  // �㷨2.21
  // ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
  // �鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С�
  NLink ha, hb;
  Position pa, pb, q;
  ElemType a, b;
  if (!InitList(Lc)) return ERROR;  // �洢�ռ����ʧ��
  ha = GetHead(La);      // ha��hb�ֱ�ָ��La��Lb��ͷ���
  hb = GetHead(Lb);
  pa = nextPos(La, ha);  // pa��pb�ֱ�ָ��La��Lb�е�ǰ���
  pb = nextPos(Lb, hb);
  while (pa && pb) {     // La��Lb���ǿ�
    a = GetCurElem(pa);  // a��bΪ�����е�ǰ�Ƚ�Ԫ��
    b = GetCurElem(pb);
    if ((*compare)(a, b)<=0) {  // a��b
      DelFirst(ha, q);  Append(Lc, q);  pa = nextPos(La, pa);  
    } else {   // a��b
      DelFirst(hb, q);  Append(Lc, q);  pb = nextPos(Lb, pb);  
    }
  } // while
  if (pa) Append(Lc, pa);        // ����La��ʣ����
  else Append(Lc, pb);           // ����Lb��ʣ����
  FreeNode(ha);   FreeNode(hb);  // �ͷ�La��Lb��ͷ���
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
 LinkList  p = L->next;   //ָ���׽ڵ�  
 int len = 0;     //��¼�����ȵı���  
 while(NULL != p)  
 {  
  len++;  
  p = p->next;    //pָ����һ���  
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
