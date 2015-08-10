#ifdef __cplusplus
extern "C"{
#endif

/*
第一步、先对这批海量数据预处理，在O（N）的时间内用Hash表完成统计；
第二步、借助堆这个数据结构，找出Top K，时间复杂度为N‘logK。
即，借助堆结构，我们可以在log量级的时间内查找和调整/移动。因此，维护一个K大小的
小根堆，然后遍历所有数据，分别和根元素进行对比，如果元素比根元素大，就替换根元素
比重新调整堆，我们最终的时间复杂度是：O（N） + N'*O（logK）

第二步也可以用二分插入排序，比较第一个数，如果比第一个数大，把一个数删除，用二分法
找出要插入的位置，前面移位后插入。
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#define HASHLEN 101
#define WORDLEN 30
#define MAX  100000
#define DOMAIN 300
#define K 5
//Hash
typedef struct node
{
    char *word;
    int count;
    struct node *next;
}node,*node_ptr;
static node_ptr head[HASHLEN];
static node array[K];
//Hash
int hash_function(char *p)
{
    unsigned int value = 0;
    while (*p != '/0')
    {
        value = value * 31 + *p++;
        if (value > HASHLEN)
            value = value % HASHLEN;
    }
    return value;
}
//HASH
void append_word(char *str)
{
    int index = hash_function(str);
    node_ptr p = head[index];
    while (p != NULL)
    {
        if (strcmp(str, p->word) == 0)
        {
            (p->count)++;
            return;
        }
        p = p->next;
    }
    // 
    node_ptr q = (node_ptr)malloc(sizeof(node));
    q->count = 1;
    q->word = (char *)malloc(sizeof(str) + 1);
    strcpy(q->word, str);
//    q->word = str;
    q->next = head[index];
    head[index] = q;
}
//0~DOMAIN - 1MAX
void gen_data()
{
    FILE *fp = fopen("c://data1.txt", "w");
    assert(fp);
    int i = 0;
    srand((int)(time(0)));
    for (i = 0; i < MAX; i++)
    	fprintf(fp,"%d  ",rand()%DOMAIN);
    fclose(fp);
}
//:
void heapAdjust(node array[], int beginIndex, int endIndex, int index)
{
	int length = endIndex - beginIndex + 1;
	int largestIndex = index;
	int leftIndex = 2 * index + 1;     //0?
	int rightIndex = 2 * index + 2;
	if (leftIndex <= length - 1 && array[leftIndex].count <= array[largestIndex].count )
		{
			largestIndex = leftIndex;
		}
	if (rightIndex <= length - 1 && array[rightIndex].count <= array[largestIndex].count )
		{
			largestIndex = rightIndex;
		}
	if (largestIndex != index)
		{
			node temp = array[largestIndex];
			array[largestIndex] = array[index];
			array[index] = temp;
			heapAdjust (array, beginIndex, endIndex, largestIndex);
		}
}
//
void heapBuild (node array[], int len )
	{
		int i = 0;
		for (i = len/2 - 1; i >= 0; i --)
		{
			heapAdjust (array, 0, len - 1, i);
		}
	}

int main()
{
	gen_data();
	char str[WORDLEN];
//	char *str;
	int i;
	int cnt1 = 0;
	for (i = 0; i < HASHLEN; i++)
	   head[i] = NULL;
	FILE *fp_passage = fopen("c://data1.txt", "r");
	assert(fp_passage);
	while (fscanf(fp_passage, "%s", str) != EOF)
	{
	    cnt1++;
	    append_word(str);
	   }
	printf("the cnt1 is %d/n", cnt1);
	     fclose(fp_passage);
	     //Top K
	for(i = 0; i < HASHLEN; i++)
	{
		if(i < K - 1)
				array[i] = *head[i];
		else
			if(i == K - 1)
				{
				array[i] = *head[i];
				heapBuild(array,K);
				}
			else
			{
				if(array[0].count < head[i]->count)
				{
					array[0] = *head[i];
					heapAdjust(array,0,K - 1,0);
				}
			}
	}
	printf("the top K is as follows/n");
	for(i = 0; i < K; i++)
		 printf("%s , and its count is %d/n",array[i].word, array[i].count);
//	printf("the total number of word is %d",cnt);
	return 0;
}



#ifdef __cplusplus
}
#endif
