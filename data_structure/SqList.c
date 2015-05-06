#include<stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ok 1
#define ERROR 0
#define error 0
#define INFEASIBLE -1
 
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
 
typedef int ElemType;
typedef int Status;

//顺序表结构体 
typedef struct{
    ElemType *elem;   //定义了顺序表中元素类型的数组指针，指向顺序表存储空间的基址
    int length;       //顺序表的长度(也即元素个数)
    int listsize;     //当前分配给顺序表的存储容量
}SqList;



Status InitList_Sq(SqList *L) {  // 算法2.3
  // 构造一个空的线性表L。
  //L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
  L->elem = (ElemType *)calloc(sizeof(ElemType), LIST_INIT_SIZE);
  if (!L->elem) exit(ERROR);        // 存储分配失败
  L->length = 0;                  // 空表长度为0
  L->listsize = LIST_INIT_SIZE;   // 初始存储容量
  return OK;
} // InitList_Sq

Status ListInsert_Sq(SqList *L, int i, ElemType e) {  // 算法2.4
  // 在顺序线性表L的第i个元素之前插入新的元素e，
  // i的合法值为1≤i≤ListLength_Sq(L)+1
  ElemType *p;
  if (i < 1 || i > L->length+1) return ERROR;  // i值不合法
  if (L->length >= L->listsize) {   // 当前存储空间已满，增加容量
    ElemType *newbase = (ElemType *)realloc(L->elem,
                  (L->listsize+LISTINCREMENT)*sizeof (ElemType));
    if (!newbase) return ERROR;   // 存储分配失败
    L->elem = newbase;             // 新基址
    L->listsize += LISTINCREMENT;  // 增加存储容量
  }
  ElemType *q = &(L->elem[i-1]);   // q为插入位置
  for (p = &(L->elem[L->length-1]); p>=q; --p) *(p+1) = *p;
                                  // 插入位置及之后的元素右移
  *q = e;       // 插入e
  ++L->length;   // 表长增1
  return OK;
} // ListInsert_Sq



Status ListDelete_Sq(SqList *L, int i, ElemType *e) {  // 算法2.5
  // 在顺序线性表L中删除第i个元素，并用e返回其值。
  // i的合法值为1≤i≤ListLength_Sq(L)。
  ElemType *p, *q;
  if (i<1 || i>L->length) return ERROR;  // i值不合法
  p = &(L->elem[i-1]);                   // p为被删除元素的位置
  if(e != NULL)
  	*e = *p;                               // 被删除元素的值赋给e
  q = L->elem+L->length-1;                // 表尾元素的位置
  for (++p; p<=q; ++p) *(p-1) = *p;     // 被删除元素之后的元素左移
  --L->length;                           // 表长减1
  return OK;
} // ListDelete_Sq

int LocateElem_Sq( SqList *L, ElemType e,
        Status (*compare)(ElemType, ElemType)) {  // 算法2.6
  // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序。
  // 若找到，则返回其在L中的位序，否则返回0。
  int i;
  ElemType *p;
  i = 1;        // i的初值为第1个元素的位序
  p = L->elem;   // p的初值为第1个元素的存储位置
  while (i <= L->length && !(*compare)(*p++, e)) 
    ++i;
  if (i <= L->length) return i;
  else return 0;
} // LocateElem_Sq

Status Compare(a, b)
{
    if (a == b)
        return 1;
    else 
		return 0;
}


void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) {  // 算法2.7
  // 已知顺序线性表La和Lb的元素按值非递减排列。
  // 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列。
  ElemType *pa,*pb,*pc,*pa_last,*pb_last;
  pa = La.elem;  pb = Lb.elem;
  Lc->listsize = Lc->length = La.length+Lb.length;
  pc = Lc->elem = (ElemType *)malloc(Lc->listsize*sizeof(ElemType));
  if (!Lc->elem)
    exit(ERROR);   // 存储分配失败
  pa_last = La.elem+La.length-1;
  pb_last = Lb.elem+Lb.length-1;
  while (pa <= pa_last && pb <= pb_last) {  // 归并
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= pa_last) *pc++ = *pa++;      // 插入La的剩余元素
  while (pb <= pb_last) *pc++ = *pb++;      // 插入Lb的剩余元素
} // MergeList



void Output_L(SqList *L)
{
	int i=0;	
    for(i=0;i<L->length;i++)
        printf("%d  ",L->elem[i]);
    printf("\n");
}


int GetElem(SqList *L,int i,ElemType *e)
{
    if(i>0&&i<=L->length)
        *e=L->elem[i-1];
    else
    	return ERROR;
}

int main()
{
    int i,elem;
	SqList L ,L2,L3;
	InitList_Sq(&L);
	for (i=0; i<10; i++)
	{
		ListInsert_Sq(&L, L.length+1, i) ;
	}
	Output_L(&L);
	ListDelete_Sq(&L, 4, NULL);
	Output_L(&L);
	printf("%d\n", (LocateElem_Sq(&L, 4,Compare)));
	printf("%d\n", (LocateElem_Sq(&L, 3,Compare)));
	GetElem(&L, 2, &elem);
	printf("%d \n",elem);
	InitList_Sq(&L2);
	for (i=0; i<10; i++)
	{
		ListInsert_Sq(&L2, L2.length+1, i*2) ;
	}
	InitList_Sq(&L3);
	MergeList_Sq(L, L2, &L3);
	Output_L(&L3);
	return 1;
	
}



