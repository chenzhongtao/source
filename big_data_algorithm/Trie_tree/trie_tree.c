#ifdef __cplusplus
extern "C"{
#endif

/*
键树又称为数字查找树（Digital Search Tree)或Trie树(trie为retrieve(检索)中间4个字符)，
单词查找树,字典树，其结构受启发于一部大型字典的“书边标目”。
优点是：利用字符串的公共前缀来减少查询时间，最大限度地减少无谓的字符串比较，查询效率比哈希树高。
其高效率是以空间为代价的

Trie is an efficient information retrieval data structure. Using trie, search 
complexities can be brought to optimal limit (key length). If we store keys in 
binary search tree, a well balanced BST will need time proportional to M * log N, 
where M is maximum string length and N is number of keys in tree. Using trie, we 
can search the key in O(M) time. However the penalty is on trie storage requirements.
Insert and search costs O(key_length), however the memory requirements of trie is 
O(ALPHABET_SIZE * key_length * N) where N is number of keys in trie. There are 
efficient representation of trie nodes (e.g. compressed trie, ternary search tree, etc.) 
to minimize memory requirements of trie.

The following picture explains construction of trie using keys given in the example below,
                       root
                    /   \    \
                    t   a     b
                    |   |     |
                    h   n     y
                    |   |  \  |
                    e   s  y  e
                 /  |   |
                 i  r   w
                 |  |   |
                 r  e   e
                        |
                        r

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define FREE(p) \
    free(p);    \
    p = NULL;
 
// trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;
    trie_node_t *children[ALPHABET_SIZE];
};
 
// trie ADT
typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};
 
// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{
    trie_node_t *pNode = NULL;
 
    pNode = (trie_node_t *)malloc(sizeof(trie_node_t));
 
    if( pNode )
    {
        int i;
 
        pNode->value = 0;
 
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }
 
    return pNode;
}
 
// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
    pTrie->root = getNode();
    pTrie->count = 0;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;
 
    pTrie->count++;
    pCrawl = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
        if( !pCrawl->children[index] )
        {
            pCrawl->children[index] = getNode();
        }
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
   // pCrawl->value = pTrie->count;
   pCrawl->value += 1;
}
 
// Returns non zero, if key presents in trie
// 没出现返回0，出现返回1
int search(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;
 
    pCrawl = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if( !pCrawl->children[index] )
        {
            return 0;
        }
 
        pCrawl = pCrawl->children[index];
    }
 
    return (0 != pCrawl && pCrawl->value);
}

// 查找出现的次数
int search_value(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;
 
    pCrawl = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if( !pCrawl->children[index] )
        {
            return 0;
        }
 
        pCrawl = pCrawl->children[index];
    }
 
    if (0 != pCrawl)
        return  pCrawl->value;
    else
        return 0;
}

int leafNode(trie_node_t *pNode)
{
    return (pNode->value != 0);
}
 
int isItFreeNode(trie_node_t *pNode)
{
    int i;
    for(i = 0; i < ALPHABET_SIZE; i++)
    {
        if( pNode->children[i] )
            return 0;
    }
 
    return 1;
}

int deleteHelper(trie_node_t *pNode, char key[], int level, int len)
{
    if( pNode )
    {
        // Base case
        if( level == len )
        {
            if( pNode->value )
            {
                // Unmark leaf node
                pNode->value = 0;

                // If empty, node to be deleted
                if( isItFreeNode(pNode) )
                {
                    return 1;
                }

                return 0;
            }
        }
        else // Recursive case 递归方式
        {
            int ind = index(key[level]);

            if( deleteHelper(pNode->children[ind], key, level+1, len) )
            {
                // last node marked, delete it
                FREE(pNode->children[ind]);

                // recursively climb up, and delete eligible nodes
                return ( !leafNode(pNode) && isItFreeNode(pNode) );
            }
        }
    }

    return 0;
}

void deleteKey(trie_t *pTrie, char key[])
{
    int len = strlen(key);

    if( len > 0 )
    {
        deleteHelper(pTrie->root, key, 0, len);
    }
}


 
// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any","the", "by", "bye", "their","the"};
    trie_t trie;
 
    char output[][32] = {"Not present in trie", "Present in trie"};
 
    initialize(&trie);
 
    // Construct trie
    for(int i = 0; i < ARRAY_SIZE(keys); i++)
    {
        insert(&trie, keys[i]);
    }
 
    // Search for different keys
    printf("%s --- %s count=%d\n", "the", output[search(&trie, "the")], search_value(&trie, "the") );
    printf("%s --- %s count=%d\n", "these", output[search(&trie, "these")], search_value(&trie, "these"));
    printf("%s --- %s count=%d\n", "their", output[search(&trie, "their")], search_value(&trie, "their"));
    printf("%s --- %s count=%d\n", "thaw", output[search(&trie, "thaw")], search_value(&trie, "thaw"));
 
    return 0;
}



#ifdef __cplusplus
}
#endif
