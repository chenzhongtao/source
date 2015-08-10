#ifdef __cplusplus
extern "C"{
#endif

/*
Red-Black Tree is a self-balancing Binary Search Tree (BST) where every node follows following rules.
RedBlackTree
1) Every node has a color either red or black.

2) Root of tree is always black.

3) There are no two adjacent red nodes (A red node cannot have a red parent or red child).

4) Every path from root to a NULL node has same number of black nodes.

5) 每个叶子节点（NIL）是黑色。 [注意：这里叶子节点，是指为空(NIL或NULL)的叶子节点！] 这点只是编程技巧吧，不要也可以

Why Red-Black Trees?
Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time where h is the 
height of the BST. The cost of these operations may become O(n) for a skewed Binary tree. If we make sure 
that height of the tree remains O(Logn) after every insertion and deletion, then we can guarantee an upper 
bound of O(Logn) for all these operations. The height of a Red Black tree is always O(Logn) where n is the 
number of nodes in the tree.

Comparison with AVL Tree
The AVL trees are more balanced compared to Red Black Trees, but they may cause more rotations during insertion 
and deletion. So if your application involves many frequent insertions and deletions, then Red Black trees should 
be preferred. And if the insertions and deletions are less frequent and search is more frequent operation, then 
AVL tree should be preferred over Red Black Tree.

红黑树与AVL的比较：
AVL是严格平衡树，因此在增加或者删除节点的时候，根据不同情况，旋转的次数比红黑树要多；
红黑是用非严格的平衡来换取增删节点时候旋转次数的降低；
所以简单说，如果你的应用中，搜索的次数远远大于插入和删除，那么选择AVL，如果搜索，
插入删除次数几乎差不多，应该选择RB。

How does a Red-Black Tree ensure balance?
A simple example to understand balancing is, a chain of 3 nodes is not possible in red black tree. We can try any combination of colors and see all of them violate Red-Black tree property.

A chain of 3 nodes is nodes is not possible in Red-Black Trees. 
Following are NOT Red-Black Trees
        30             30               30       
       / \            /  \             /  \
     20  NIL       20(r) NIL       20(r)   NIL
    / \             / \              /  \   
  10  NIL          10  NIL        10(r)  NIL  
Violates          Violates        Violates
Property 4.      Property 4       Property 3 

Following are different possible Red-Black Trees with above 3 keys
         20                           20
       /   \                        /   \
     10     30                 10(r)    30(r)
    /  \   /  \                 /  \    /  \
 NIL  NIL NIL NIL             NIL  NIL NIL NIL

From the above examples, we get some idea how Red-Black trees ensure balance. Following is an important fact about balancing in Red-Black Trees.

Every Red Black Tree with n nodes has height <= 2Log2(n+1)

This can be proved using following facts:
1) For a general Binary Tree, let k be the minimum number of nodes on all root to NULL paths, then n >= 2k – 1 (Ex. If k is 3, then n is atleast 7). This expression can also be written as k <= 2Log2(n+1)

2) From property 4 of Red-Black trees and above claim, we can say in a Red-Black Tree with n nodes, there is a root to leaf path with at-most Log2(n+1) black nodes.

3) From property 3 of Red-Black trees, we can claim that the number black nodes in a Red-Black tree is at least ? n/2 ? where n is total number of nodes.

From above 2 points, we can conclude the fact that Red Black Tree with n nodes has height <= 2Log2(n+1)

In this post, we introduced Red-Black trees and discussed how balance is ensured. The hard part is to maintain 
balance when keys are added and removed. We will soon be discussing insertion and deletion operations in coming posts on Red-Black tree.


Red Black Tree Insertion: 图形看 http://www.geeksforgeeks.org/red-black-tree-set-2-insert/

Color of a NULL node is considered as BLACK.
Let x be the newly inserted node.
1) Perform standard BST insertion and make the color of newly inserted nodes as RED. 
   将插入的节点着色为"红色"
2) Do following if color of x’s parent is not BLACK or x is not root.
   如何父亲节点是黑色，不用调整，如何x是root，把红色改为黑色
….a) If x’s uncle is RED (Grand parent must have been black from property 4)
       如何叔叔节点是红色的(祖父节点肯定是黑色的，性质4)
……..(i) Change color of parent and uncle as BLACK.
        把父亲节点和叔叔节点变为黑色
……..(ii) color of grand parent as RED.
        祖父节点变为红色
……..(iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
        此时祖父节点变成X,把祖父看成新插入的节点，重复步骤2,3(可能一直变色上去直到root节点，把root节点变为黑色就好，不用用到旋转，情况b要旋转)
….b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s
grandparent (g).
……..i) Left Left Case (p is left child of g and x is left child of p)
……..ii) Left Right Case (p is left child of g and x is right child of p)
……..iii) Right Right Case (Mirror of case a)
……..iv) Right Left Case (Mirror of case c)
3) If x is root, change color of x as BLACK (Black height of complete tree increases by 1).

All four cases when Uncle is BLACK

这里的旋转跟AVL数是一样的
a) Left Left Case

T1, T2, T3 , T4 and T5 are subtrees.
          g                                       p 
        /   \                                   /   \
      p(r)    u      Right Rotate (g)         x(r)   g(r)
      /  \   / \      - - - - - - - - ->      /  \   /  \ 
    x(r) T3 T4  T5  swap colors of g and p   T1  T2  T3  u
    / \                                                 /  \
  T1   T2                                              T4   T5
b) Left Right Case

      g                               g                                  x
    /   \                            /   \                             /   \
 p(r)    u     Left Rotate (p)     x(r)    u   apply left left case  p(r)   g(r)
  / \    / \   - - - - - - - - ->  /  \   / \   - - - - - - - ->     /  \   /  \ 
T1 x(r) T2 T3                    p(r) T3 T4  T5                     T1  T2  T3  u
    / \                          / \                                           /  \
  T2   T3                      T1   T2                                        T4   T5
c) Right Right Case

     g                                        p
   /  \                                     /   \ 
 u      p(r)     Left Rotate(g)          g(r)   x(r) 
/  \   /  \     - - - - - - - ->          / \    / \
T1 T2 T3  x (r) swap colors of g and p   u  T3 T4  T5
         / \                            / \
        T4  T5                        T1  T2
d) Right Left Case

     g                                g                                       x
   /    \                            /  \                                   /   \ 
  u      p(r)   Right Rotate (p)   u      x(r)   apply right right case  g(r)    p(r) 
 /  \    /  \ - - - - - - - - ->   /  \   /  \    - - - - - - - ->       / \     / \
T1 T2  x (r) T5                   T1 T2  T3   p(r)                      u  T3   T4  T5
        / \                                  /  \                       / \
      T3  T4                                T4   T5                    T1  T2



In this article, C code for insertion is discussed. Following is complete C code for insertion. 
Following are few important points for coding the insertion process.
1) Since we need to access uncle node to decide case, it is a good idea to have parent pointer in every node.
2) We also need to write functions for left and right rotations. These functions are similar to 
left and right rotations for AVL Tree insertion. In AVL Tree, we maintain height, but here we need to 
maintain parent pointer and color.




*/
#include<stdio.h>
#include<stdlib.h>
 
//A Red-Black tree node structure
struct node
{
    int data;     // for data part
    char color;  // for color property
 
    //links for left, right children and parent
    struct node *left, *right, *parent;
};
struct node Nil={.color = 'B'}; // null 节点为黑色
struct node *nil= &Nil; //为了避免讨论结点的边界情况，定义一个nil结点代替所有的NULL 
 
 /*
                y                               x
               / \     Right Rotation          /  \
              x   T3   – – – – – – – > T1   y 
             / \       < - - - - - - -            / \
            T1  T2     Left Rotation            T2  T3
 */
// Left Rotation
void LeftRotate(struct node **root,struct node *x)
{
    //y stored pointer of right child of x
    struct node *y = x->right;
 
    //store y's left subtree's pointer as x's right child
    x->right = y->left;
 
    //update parent pointer of x's right
    if (x->right != nil)
        x->right->parent = x;
 
    //update y's parent pointer
    y->parent = x->parent;
 
    // if x's parent is null make y as root of tree
    if (x->parent == nil)
        (*root) = y;
 
    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;
 
    // make x as left child of y
    y->left = x;
 
    //update parent pointer of x
    x->parent = y;
}
 
/*
            y                               x
           / \     Right Rotation          /  \
          x   T3   – – – – – – – > T1   y 
         / \       < - - - - - - -            / \
        T1  T2     Left Rotation            T2  T3
 */
// Right Rotation (Similar to LeftRotate)
void rightRotate(struct node **root,struct node *y)
{
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != nil)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == nil)
        (*root) = x; //成为root节点
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}
 
