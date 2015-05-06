#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>

/*
插入排序(直插排序、二分排序、希尔排序)
交换排序(冒泡排序、快速排序)
选择排序 (直选排序、树型排序、堆排序)
归并排序(二路归并排序、多路归并排序)
分配排序(多关键字排序、基数排序)
*/ 

/*
 类别    排序方法        时间复杂度                 空间复杂度     稳定性 
                     平均       最好      最坏      辅助存储 
插入排序  直接插入   O(n^2)     O(n)     O(n^2)       O(1)          稳定 
插入排序  shell插入  O(n^1.3)   O(n)     O(n^2)       O(1)          不稳定
选择排序  直接选择   O(n^2)    O(n^2)    O(n^2)       O(1)          不稳定
选择排序  堆排序    O(nlogn)  O(nlogn)   O(nlogn)     O(1)          不稳定
交换排序  冒泡排序  O(n^2)     O(n)      O(n^2)       O(1)          稳定
交换排序  快速排序  O(nlogn)  O(nlogn)   O(n^2)       O(nlogn)      不稳定
归并排序  归并排序  O(nlogn)  O(nlogn)   O(nlogn)     O(1)          稳定
基数排序  基数排序  O(d(r+n)) O(d(rd+n)) O(d(r+n))    O(rd+n)       稳定 

r代表关键字的基数，d代表长度， 
*/



/** 
  *插入排序 
  *算法实现：无序区第一记录R[i] 插入有序区R[1]~R[i-1]，找插入位置和移动记录交替
  *进行：从有序区的后部j开始，如果该位置记录大于待插记录，则后移一位；待插记录插
  *入到最后空出的位置上。 
 
  * @brief 严版数据结构书代码 
  *        最好的情况,数组本身有序，就只需执行n-1次比较，此时时间复杂度为O(n); 
  *        最坏的情况，数组本身逆序，要执行n(n-1)/2次，此时时间复杂度为O(n^2); 
  *        稳定 
  */  
void insertSort(int R[], int n)  
{  
    int i, j, key;  
    for ( i = 1; i < n; ++i ) {  
        if ( R[i] < R[i - 1] ) {//将R[i]插入有序字表  
            key = R[i];        //可以R[0]不用，用作哨兵  
            for ( j = i - 1; R[j] > key && j>=0; --j ) {  
                R[j+1] = R[j];  
            }  
            R[j+1] = key;  
        }  
    }  
}

/*
二分排序:
在插入第i个元素时，对前面的0～i-1元素进行折半，先跟他们 中间的那个元素比，
如果小，则对前半再进行折半，否则对后半 进行折半，直到left>right，然后再把第i
个元素前1位与目标位置之间 的所有元素后移，再把第i个元素放在目标位置上。
 
二分法排序最重要的一个步骤就是查找要插入元素的位置，也就是要在哪一个位置上放我
们要准备排序的这个元素。当我们查找到位置以后就很好说了，和插入排序一样，将这个
位置以后的所有元素都向后移动一位。这样就实现了二分法排序。

平均时间O(n^2)
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
        while (start <= end)  //循环结束时 end = start-1 
        {
            mid = (start + end) / 2;
            if (R[mid] > temp)//要排序元素在已经排过序的数组左边
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
        for (j = i - 1; j > end; j--)//找到了要插入的位置，然后将这个位置以后的所有元素向后移动

        {
            R[j + 1] = R[j];
        }
        R[end] = temp;  //end + 1 = start 
    }
}


/*
shell排序 
算法实现：
数据表分成若干组，相隔为某个“增量”的记录为一组，各组内直接插入排序；初始增量d1
较大，分组较多(每组的记录数少)，以后增量逐渐减少，分组减少(每组的记录数增多)，直
到最后增量为1(d1>d2>…>dt=1)，所有记录放为同一组，再整体进行一次直接插入排序。

时间：O(nlog2n)和O(n2)之间，比如O(n1.3) ，优于直接插入
不稳定 
*/

void ShellInsert(int R[],int n,int h) {
//一趟插入排序，h为本趟增量
  int i,j,k,temp;
  for(i=0; i<=h-1; i++)		 //i为组号
    for(j=i+h; j<n; j+=h) {//每组从第2个记录开始插入
      if(R[j] >= R[j-h]) continue;
      temp = R[j];	//保存待插记录，但不是监视哨
      k = j-h;		//待插记录的前一个记录
      do {		     //查找插入位置
        R[k+h] = R[k];
		k = k-h; //后移记录，继续向前搜索
      } while(k>=0 && temp<R[k]);
      R[k+h] = temp;	 //插入R[j]
    }
}
void ShellSort(int R[],int n) 
{
   int i;
   for(i = n/2; i>0; i = i/2) //各趟插入排序
   ShellInsert(R,n,i); 
}

/*
void ShellSort(int R[], int n, int dlta[], int t) 
{
   int i;
   for(i = 0; i<t; i++) //各趟插入排序
   ShellInsert(R,n,dlta[i]); 
}*/

