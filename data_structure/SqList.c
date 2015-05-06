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

//˳���ṹ�� 
typedef struct{
    ElemType *elem;   //������˳�����Ԫ�����͵�����ָ�룬ָ��˳���洢�ռ�Ļ�ַ
    int length;       //˳���ĳ���(Ҳ��Ԫ�ظ���)
    int listsize;     //��ǰ�����˳���Ĵ洢����
}SqList;



Status InitList_Sq(SqList *L) {  // �㷨2.3
  // ����һ���յ����Ա�L��
  //L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
  L->elem = (ElemType *)calloc(sizeof(ElemType), LIST_INIT_SIZE);
  if (!L->elem) exit(ERROR);        // �洢����ʧ��
  L->length = 0;                  // �ձ���Ϊ0
  L->listsize = LIST_INIT_SIZE;   // ��ʼ�洢����
  return OK;
} // InitList_Sq

Status ListInsert_Sq(SqList *L, int i, ElemType e) {  // �㷨2.4
  // ��˳�����Ա�L�ĵ�i��Ԫ��֮ǰ�����µ�Ԫ��e��
  // i�ĺϷ�ֵΪ1��i��ListLength_Sq(L)+1
  ElemType *p;
  if (i < 1 || i > L->length+1) return ERROR;  // iֵ���Ϸ�
  if (L->length >= L->listsize) {   // ��ǰ�洢�ռ���������������
    ElemType *newbase = (ElemType *)realloc(L->elem,
                  (L->listsize+LISTINCREMENT)*sizeof (ElemType));
    if (!newbase) return ERROR;   // �洢����ʧ��
    L->elem = newbase;             // �»�ַ
    L->listsize += LISTINCREMENT;  // ���Ӵ洢����
  }
  ElemType *q = &(L->elem[i-1]);   // qΪ����λ��
  for (p = &(L->elem[L->length-1]); p>=q; --p) *(p+1) = *p;
                                  // ����λ�ü�֮���Ԫ������
  *q = e;       // ����e
  ++L->length;   // ����1
  return OK;
} // ListInsert_Sq



Status ListDelete_Sq(SqList *L, int i, ElemType *e) {  // �㷨2.5
  // ��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ��
  // i�ĺϷ�ֵΪ1��i��ListLength_Sq(L)��
  ElemType *p, *q;
  if (i<1 || i>L->length) return ERROR;  // iֵ���Ϸ�
  p = &(L->elem[i-1]);                   // pΪ��ɾ��Ԫ�ص�λ��
  if(e != NULL)
  	*e = *p;                               // ��ɾ��Ԫ�ص�ֵ����e
  q = L->elem+L->length-1;                // ��βԪ�ص�λ��
  for (++p; p<=q; ++p) *(p-1) = *p;     // ��ɾ��Ԫ��֮���Ԫ������
  --L->length;                           // ����1
  return OK;
} // ListDelete_Sq

int LocateElem_Sq( SqList *L, ElemType e,
        Status (*compare)(ElemType, ElemType)) {  // �㷨2.6
  // ��˳�����Ա�L�в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ��
  // ���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0��
  int i;
  ElemType *p;
  i = 1;        // i�ĳ�ֵΪ��1��Ԫ�ص�λ��
  p = L->elem;   // p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
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


void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) {  // �㷨2.7
  // ��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
  // �鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С�
  ElemType *pa,*pb,*pc,*pa_last,*pb_last;
  pa = La.elem;  pb = Lb.elem;
  Lc->listsize = Lc->length = La.length+Lb.length;
  pc = Lc->elem = (ElemType *)malloc(Lc->listsize*sizeof(ElemType));
  if (!Lc->elem)
    exit(ERROR);   // �洢����ʧ��
  pa_last = La.elem+La.length-1;
  pb_last = Lb.elem+Lb.length-1;
  while (pa <= pa_last && pb <= pb_last) {  // �鲢
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= pa_last) *pc++ = *pa++;      // ����La��ʣ��Ԫ��
  while (pb <= pb_last) *pc++ = *pb++;      // ����Lb��ʣ��Ԫ��
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



