#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>

/*
��������(ֱ�����򡢶�������ϣ������)
��������(ð�����򡢿�������)
ѡ������ (ֱѡ�����������򡢶�����)
�鲢����(��·�鲢���򡢶�·�鲢����)
��������(��ؼ������򡢻�������)
*/ 

/*
 ���    ���򷽷�        ʱ�临�Ӷ�                 �ռ临�Ӷ�     �ȶ��� 
                     ƽ��       ���      �      �����洢 
��������  ֱ�Ӳ���   O(n^2)     O(n)     O(n^2)       O(1)          �ȶ� 
��������  shell����  O(n^1.3)   O(n)     O(n^2)       O(1)          ���ȶ�
ѡ������  ֱ��ѡ��   O(n^2)    O(n^2)    O(n^2)       O(1)          ���ȶ�
ѡ������  ������    O(nlogn)  O(nlogn)   O(nlogn)     O(1)          ���ȶ�
��������  ð������  O(n^2)     O(n)      O(n^2)       O(1)          �ȶ�
��������  ��������  O(nlogn)  O(nlogn)   O(n^2)       O(nlogn)      ���ȶ�
�鲢����  �鲢����  O(nlogn)  O(nlogn)   O(nlogn)     O(1)          �ȶ�
��������  ��������  O(d(r+n)) O(d(rd+n)) O(d(r+n))    O(rd+n)       �ȶ� 

r����ؼ��ֵĻ�����d�����ȣ� 
*/



/** 
  *�������� 
  *�㷨ʵ�֣���������һ��¼R[i] ����������R[1]~R[i-1]���Ҳ���λ�ú��ƶ���¼����
  *���У����������ĺ�j��ʼ�������λ�ü�¼���ڴ����¼�������һλ�������¼��
  *�뵽���ճ���λ���ϡ� 
 
  * @brief �ϰ����ݽṹ����� 
  *        ��õ����,���鱾�����򣬾�ֻ��ִ��n-1�αȽϣ���ʱʱ�临�Ӷ�ΪO(n); 
  *        �����������鱾������Ҫִ��n(n-1)/2�Σ���ʱʱ�临�Ӷ�ΪO(n^2); 
  *        �ȶ� 
  */  
void insertSort(int R[], int n)  
{  
    int i, j, key;  
    for ( i = 1; i < n; ++i ) {  
        if ( R[i] < R[i - 1] ) {//��R[i]���������ֱ�  
            key = R[i];        //����R[0]���ã������ڱ�  
            for ( j = i - 1; R[j] > key && j>=0; --j ) {  
                R[j+1] = R[j];  
            }  
            R[j+1] = key;  
        }  
    }  
}