/** 
 算法实现：
 设数据表垂直放置，每个记录看作重量为键值的气泡；根据轻上重下原则，从下往上扫描，
 违反本原则的轻气泡，向上“飘浮”，如此反复，直到任何两个气泡都是轻上重下为止。
 
  * @brief     改进的冒泡排序 
  * @attention 时间复杂度，最好的情况，要排序的表本身有序，比较次数n-1,没有数据交换,时间复杂度O(n)。 
  *            最坏的情况，要排序的表本身逆序，需要比较n(n-1)/2次，并做等数量级的记录移动，总时间复杂度为O(n^2).
  * 稳定 
  */  
void bubbleSort(int R[], int n)  
{  
    int i, j, temp;  
   	int flag = 1;  //flag用来作为标记  
  
    for ( i = 0; i < n && flag; ++i ) {  
        flag = 0;  
        for ( j = n - 1; j > i; --j ) {  
            if (R[j] < R[j - 1]) { //轻的向上飘 
                temp = R[j];  
                R[j] = R[j - 1];  
                R[j - 1] = temp;  
                flag = 1;//如果有数据交换，则flag为true  
            }  
        }  
    }  
}
  
/**  
  * @brief 虽然快速排序称为分治法，但分治法这三个字显然无法很好的概括快速排序的全部步骤。 
  *        因此我的对快速排序作了进一步的说明：挖坑填数+分治法： 
  * @param R为待排数组，low和high为无序区 
  *        时间复杂度：最好O(nlogn),最坏O(n^2)，平均O(nlogn)，空间复杂度O(logn)； 
  不稳定 
*/ 

void quickSort(int *R, int left, int right)
{
    if(left >= right)/*如果左边的数组大于或者等于就代表已经整理完成一个组了*/
    {
        return ;
    }
    int i = left;
    int j = right;
    //int key = a[left]; /*如果数据本身有序，算法O=n^2*/
    int key = R[(left+right)/2]; /*如果数据本身有序，算法O=nlog(n)  不能这样改，加上下面两行,交换一下数据*/
    R[(left+right)/2] = R[left];
	R[left] = key; //这行也可以不要 
     
    while(i < j)                               /*控制在当组内寻找一遍*/
    {
        while(i < j && key <= R[j])
        /*而寻找结束的条件就是，1，找到一个小余或者大于key的数（大小取决于你想升
        序还是降序）2，没有符合的切i与j相遇*/ 
        {
            j--;/*向前寻找*/
        }
         
        R[i] = R[j];
        /*找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
        a[0]，那么就是给key）*/
         
        while(i < j && key >= R[i])
        /*这是i在当组内向前寻找，同上，不过注意与key的大小关系停止循环和上面相反，
        因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反*/
        {
            i++;
        }
         
        R[j] = R[i];
    }
     
    R[i] = key;/*当在当组内找完一遍以后就把中间数key回归*/
    quickSort(R, left, i - 1);/*最后用同样的方式对分出来的左边的小组进行同上的做法*/
    quickSort(R, i + 1, right);/*用同样的方式对分出来的右边的小组进行同上的做法*/
                       /*当然最后可能会出现很多分左右，直到每一组的i = j 为止*/
}

/** 
  * @brief 严版数据结构 选择排序 
  *        采用"选择排序"对长度为n的数组进行排序,时间复杂度最好，最坏都是O(n^2) 
  *        当最好的时候，交换次数为0次，比较次数为n(n-1)/2 
  *        最差的时候，也就初始降序时，交换次数为n-1次，最终的排序时间是比较与交换的次数总和， 
  *        总的时间复杂度依然为O(n^2)
  * 
  *        不稳定 
  */  
