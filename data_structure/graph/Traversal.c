#ifdef __cplusplus
extern "C"{
#endif
/*

               0---1
               |  /|\
               | / | 2
               |/  |/
               4---3

*/


 
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define OK 1
#define ok 1
#define ERROR 0
#define error 0

// Structure for Queue
typedef int QElemType;  
typedef int Status; 
typedef int bool;  

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

 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest; //顶点名
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;  //顶点数
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;//顶点数
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
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
    return OK;
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

  

//广度优先遍历 Breadth First Traversal
void BFSTraverse(struct Graph* graph)
{
    int s;
    bool *visited = (bool *)malloc(sizeof(bool)*graph->V);
    // Create a queue for BFS
    LinkQueue queue; 
    InitQueue(&queue); 
 

    for (s = 0; s < graph->V; ++s)
    {
        if(!visited[s])
        {
            visited[s] = true;
            EnQueue(&queue, s);
        }
     
        while(!IsEmpty(queue))
        {
            // Dequeue a vertex from queue and print it
            DEQueue(&queue, &s);
            printf("%d ",s);
     
            // Get all adjacent vertices of the dequeued vertex s
            // If a adjacent has not been visited, then mark it visited
            // and enqueue it
            struct AdjListNode* node_p = graph->array[s].head;
            while (node_p)
            {
                if(!visited[node_p->dest])
                {
                    visited[node_p->dest] = true;
                    EnQueue(&queue, node_p->dest);
                }
                node_p = node_p->next;
            }
        }
    }
}

    
//深度优先遍历 Depth First Traversal
void DFS(struct Graph* graph, int s, bool *visited)
{
    //先访问自己
    visited[s] = true;
    printf("%d ",s);
    struct AdjListNode* node_p = graph->array[s].head;
    while (node_p)
    {
        if(!visited[node_p->dest])
        {
            DFS(graph, node_p->dest, visited);
        }
        node_p = node_p->next;
    }
}

void DFSTraverse(struct Graph* graph)
{
    int v;
    bool *visited = (bool *)malloc(sizeof(bool)*graph->V);
    for(v = 0; v < graph->V; v++)
        visited[v] = false;
    for (v = 0; v < graph->V; ++v)
    {
        if(!visited[v])
        {
            DFS(graph, v, visited);
        }
    }
    free(visited);
}
 
// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 6;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
 
    // print the adjacency list representation of the above graph
    printGraph(graph);
    printf("Breadth First Traversal for a Graph\n");
    BFSTraverse(graph);
    //printf("\nDepth First Traversal for a Graph start with 2\n");
    //DFS(graph, 2);
    //printf("\nDepth First Traversal for a Graph start with 0\n");
    //DFS(graph, 0);
    printf("\nDepth First Traversal for a Graph\n");
    DFSTraverse(graph);
 
    return 0;
}

/*
 Adjacency list of vertex 0
 head -> 4-> 1

 Adjacency list of vertex 1
 head -> 4-> 3-> 2-> 0

 Adjacency list of vertex 2
 head -> 3-> 1

 Adjacency list of vertex 3
 head -> 4-> 2-> 1

 Adjacency list of vertex 4
 head -> 3-> 1-> 0
*/


#ifdef __cplusplus
}
#endif
