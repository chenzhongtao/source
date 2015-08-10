#ifdef __cplusplus
extern "C"{
#endif

// binary search tree

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include<stdlib.h>
 
struct node
{
    int key;
    struct node *left, *right;
};
 
// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
 
// A utility function to do inorder traversal of BST
// 中序遍历
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
 
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* root, int key)
{
    /* If the tree is empty, return a new node */
    if (root == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < root->key)
        root->left  = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);   

    /* return the (unchanged) node pointer */
    return root;
}

// C function to search a given key in a given BST
struct node* search(struct node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
       return root;
   
    // Key is greater than root's key
    if (root->key < key)
       return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. 
   查找二叉查找树的最小值*/
  
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            //递归算法，返回子树
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        // 右子树的最小值，为root的中序后继
        struct node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}


/* Returns true if a binary tree is a binary search tree */
// 效率不高
int isBST_2(struct node* node) 
{ 
  if (node == NULL) 
    return(true); 
     
  /* false if the max of the left is > than us */
  if (node->left!=NULL && maxValue(node->left) > node->data) 
    return(false); 
     
  /* false if the min of the right is <= than us */
  if (node->right!=NULL && minValue(node->right) < node->data) 
    return(false); 
   
  /* false if, recursively, the left or right is not a BST */
  if (!isBST(node->left) || !isBST(node->right)) 
    return(false); 
     
  /* passing all that, it's a BST */
  return(true); 
}


int isBSTUtil(struct node* node, int min, int max);

/* Returns true if the given tree is a binary search tree 
 (efficient version). */ 
int isBST(struct node* node) 
{ 
  return(isBSTUtil(node, INT_MIN, INT_MAX)); 
} 

/* Returns true if the given tree is a BST and its 
   values are >= min and <= max. */ 
int isBSTUtil(struct node* node, int min, int max) 
{ 

  /* an empty tree is BST */
  if (node==NULL) 
     return 1;
      
  /* false if this node violates the min/max constraint */  
  if (node->data < min || node->data > max) 
     return 0; 

  /* otherwise check the subtrees recursively, 
   tightening the min or max constraint */
  return 
    isBSTUtil(node->left, min, node->data-1) &&  // Allow only distinct values
    isBSTUtil(node->right, node->data+1, max);  // Allow only distinct values
} 


// This function finds predecessor and successor of key in BST.
// It sets pre and suc as predecessor and successor respectively
// 查找某个值对应的中序前驱和后记
void findPreSuc(struct node* root, struct node*& pre, struct node*& suc, int key)
{
    // Base case
    if (root == NULL)  return ;
 
    // If key is present at root
    if (root->key == key)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            struct node *tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
 
        // the minimum value in right subtree is successor
        if (root->right != NULL)
        {
            struct node *tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return ;
    }
 
    // If key is smaller than root's key, go to left subtree
    if (root->key > key)
    {
        // 左子树某节点的后继可能是root  中序是: 左子树 root 右子树
        suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else // go to right subtree
    {
        // 右子树某节点的前驱可能是root  中序是: 左子树 root 右子树
        pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}


/*  This function traverses tree in post order to 
    to delete each and every node of the tree */
void _destoryTree(struct node* node) 
{
    if (node == NULL) return;
 
    /* first delete both subtrees */
    _destoryTree(node->left);
    _destoryTree(node->right);
   
    /* then delete the node */
    printf("\n Deleting node: %d", node->key);
    free(node);
} 

/* Deletes a tree and sets the root as NULL */
void destoryTree(struct node** node_ref)
{
  _destoryTree(*node_ref);
  *node_ref = NULL;
}

// Driver Program to test above functions
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
 
    // print inoder traversal of the BST
    inorder(root); //20 30 40 50 60 70 80
    printf("\n");

    printf("Inorder traversal of the given tree \n");
    inorder(root);
 
    printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
 
    printf("\nDelete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
 
    printf("\nDelete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
 
    return 0;
 
    return 0;
}


#ifdef __cplusplus
}
#endif