/*
��������:
�ڲ����i��Ԫ��ʱ����ǰ���0��i-1Ԫ�ؽ����۰룬�ȸ����� �м���Ǹ�Ԫ�رȣ�
���С�����ǰ���ٽ����۰룬����Ժ�� �����۰룬ֱ��left>right��Ȼ���ٰѵ�i
��Ԫ��ǰ1λ��Ŀ��λ��֮�� ������Ԫ�غ��ƣ��ٰѵ�i��Ԫ�ط���Ŀ��λ���ϡ�
 
���ַ���������Ҫ��һ��������ǲ���Ҫ����Ԫ�ص�λ�ã�Ҳ����Ҫ����һ��λ���Ϸ���
��Ҫ׼����������Ԫ�ء������ǲ��ҵ�λ���Ժ�ͺܺ�˵�ˣ��Ͳ�������һ���������
λ���Ժ������Ԫ�ض�����ƶ�һλ��������ʵ���˶��ַ�����

ƽ��ʱ��O(n^2)
*/

 void binSort(int R[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        int start, end, mid;
        start = 0;
        end = i - 1;
        mid = 0;
        int temp = R[i];
        while (start <= end)  //ѭ������ʱ end = start-1 
        {
            mid = (start + end) / 2;
            if (R[mid] > temp)//Ҫ����Ԫ�����Ѿ��Ź�����������
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
        for (j = i - 1; j > end; j--)//�ҵ���Ҫ�����λ�ã�Ȼ�����λ���Ժ������Ԫ������ƶ�

        {
            R[j + 1] = R[j];
        }
        R[end] = temp;  //end + 1 = start 
    }
}


/*
shell���� 
�㷨ʵ�֣�
���ݱ�ֳ������飬���Ϊĳ�����������ļ�¼Ϊһ�飬������ֱ�Ӳ������򣻳�ʼ����d1
�ϴ󣬷���϶�(ÿ��ļ�¼����)���Ժ������𽥼��٣��������(ÿ��ļ�¼������)��ֱ
���������Ϊ1(d1>d2>��>dt=1)�����м�¼��Ϊͬһ�飬���������һ��ֱ�Ӳ�������

ʱ�䣺O(nlog2n)��O(n2)֮�䣬����O(n1.3) ������ֱ�Ӳ���
���ȶ� 
*/

void ShellInsert(int R[],int n,int h) {
//һ�˲�������hΪ��������
  int i,j,k,temp;
  for(i=0; i<=h-1; i++)		 //iΪ���
    for(j=i+h; j<n; j+=h) {//ÿ��ӵ�2����¼��ʼ����
      if(R[j] >= R[j-h]) continue;
      temp = R[j];	//��������¼�������Ǽ�����
      k = j-h;		//�����¼��ǰһ����¼
      do {		     //���Ҳ���λ��
        R[k+h] = R[k];
		k = k-h; //���Ƽ�¼��������ǰ����
      } while(k>=0 && temp<R[k]);
      R[k+h] = temp;	 //����R[j]
    }
}
void ShellSort(int R[],int n) 
{
   int i;
   for(i = n/2; i>0; i = i/2) //���˲�������
   ShellInsert(R,n,i); 
}

/*
void ShellSort(int R[], int n, int dlta[], int t) 
{
   int i;
   for(i = 0; i<t; i++) //���˲�������
   ShellInsert(R,n,dlta[i]); 
}*/

/** 
 �㷨ʵ�֣�
 �����ݱ�ֱ���ã�ÿ����¼��������Ϊ��ֵ�����ݣ�������������ԭ�򣬴�������ɨ�裬
 Υ����ԭ��������ݣ����ϡ�Ʈ��������˷�����ֱ���κ��������ݶ�����������Ϊֹ��
 
  * @brief     �Ľ���ð������ 
  * @attention ʱ�临�Ӷȣ���õ������Ҫ����ı������򣬱Ƚϴ���n-1,û�����ݽ���,ʱ�临�Ӷ�O(n)�� 
  *            ��������Ҫ����ı���������Ҫ�Ƚ�n(n-1)/2�Σ��������������ļ�¼�ƶ�����ʱ�临�Ӷ�ΪO(n^2).
  * �ȶ� 
  */  
void bubbleSort(int R[], int n)  
{  
    int i, j, temp;  
   	int flag = 1;  //flag������Ϊ���  
  
    for ( i = 0; i < n && flag; ++i ) {  
        flag = 0;  
        for ( j = n - 1; j > i; --j ) {  
            if (R[j] < R[j - 1]) { //�������Ʈ 
                temp = R[j];  
                R[j] = R[j - 1];  
                R[j - 1] = temp;  
                flag = 1;//��������ݽ�������flagΪtrue  
            }  
        }  
    }  
}
  
/**  
  * @brief ��Ȼ���������Ϊ���η��������η�����������Ȼ�޷��ܺõĸ������������ȫ�����衣 
  *        ����ҵĶԿ����������˽�һ����˵�����ڿ�����+���η��� 
  * @param RΪ�������飬low��highΪ������ 
  *        ʱ�临�Ӷȣ����O(nlogn),�O(n^2)��ƽ��O(nlogn)���ռ临�Ӷ�O(logn)�� 
  ���ȶ� 
*/ 

void quickSort(int *R, int left, int right)
{
    if(left >= right)/*�����ߵ�������ڻ��ߵ��ھʹ����Ѿ��������һ������*/
    {
        return ;
    }
    int i = left;
    int j = right;
    //int key = a[left]; /*������ݱ��������㷨O=n^2*/
    int key = R[(left+right)/2]; /*������ݱ��������㷨O=nlog(n)  ���������ģ�������������,����һ������*/
    R[(left+right)/2] = R[left];
	R[left] = key; //����Ҳ���Բ�Ҫ 
     
    while(i < j)                               /*�����ڵ�����Ѱ��һ��*/
    {
        while(i < j && key <= R[j])
        /*��Ѱ�ҽ������������ǣ�1���ҵ�һ��С����ߴ���key��������Сȡ����������
        ���ǽ���2��û�з��ϵ���i��j����*/ 
        {
            j--;/*��ǰѰ��*/
        }
         
        R[i] = R[j];
        /*�ҵ�һ������������Ͱ�������ǰ��ı����ߵ�i��ֵ�������һ��ѭ����key��
        a[0]����ô���Ǹ�key��*/
         
        while(i < j && key >= R[i])
        /*����i�ڵ�������ǰѰ�ң�ͬ�ϣ�����ע����key�Ĵ�С��ϵֹͣѭ���������෴��
        ��Ϊ����˼���ǰ����������ӣ������������ߵ�����С��key�Ĺ�ϵ�෴*/
        {
            i++;
        }
         
        R[j] = R[i];
    }
     
    R[i] = key;/*���ڵ���������һ���Ժ�Ͱ��м���key�ع�*/
    quickSort(R, left, i - 1);/*�����ͬ���ķ�ʽ�Էֳ�������ߵ�С�����ͬ�ϵ�����*/
    quickSort(R, i + 1, right);/*��ͬ���ķ�ʽ�Էֳ������ұߵ�С�����ͬ�ϵ�����*/
                       /*��Ȼ�����ܻ���ֺܶ�����ң�ֱ��ÿһ���i = j Ϊֹ*/
}

/** 
  * @brief �ϰ����ݽṹ ѡ������ 
  *        ����"ѡ������"�Գ���Ϊn�������������,ʱ�临�Ӷ���ã������O(n^2) 
  *        ����õ�ʱ�򣬽�������Ϊ0�Σ��Ƚϴ���Ϊn(n-1)/2 
  *        ����ʱ��Ҳ�ͳ�ʼ����ʱ����������Ϊn-1�Σ����յ�����ʱ���ǱȽ��뽻���Ĵ����ܺͣ� 
  *        �ܵ�ʱ�临�Ӷ���ȻΪO(n^2)
  * 
  *        ���ȶ� 
  */  
void selectSort(int R[], int n)  
{  
    int i, j, temp, index;  
    for ( i = 0; i < n-1; ++i ) {  
        index = i;  
        for ( j = i + 1; j < n; ++j ) {  
            if ( R[index] > R[j] ) {  
                index = j;//index�д�Źؼ�����С��¼���±�  
            }  
        }  
        if (index != i) {  
            temp = R[i];  
            R[i] = R[index];  
            R[index] = temp;  
        }  
    }  
} 

/** 
  * @brief     ���� �󶥶� 
  * @attention ���˰汾�������� 
  */  
  
//start Ϊԭ���ڵ㣬end �ڵ��������������Ϊ[start,end]��Ϊstart����Ľڵ� 
void heapAdjust(int R[], int start, int end)  
{  
    int j, temp;  
    temp = R[start];  //������������ԭ�����
    //���ڸ��ڵ��Ǵ�0��ʼ������j������Ϊ 2*j+1���Һ���Ϊ2*j+2 
    for ( j = 2 * start + 1; j <= end; j = j * 2 + 1 ) {  
          
        if ( j < end && R[j] < R[j + 1] ) {  
            ++j;  //�Һ��ӱȽϴ� jָ��R[i]���Һ���
        }  
        if ( temp >  R[j] ) {   // �������ӣ��Ѷѣ��������� 
            break;  
        }  
        R[start] = R[j];  
        start = j;  
    }  
    R[start] = temp;  //ԭ����������ȷλ��
}  

//ʹ�õݹ������ 
void heapAdjust2(int R[],int start,int end) 
{
   int j, temp;
   if(start >= end) return;	//ֻ��һ��Ԫ�ػ���Ԫ��
   j = 2*start +1; 			//jָ��R[i]������
   if(j > end) return;  //�޺��ӣ���Ҷ��
   if(j < end && R[j]<R[j+1]) 
       j++; //jָ��R[i]���Һ���
   if(R[start] >= R[j]) 
       return;  //����������󣬲���
   temp = R[j];
   R[j] = R[start];
   R[start] = temp;  //����R[j]��R[i]��temp������
   heapAdjust2(R, j, end);	//�ݹ�
}

  
/** 
  * @brief ������ 
  * @param RΪ����������飬sizeΪ����ĳ��� 
  *  ʱ�临�Ӷ�:������(С)���ѣ���ȫ�������ĸ߶�Ϊlog(n+1)����˶�ÿ����������ʱ�临�Ӷ�ΪO(logn) 
  *           ����ѭ������һ��ѭ�����Ĳ�������Ϊn/2���ڶ�����������Ϊ(n-1)�����ʱ�临�Ӷ�ΪO(nlogn) 
  */  
void heapSort(int R[], int size)  
{  
    int i, temp;  
    for ( i = size / 2 - 1; i >= 0; --i ) {  //ǰsize/2��Ϊ��Ҷ�ӽڵ� 
        heapAdjust2(R, i, size -1);  //����ʼ��
    }  
    for ( i = size - 1; i >=1; --i ) { //����n-1�˶�����,���ؽ���,R[0]��󣬷ŵ�������½��� 
        temp = R[i];  
        R[i] = R[0];  
        R[0] = temp;//��β�ͱ��׵�Ԫ�ؽ���  
        heapAdjust(R, 0, i - 1);//�ѱ��׵�Ԫ�ػ��ɱ�β��Ԫ�غ����¹��ɴ󶥶ѣ���Ϊ�����׵�Ԫ���⣬  
                                //����Ľ�㶼����󶥶ѵ���������heapAdjust()�ĵڶ�������ֻ��Ϊ0  
    }  
}   

/** 
  * @brief ������ĳ���Ϊn������a[]�ͳ���Ϊm��b[]�鲢Ϊ���������c[] 
  *        ֻҪ�ӱȽ϶������еĵ�һ������˭С����ȡ˭��ȡ��֮���ڶ�Ӧ��������ɾ��������� 
  *        Ȼ���ٽ��бȽϣ����������Ϊ�գ���ֱ�ӽ���һ�����е���������ȡ�����ɡ� 
  *        ��������������a[first...mid]��a[mid...last]�ϲ� 
  */  
void mergeArray(int a[], int first, int mid, int last, int tmp[])  
{  
    int i = first, j = mid + 1;  
    int k = 0;  
    while ( i <= mid && j <= last ) {  
        if ( a[i] <= a[j] )  
            tmp[k++] = a[i++];  
        else  
            tmp[k++] = a[j++];  
    }  
    while ( i <= mid ) {  
        tmp[k++] = a[i++];  
    }  
    while ( j <= last ) {  
        tmp[k++] = a[j++];  
    }  
    for (i = 0; i < k; i++) {//����ǧ���ܶ������  
        a[first + i] = tmp[i];  
    }  
}  
/** 
  * @brief �鲢������Ļ���˼·���ǽ�����ֳɶ���A��B�������������ڵ����ݶ�������ģ� 
  *        ��ô�Ϳ��Ժܷ���Ľ���������ݽ������������������������������ˣ� 
 
  *        ���Խ�A��B������ٷֳɶ��顣�������ƣ����ֳ�����С��ֻ��һ������ʱ�� 
  *        ������Ϊ���С�������Ѿ��ﵽ������Ȼ���ٺϲ����ڵĶ���С��Ϳ����ˡ�����ͨ���� (�ݹ�) �ķֽ����У� 
  *        �� (�ϲ�) ���о�����˹鲢���� 
  */  
void mergeSort(int a[], int first, int last, int tmp[])  
{  
    int mid;  
    if ( first < last ) {  
        mid = ( first + last ) / 2;  
        mergeSort(a, first, mid, tmp);  //�������  
        mergeSort(a, mid + 1, last, tmp);   //�ұ�����  
        mergeArray(a, first, mid, last, tmp);  
    }  
} 

/*
//һ�¹鲢�����㷨������ε�����ݽṹ 
void Merge (int SR[], int TR[], int i, int m, int n) {
   // �㷨10.12
   // �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
   int j,k;
   for (j=m+1, k=i;  i<=m && j<=n;  ++k) {   
      // ��SR�м�¼��С����ز���TR
      if LQ(SR[i].key,SR[j].key) TR[k] = SR[i++];
      else TR[k] = SR[j++];
   }
   if (i<=m)  // TR[k..n] = SR[i..m];  ��ʣ���SR[i..m]���Ƶ�TR
      while (k<=n && i<=m) TR[k++]=SR[i++];
   if (j<=n)  // ��ʣ���SR[j..n]���Ƶ�TR
      while (k<=n &&j <=n) TR[k++]=SR[j++];
      
   for (j = 0; j < k; j++) {//����ǧ���ܶ������  
        SR[i + j] = TR[j];  
    }
} // Merge

//ʹ�õݹ鷽������ʽ��࣬��ʵ���Բ��� 
void MSort(int SR[], int s, int t, int TR1[]) { // �㷨10.13
   // ��SR[s..t]�鲢����ΪTR1[s..t]��
   int m;
   int TR2[20];
   if (s==t) TR1[t] = SR[s];
   else {
      m=(s+t)/2;            // ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
      MSort(SR,TR2,s,m);    // �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
      MSort(SR,TR2,m+1,t);  // ��SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
      Merge(TR2,TR1,s,m,t); // ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
   }
} // MSort
*/

double diff_time(struct timeval tv_begin, struct timeval tv_end)
{
	double end_d = tv_end.tv_sec + tv_end.tv_usec / 1000000.0;
	double begin_d = tv_begin.tv_sec + tv_begin.tv_usec / 1000000.0;
	return end_d - begin_d;
}

int test_array(int *number, int n, char *algorithm)
{
	int i, j;
	for(i = 0; i<n-1; i++)
	{
		if(number[i] > number[i + 1])
			{
				printf("the algorithm %s is wrong\n",algorithm);
				printf("output array is :\n");
				for(j=0; j<n; j++)
				{
					printf("%d  ",number[j]);
				} 
				return -1;	
			}
	}
	return 0;
}
int test_algorithm()
{
	int len[]={1, 2, 10, 100, 200, 300, 400, 500, 600, 1000};
	int num=sizeof(len) / sizeof(int);
	int i, j, *number_rand, *number_order, *temp, *number_test;

	for(i = 0; i < num; i++)
	{
		number_rand = calloc(sizeof(int), len[i]);
		number_order = calloc(sizeof(int), len[i]);
		number_test = calloc(sizeof(int), len[i]);
		temp = calloc(sizeof(int), len[i]);
		for (j = 0; j<len[i]; j++)
		{
			*(number_rand + j) = rand() * 1000 + rand();
			*(number_order + j) = j;
		}
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		quickSort(number_test, 0, len[i] - 1);
		test_array(number_test, len[i], "quickSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		quickSort(number_test, 0, len[i] - 1);
		test_array(number_test, len[i], "quickSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		mergeSort(number_test, 0, len[i]-1, temp);
		test_array(number_test, len[i], "mergeSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		mergeSort(number_test, 0, len[i]-1, temp);
		test_array(number_test, len[i], "mergeSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		insertSort(number_test, len[i]);
		test_array(number_test, len[i], "insertSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		insertSort(number_test, len[i]);
		test_array(number_test, len[i], "insertSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		ShellSort(number_test, len[i]);
		test_array(number_test, len[i], "ShellSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		ShellSort(number_test, len[i]);
		test_array(number_test, len[i], "ShellSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		bubbleSort(number_test, len[i]);
		test_array(number_test, len[i], "bubbleSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		bubbleSort(number_test, len[i]);
		test_array(number_test, len[i], "bubbleSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		selectSort(number_test, len[i]);
		test_array(number_test, len[i], "selectSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		selectSort(number_test, len[i]);
		test_array(number_test, len[i], "selectSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		heapSort(number_test, len[i]);
		test_array(number_test, len[i], "heapSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		heapSort(number_test, len[i]);
		test_array(number_test, len[i], "heapSort");
		
		memcpy(number_test, number_rand, sizeof(int) * len[i]);
		binSort(number_test, len[i]);
		test_array(number_test, len[i], "binSort");
		
		memcpy(number_test, number_order, sizeof(int) * len[i]);
		binSort(number_test, len[i]);
		test_array(number_test, len[i], "binSort");

	}
	printf("test algorithm finish\n");
	free(number_rand);
	free(number_order);
	free(temp);
	free(number_test);
}

int main()
{
	int len[]={10,100,1000,10000,100000,1000000};
	int num=sizeof(len) / sizeof(int);
	int i, j, *number_rand, *number_order, *temp, *number_test;
	struct timeval tv_begin, tv_end;
	double diff ;
	test_algorithm();
//	for(i = 0; i < num; i++)
//	{
//		printf("%d\n", len[i]);
//		number_rand = calloc(sizeof(int), len[i]);
//		number_order = calloc(sizeof(int), len[i]);
//		number_test = calloc(sizeof(int), len[i]);
//		temp = calloc(sizeof(int), len[i]);
//		for (j = 0; j<len[i]; j++)
//		{
//			*(number_rand + j) = rand() * 1000 + rand();
//			//*(number_order + j) = j;
//			*(number_order + j) = len[i] - j; //���� 
//		}
//		printf("\nthe array length is %d\n",len[i]);
//		
//		printf("quickSort:\n");	
//		memcpy(number_test, number_rand, sizeof(int) * len[i]);
//		gettimeofday(&tv_begin, NULL);
//		quickSort(number_test, 0, len[i] - 1);
//		gettimeofday(&tv_end, NULL);
//		diff = diff_time(tv_begin, tv_end);
//		printf("rand number: %f\n",diff);
//		
//		memcpy(number_test, number_order, sizeof(int) * len[i]);
//		gettimeofday(&tv_begin, NULL);
//		quickSort(number_test, 0, len[i] - 1);
//		gettimeofday(&tv_end, NULL);
//		diff = diff_time(tv_begin, tv_end);
//		printf("order number: %f\n",diff);
//		
//		printf("MergeSort:\n");	
//		memcpy(number_test, number_rand, sizeof(int) * len[i]);
//		gettimeofday(&tv_begin, NULL);
//		mergeSort(number_test, 0, len[i]-1, temp);
//		gettimeofday(&tv_end, NULL);
//		diff = diff_time(tv_begin, tv_end);
//		printf("rand number: %f\n",diff);
//		
//		memcpy(number_test, number_order, sizeof(int) * len[i]);
//		gettimeofday(&tv_begin, NULL);
//		mergeSort(number_test, 0, len[i]-1, temp);
//		gettimeofday(&tv_end, NULL);
//		diff = diff_time(tv_begin, tv_end);
//		printf("order number: %f\n",diff);
//		
//		free(number_rand);
//		free(number_order);
//		free(temp);
//		free(number_test);
//		
//	}


	return 0;
}