// Utility function to fixup the Red-Black tree after standard BST insertion
void insertFixUp(struct node **root,struct node *z)
{
    // iterate until z is not the root and z's parent color is red
    // 如果z为根节点或父亲节点为红色，什么也不用做
    while (z != *root && z->parent->color == 'R')
    {
        struct node *y;
         // 由于父节点为红色所以肯定有祖父节点，且祖父节点为黑色
        // Find uncle and store uncle in y 找出叔叔节点y
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;
 
        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (y->color == 'R')
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent; //祖父接点为要修复的节点
        }
 
        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
            }
 
            // Left-Right (LR) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            else if (z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent);
                rightRotate(root,z->parent);
            }
 
            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            else if (z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent->parent);
            }
 
            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            else if (z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                LeftRotate(root,z->parent);
            }
        }
    }
    (*root)->color = 'B'; //keep root always black
}
 
// Utility function to insert newly node in RedBlack tree
void insert(struct node **root, int data)
{
    // Allocate memory for new node
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = nil;
 
     //if root is null make z as root
    if (*root == NULL)
    {
        z->color = 'B';
        (*root) = z;
        //nil=(struct node*)malloc(sizeof(struct node)); 
        //nil->color=BLACK; //nil的颜色设置为黑 
        //z->left=nil; 
        //z->right=nil; 
        //z->parent=nil; 
    }
    else
    {
        struct node *y = NULL;
        struct node *x = (*root);
 
        // Follow standard BST insert steps to first insert the node
        while (x != nil)
        {
            y = x; //用y保存父节点
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (z->data > y->data)
            y->right = z;
        else
            y->left = z;
        z->color = 'R'; //插入的节点总是红色
 
        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(root,z);
    }
}
 
// A utility function to traverse Red-Black tree in inorder fashion
void inorder(struct node *root)
{
    if (root == nil)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
/* Drier program to test above function*/
int main()
{
    struct node *root = NULL;
    insert(&root,13);
    insert(&root,8);
    insert(&root,11);
    insert(&root,5);
    insert(&root,3);
    insert(&root,7);
    insert(&root,2);
    insert(&root,4);
    insert(&root,6);
    insert(&root,8);
    insert(&root,11);
    printf("inorder Traversal Is : ");
    inorder(root);
 
    return 0;
}

#ifdef __cplusplus
}
#endif
