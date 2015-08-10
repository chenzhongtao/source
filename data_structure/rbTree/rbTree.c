#ifdef __cplusplus
extern "C"{
#endif

/* 
性质1. 节点是红色或黑色 
性质2. 根是黑色 
性质3. 每个红色节点的两个子节点都是黑色 (从每个叶子到根的所有路径上不能有两个连续的红色节点) 
性质4. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点 
*/ 

/*
红黑树与AVL的比较：
AVL是严格平衡树，因此在增加或者删除节点的时候，根据不同情况，旋转的次数比红黑树要多；
红黑是用非严格的平衡来换取增删节点时候旋转次数的降低；
所以简单说，如果你的应用中，搜索的次数远远大于插入和删除，那么选择AVL，如果搜索，
插入删除次数几乎差不多，应该选择RB。
*/
  
#include <stdio.h> 
#include <stdlib.h> 
typedef enum Color //定义红黑树结点颜色颜色类型 
{ 
    RED = 0, 
    BLACK = 1 
}Color; 
  
typedef struct Node //定义红黑树结点类型 
{ 
    struct Node *parent; 
    struct Node *left; 
    struct Node *right; 
    int value; 
    Color color; 
}Node, *Tree; 
Node *nil=NULL; //为了避免讨论结点的边界情况，定义一个nil结点代替所有的NULL 
  
Node* Parent(Node *z) //返回某结点的父母 
{ 
    return z->parent; 
} 
Node* Left(Node *z) //返回左子树 
{ 
    return z->left; 
} 
Node *Right(Node *z) //返回右子树 
{ 
    return z->right; 
} 
void LeftRotate(Tree &T, Node *x) //左旋转：结点x原来的右子树y旋转成为x的父母 
{ 
    if( x-> right != nil ) 
    { 
        Node *y=Right(x); 
        x->right=y->left; 
        if(y->left != nil) 
        { 
            y->left->parent=x; 
        } 
        y->parent=x->parent; 
        if( x->parent == nil ) 
        { 
            T=y; 
        } 
        else 
        { 
            if( x == Left(Parent(x)) ) 
            { 
                x->parent->left=y; 
            } 
            else 
            { 
                x->parent->right=y; 
            } 
        } 
        y->left=x; 
        x->parent=y; 
    } 
    else 
    { 
        printf("%s/n","can't execute left rotate due to null right child"); 
    } 
} 
  
void RightRotate(Tree &T, Node *x) //右旋转：结点x原来的左子树y旋转成为x的父母 
{ 
    if( x->left != nil ) 
    { 
        Node *y=Left(x); 
        x->left=y->right; 
        if( y->right != nil ) 
        { 
            y->right->parent=x; 
        } 
        y->parent=x->parent; 
        if( x->parent == nil ) 
        { 
            T=y; 
        } 
        else 
        { 
            if(x == Left(Parent(x)) ) 
            { 
                x->parent->left=y; 
            } 
            else 
            { 
                x->parent->right=y; 
            } 
        } 
        y->right=x; 
        x->parent=y; 
    } 
    else 
    { 
        printf("%s/n","can't execute right rotate due to null left child"); 
    } 
  
} 
  
void InsertFixup(Tree &T, Node *z) //插入结点后, 要维持红黑树四条性质的不变性 
{ 
    Node *y; 
    while( Parent(z)->color == RED ) //因为插入的结点是红色的，所以只可能违背性质3,即假如父结点也是红色的，要做调整 
    { 
        if( Parent(Parent(z))->left == Parent(z) ) //如果要插入的结点z是其父结点的左子树 
        { 
            y=Parent(Parent(z))->right; // y设置为z的叔父结点 
            if( y->color == RED ) //case 1: 如果y的颜色为红色，那么将y与z的父亲同时着为黑色，然后把z的 
            { //祖父变为红色，这样子z的祖父结点可能违背性质3,将z上移成z的祖父结点 
                y->color=BLACK; 
                z->parent->color=BLACK; 
                z->parent->parent->color=RED; 
                z=z->parent->parent; 
            } 
            else 
            { 
                if( z == z->parent->right ) //case 2: 如果y的颜色为黑色，并且z是z的父母的右结点，则z左旋转，并且将z变为原来z的parent. 
                { 
                    z=z->parent; 
                    LeftRotate(T, z); 
                } 
                z->parent->color=BLACK; //case 3: 如果y的颜色为黑色，并且z是z的父母的左结点，那么将z的 
                z->parent->parent->color=RED; //父亲的颜色变为黑，将z的祖父的颜色变为红，然后旋转z的祖父 
                RightRotate(T,z->parent->parent); 
            } 
        } 
        else //与前一种情况对称，要插入的结点z是其父结点的右子树,注释略去 
        { 
            y=Parent(Parent(z))->left; 
            if( y->color == RED) 
            { 
                z->parent->color=BLACK; 
                y->color=BLACK; 
                z->parent->parent->color=RED; 
                z=z->parent->parent; 
            } 
            else 
            { 
                if( z == z->parent->left ) 
                { 
                    z=z->parent; 
                    RightRotate(T,z); 
                } 
                z->parent->color=BLACK; 
                z->parent->parent->color=RED; 
                LeftRotate(T,z->parent->parent); 
            } 
        } 
    } 
    T->color=BLACK; //最后如果上升为T的根的话，把T的颜色设置为黑色 
} 
void Insert(Tree &T, int val) //插入结点 
{ 
    if(T == NULL) //初始化工作：如果根尚不存在，那么new一个新结点给根，同时new一个新结点给nil 
    { 
        T=(Tree)malloc(sizeof(Node)); 
        nil=(Node*)malloc(sizeof(Node)); 
        nil->color=BLACK; //nil的颜色设置为黑 
        T->left=nil; 
        T->right=nil; 
        T->parent=nil; 
        T->value=val; 
        T->color=BLACK; //为了满足性质2,根的颜色设置为黑色 
    } 
    else //如果此树已经不为空，那么从根开始，从上往下查找插入点 
    { 
        Node *x=T; //用x保存当前顶点的父母结点，用p保存当前的结点 
        Node *p=nil; 
        while(x != nil) //如果val小于当前结点的value值，则从左边下去，否则从右边下去 
        { 
            p=x; 
            if(val < x->value ) 
            { 
                x=x->left; 
            } 
            else if(val > x->value) 
            { 
                x=x->right; 
            } 
            else 
            { 
                printf("%s %d/n","duplicate value",val); //如果查找到与val值相同的结点，则什么也不做，直接返回 
                return; 
            } 
  
        } 
        x=(Node*)malloc(sizeof(Node)); 
        x->color=RED; //新插入的结点颜色设置为红色 
        x->left=nil; 
        x->right=nil; 
        x->parent=p; 
        x->value=val; 
        if( val < p->value ) 
        { 
            p->left = x; 
        } 
        else 
        { 
            p->right = x; 
        } 
          
        InsertFixup(T, x); //插入后对树进行调整 
          
    } 
} 
  
Node* Successor(Tree &T, Node *x) //寻找结点x的中序后继 
{ 
    if( x->right != nil ) //如果x的右子树不为空，那么为右子树中最左边的结点 
    { 
        Node *q=nil; 
        Node *p=x->right; 
        while( p->left != nil ) 
        { 
            q=p; 
            p=p->left; 
        } 
        return q; 
    } 
    else //如果x的右子树为空，那么x的后继为x的所有祖先中为左子树的祖先 
    { 
        Node *y=x->parent; 
        while( y != nil && x == y->right ) 
        { 
            x=y; 
            y=y->parent; 
        } 
          
        return y; 
    } 
} 
  
void DeleteFixup(Tree &T, Node *x) //删除黑色结点后，导致黑色缺失，违背性质4,故对树进行调整 
{ 
    while( x != T && x->color == BLACK ) //如果x是红色，则直接把x变为黑色跳出循环，这样子刚好补了一重黑色,也满足了性质4 
    { 
        if( x == x->parent->left ) //如果x是其父结点的左子树 
        { 
            Node *w=x->parent->right; //设w是x的兄弟结点 
            if( w->color == RED ) //case 1: 如果w的颜色为红色的话 
            { 
                w->color=BLACK; 
                x->parent->color=RED; 
                LeftRotate(T, x->parent); 
                w=x->parent->right; 
            } 
            if( w->left->color == BLACK && w->right->color == BLACK ) //case 2: w的颜色为黑色，其左右子树的颜色都为黑色 
            { 
                w->color=RED; 
                x=x->parent; 
            } 
            else if( w->right->color == BLACK ) //case 3: w的左子树是红色，右子树是黑色的话 
            { 
                w->color=RED; 
                w->left->color=BLACK; 
                RightRotate(T, w); 
                w=x->parent->right; 
            } 
            w->color=x->parent->color; //case 4: w的右子树是红色 
            x->parent->color=BLACK; 
            w->right->color=BLACK; 
            LeftRotate(T , x->parent); 
              
            x=T; 
        } 
        else //对称情况，如果x是其父结点的右子树 
        { 
            Node *w=x->parent->left; 
            if( w->color == RED ) 
            { 
                w->color=BLACK; 
                x->parent->color=RED; 
                RightRotate(T, x->parent); 
                w=x->parent->left; 
            } 
            if( w->left->color == BLACK && w->right->color == BLACK ) 
            { 
                w->color=RED; 
                x=x->parent; 
            } 
            else if( w->left->color == BLACK ) 
            { 
                w->color=RED; 
                w->right->color=BLACK; 
                LeftRotate(T, w); 
                w=x->parent->left; 
            } 
            w->color=x->parent->color; 
            x->parent->color=BLACK; 
            w->left->color=BLACK; 
            RightRotate(T , x->parent); 
              
            x=T; 
              
        } 
    } 
    x->color=BLACK; 
} 
  
void Delete(Tree &T, Node *z) //在红黑树T中删除结点z 
{ 
    Node *y; //y指向将要被删除的结点 
    Node *x; //x指向将要被删除的结点的唯一儿子 
    if( z->left == nil || z->right == nil ) //如果z有一个子树为空的话，那么将直接删除z,即y指向z 
    { 
        y=z; 
    } 
    else 
    { 
        y=Successor(T, z); //如果z的左右子树皆不为空的话，则寻找z的中序后继y， 
    } //用其值代替z的值，然后将y删除 ( 注意: y肯定是没有左子树的 ) 
    if( y->left != nil ) //如果y的左子树不为空，则x指向y的左子树 
    { 
        x=y->left; 
    } 
    else 
    { 
        x=y->right; 
    } 
    x->parent=y->parent; //将原来y的父母设为x的父母，y即将被删除 
    if( y->parent == nil ) 
    { 
        T=x; 
    } 
    else 
    { 
        if( y == y->parent->left ) 
        { 
            y->parent->left=x; 
        } 
        else 
        { 
            y->parent->right=x; 
        } 
    } 
    if( y != z ) //如果被删除的结点y不是原来将要删除的结点z， 
    { //即只是用y的值来代替z的值，然后变相删除y以达到删除z的效果 
        z->value=y->value; 
    } 
    if( y->color == BLACK ) //如果被删除的结点y的颜色为黑色，那么可能会导致树违背性质4,导致某条路径上少了一个黑色 
    { 
        DeleteFixup(T, x); 
    } 
} 
Node* Search(Tree T, int val) 
{ 
    if( T != nil ) 
    { 
        if( val < T->value ) 
        { 
            Search(T->left, val); 
        } 
        else if ( val > T->value ) 
        { 
            Search(T->right,val); 
        } 
        else 
        { 
            return T; 
        } 
    } 
} 
  
void MidTranverse(Tree T) 
{ 
    if( T != NULL && T != nil ) 
    { 
        MidTranverse(T->left); 
        printf("%d ",T->value); 
        MidTranverse(T->right); 
    } 
  
} 
int main() 
{ 
    Tree t=NULL; 
    Insert(t,30); 
    Insert(t,50); 
    Insert(t,65); 
    Insert(t,80); 
    Delete(t,Search(t,30)); 
    Delete(t,Search(t,65)); 
    MidTranverse(t); 
    return 0; 
}

#ifdef __cplusplus
}
#endif