void selectSort(int R[], int n)  
{  
    int i, j, temp, index;  
    for ( i = 0; i < n-1; ++i ) {  
        index = i;  
        for ( j = i + 1; j < n; ++j ) {  
            if ( R[index] > R[j] ) {  
                index = j;//index中存放关键码最小记录的下标  
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
  * @brief     构建 大顶堆 
  * @attention 个人版本，堆排序 
  */  
  
//start 为原根节点，end 节点数，参与调整的为[start,end]中为start子孙的节点 
void heapAdjust(int R[], int start, int end)  
{  
    int j, temp;  
    temp = R[start];  //辅助量，保存原根结点
    //由于根节点是从0开始，所以j的左孩子为 2*j+1，右孩子为2*j+2 
    for ( j = 2 * start + 1; j <= end; j = j * 2 + 1 ) {  
          
        if ( j < end && R[j] < R[j + 1] ) {  
            ++j;  //右孩子比较大 j指向R[i]的右孩子
        }  
        if ( temp >  R[j] ) {   // 根＞孩子，已堆，调整结束 
            break;  
        }  
        R[start] = R[j];  
        start = j;  
    }  
    R[start] = temp;  //原根结点放入正确位置
}  

//使用递归调整堆 
void heapAdjust2(int R[],int start,int end) 
{
   int j, temp;
   if(start >= end) return;	//只有一个元素或无元素
   j = 2*start +1; 			//j指向R[i]的左孩子
   if(j > end) return;  //无孩子，即叶子
   if(j < end && R[j]<R[j+1]) 
       j++; //j指向R[i]的右孩子
   if(R[start] >= R[j]) 
       return;  //待调点已最大，不调
   temp = R[j];
   R[j] = R[start];
   R[start] = temp;  //交换R[j]和R[i]，temp作辅助
   heapAdjust2(R, j, end);	//递归
}

  
/** 
  * @brief 堆排序 
  * @param R为待排序的数组，size为数组的长度 
  *  时间复杂度:构建大(小)顶堆，完全二叉树的高度为log(n+1)，因此对每个结点调整的时间复杂度为O(logn) 
  *           两个循环，第一个循环做的操作次数为n/2，第二个操作次数为(n-1)，因此时间复杂度为O(nlogn) 
  */  
void heapSort(int R[], int size)  
{  
    int i, temp;  
    for ( i = size / 2 - 1; i >= 0; --i ) {  //前size/2个为非叶子节点 
        heapAdjust2(R, i, size -1);  //建初始堆
    }  
    for ( i = size - 1; i >=1; --i ) { //进行n-1趟堆排序,堆重建后,R[0]最大，放到最后，重新建堆 
        temp = R[i];  
        R[i] = R[0];  
        R[0] = temp;//表尾和表首的元素交换  
        heapAdjust(R, 0, i - 1);//把表首的元素换成表尾的元素后，重新构成大顶堆，因为除表首的元素外，  
                                //后面的结点都满足大顶堆的条件，故heapAdjust()的第二个参数只需为0  
    }  
}   

/** 
  * @brief 将有序的长度为n的数组a[]和长度为m的b[]归并为有序的数组c[] 
  *        只要从比较二个数列的第一个数，谁小就先取谁，取了之后在对应的数列中删除这个数。 
  *        然后再进行比较，如果有数列为空，那直接将另一个数列的数据依次取出即可。 
  *        将两个有序序列a[first...mid]和a[mid...last]合并 
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
    for (i = 0; i < k; i++) {//这里千万不能丢了这个  
        a[first + i] = tmp[i];  
    }  
}  
/** 
  * @brief 归并排序，其的基本思路就是将数组分成二组A，B，如果这二组组内的数据都是有序的， 
  *        那么就可以很方便的将这二组数据进行排序。如何让这二组组内数据有序了？ 
 
  *        可以将A，B组各自再分成二组。依次类推，当分出来的小组只有一个数据时， 
  *        可以认为这个小组组内已经达到了有序，然后再合并相邻的二个小组就可以了。这样通过先 (递归) 的分解数列， 
  *        再 (合并) 数列就完成了归并排序。 
  */  
void mergeSort(int a[], int first, int last, int tmp[])  
{  
    int mid;  
    if ( first < last ) {  
        mid = ( first + last ) / 2;  
        mergeSort(a, first, mid, tmp);  //左边有序  
        mergeSort(a, mid + 1, last, tmp);   //右边有序  
        mergeArray(a, first, mid, last, tmp);  
    }  
} 

/*
//一下归并排序算法来自严蔚敏数据结构 
void Merge (int SR[], int TR[], int i, int m, int n) {
   // 算法10.12
   // 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
   int j,k;
   for (j=m+1, k=i;  i<=m && j<=n;  ++k) {   
      // 将SR中记录由小到大地并入TR
      if LQ(SR[i].key,SR[j].key) TR[k] = SR[i++];
      else TR[k] = SR[j++];
   }
   if (i<=m)  // TR[k..n] = SR[i..m];  将剩余的SR[i..m]复制到TR
      while (k<=n && i<=m) TR[k++]=SR[i++];
   if (j<=n)  // 将剩余的SR[j..n]复制到TR
      while (k<=n &&j <=n) TR[k++]=SR[j++];
      
   for (j = 0; j < k; j++) {//这里千万不能丢了这个  
        SR[i + j] = TR[j];  
    }
} // Merge

//使用递归方法，形式简洁，但实用性不好 
void MSort(int SR[], int s, int t, int TR1[]) { // 算法10.13
   // 将SR[s..t]归并排序为TR1[s..t]。
   int m;
   int TR2[20];
   if (s==t) TR1[t] = SR[s];
   else {
      m=(s+t)/2;            // 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
      MSort(SR,TR2,s,m);    // 递归地将SR[s..m]归并为有序的TR2[s..m]
      MSort(SR,TR2,m+1,t);  // 将SR[m+1..t]归并为有序的TR2[m+1..t]
      Merge(TR2,TR1,s,m,t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
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
//			*(number_order + j) = len[i] - j; //反序 
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

