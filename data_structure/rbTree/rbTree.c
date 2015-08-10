#ifdef __cplusplus
extern "C"{
#endif

/* 
����1. �ڵ��Ǻ�ɫ���ɫ 
����2. ���Ǻ�ɫ 
����3. ÿ����ɫ�ڵ�������ӽڵ㶼�Ǻ�ɫ (��ÿ��Ҷ�ӵ���������·���ϲ��������������ĺ�ɫ�ڵ�) 
����4. ����һ�ڵ㵽��ÿ��Ҷ�ӵ�����·����������ͬ��Ŀ�ĺ�ɫ�ڵ� 
*/ 

/*
�������AVL�ıȽϣ�
AVL���ϸ�ƽ��������������ӻ���ɾ���ڵ��ʱ�򣬸��ݲ�ͬ�������ת�Ĵ����Ⱥ����Ҫ�ࣻ
������÷��ϸ��ƽ������ȡ��ɾ�ڵ�ʱ����ת�����Ľ��ͣ�
���Լ�˵��������Ӧ���У������Ĵ���ԶԶ���ڲ����ɾ������ôѡ��AVL�����������
����ɾ������������࣬Ӧ��ѡ��RB��
*/
  
#include <stdio.h> 
#include <stdlib.h> 
typedef enum Color //�������������ɫ��ɫ���� 
{ 
    RED = 0, 
    BLACK = 1 
}Color; 
  
typedef struct Node //��������������� 
{ 
    struct Node *parent; 
    struct Node *left; 
    struct Node *right; 
    int value; 
    Color color; 
}Node, *Tree; 
Node *nil=NULL; //Ϊ�˱������۽��ı߽����������һ��nil���������е�NULL 
  
Node* Parent(Node *z) //����ĳ���ĸ�ĸ 
{ 
    return z->parent; 
} 
Node* Left(Node *z) //���������� 
{ 
    return z->left; 
} 
Node *Right(Node *z) //���������� 
{ 
    return z->right; 
} 
void LeftRotate(Tree &T, Node *x) //����ת�����xԭ����������y��ת��Ϊx�ĸ�ĸ 
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
  
void RightRotate(Tree &T, Node *x) //����ת�����xԭ����������y��ת��Ϊx�ĸ�ĸ 
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
  
void InsertFixup(Tree &T, Node *z) //�������, Ҫά�ֺ�����������ʵĲ����� 
{ 
    Node *y; 
    while( Parent(z)->color == RED ) //��Ϊ����Ľ���Ǻ�ɫ�ģ�����ֻ����Υ������3,�����縸���Ҳ�Ǻ�ɫ�ģ�Ҫ������ 
    { 
        if( Parent(Parent(z))->left == Parent(z) ) //���Ҫ����Ľ��z���丸���������� 
        { 
            y=Parent(Parent(z))->right; // y����Ϊz���常��� 
            if( y->color == RED ) //case 1: ���y����ɫΪ��ɫ����ô��y��z�ĸ���ͬʱ��Ϊ��ɫ��Ȼ���z�� 
            { //�游��Ϊ��ɫ��������z���游������Υ������3,��z���Ƴ�z���游��� 
                y->color=BLACK; 
                z->parent->color=BLACK; 
                z->parent->parent->color=RED; 
                z=z->parent->parent; 
            } 
            else 
            { 
                if( z == z->parent->right ) //case 2: ���y����ɫΪ��ɫ������z��z�ĸ�ĸ���ҽ�㣬��z����ת�����ҽ�z��Ϊԭ��z��parent. 
                { 
                    z=z->parent; 
                    LeftRotate(T, z); 
                } 
                z->parent->color=BLACK; //case 3: ���y����ɫΪ��ɫ������z��z�ĸ�ĸ�����㣬��ô��z�� 
                z->parent->parent->color=RED; //���׵���ɫ��Ϊ�ڣ���z���游����ɫ��Ϊ�죬Ȼ����תz���游 
                RightRotate(T,z->parent->parent); 
            } 
        } 
        else //��ǰһ������Գƣ�Ҫ����Ľ��z���丸����������,ע����ȥ 
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
    T->color=BLACK; //����������ΪT�ĸ��Ļ�����T����ɫ����Ϊ��ɫ 
} 
void Insert(Tree &T, int val) //������ 
{ 
    if(T == NULL) //��ʼ��������������в����ڣ���ônewһ���½�������ͬʱnewһ���½���nil 
    { 
        T=(Tree)malloc(sizeof(Node)); 
        nil=(Node*)malloc(sizeof(Node)); 
        nil->color=BLACK; //nil����ɫ����Ϊ�� 
        T->left=nil; 
        T->right=nil; 
        T->parent=nil; 
        T->value=val; 
        T->color=BLACK; //Ϊ����������2,������ɫ����Ϊ��ɫ 
    } 
    else //��������Ѿ���Ϊ�գ���ô�Ӹ���ʼ���������²��Ҳ���� 
    { 
        Node *x=T; //��x���浱ǰ����ĸ�ĸ��㣬��p���浱ǰ�Ľ�� 
        Node *p=nil; 
        while(x != nil) //���valС�ڵ�ǰ����valueֵ����������ȥ��������ұ���ȥ 
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
                printf("%s %d/n","duplicate value",val); //������ҵ���valֵ��ͬ�Ľ�㣬��ʲôҲ������ֱ�ӷ��� 
                return; 
            } 
  
        } 
        x=(Node*)malloc(sizeof(Node)); 
        x->color=RED; //�²���Ľ����ɫ����Ϊ��ɫ 
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
          
        InsertFixup(T, x); //�����������е��� 
          
    } 
} 
  
Node* Successor(Tree &T, Node *x) //Ѱ�ҽ��x�������� 
{ 
    if( x->right != nil ) //���x����������Ϊ�գ���ôΪ������������ߵĽ�� 
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
    else //���x��������Ϊ�գ���ôx�ĺ��Ϊx������������Ϊ������������ 
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
  
void DeleteFixup(Tree &T, Node *x) //ɾ����ɫ���󣬵��º�ɫȱʧ��Υ������4,�ʶ������е��� 
{ 
    while( x != T && x->color == BLACK ) //���x�Ǻ�ɫ����ֱ�Ӱ�x��Ϊ��ɫ����ѭ���������Ӹպò���һ�غ�ɫ,Ҳ����������4 
    { 
        if( x == x->parent->left ) //���x���丸���������� 
        { 
            Node *w=x->parent->right; //��w��x���ֵܽ�� 
            if( w->color == RED ) //case 1: ���w����ɫΪ��ɫ�Ļ� 
            { 
                w->color=BLACK; 
                x->parent->color=RED; 
                LeftRotate(T, x->parent); 
                w=x->parent->right; 
            } 
            if( w->left->color == BLACK && w->right->color == BLACK ) //case 2: w����ɫΪ��ɫ����������������ɫ��Ϊ��ɫ 
            { 
                w->color=RED; 
                x=x->parent; 
            } 
            else if( w->right->color == BLACK ) //case 3: w���������Ǻ�ɫ���������Ǻ�ɫ�Ļ� 
            { 
                w->color=RED; 
                w->left->color=BLACK; 
                RightRotate(T, w); 
                w=x->parent->right; 
            } 
            w->color=x->parent->color; //case 4: w���������Ǻ�ɫ 
            x->parent->color=BLACK; 
            w->right->color=BLACK; 
            LeftRotate(T , x->parent); 
              
            x=T; 
        } 
        else //�Գ���������x���丸���������� 
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
  
void Delete(Tree &T, Node *z) //�ں����T��ɾ�����z 
{ 
    Node *y; //yָ��Ҫ��ɾ���Ľ�� 
    Node *x; //xָ��Ҫ��ɾ���Ľ���Ψһ���� 
    if( z->left == nil || z->right == nil ) //���z��һ������Ϊ�յĻ�����ô��ֱ��ɾ��z,��yָ��z 
    { 
        y=z; 
    } 
    else 
    { 
        y=Successor(T, z); //���z�����������Բ�Ϊ�յĻ�����Ѱ��z��������y�� 
    } //����ֵ����z��ֵ��Ȼ��yɾ�� ( ע��: y�϶���û���������� ) 
    if( y->left != nil ) //���y����������Ϊ�գ���xָ��y�������� 
    { 
        x=y->left; 
    } 
    else 
    { 
        x=y->right; 
    } 
    x->parent=y->parent; //��ԭ��y�ĸ�ĸ��Ϊx�ĸ�ĸ��y������ɾ�� 
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
    if( y != z ) //�����ɾ���Ľ��y����ԭ����Ҫɾ���Ľ��z�� 
    { //��ֻ����y��ֵ������z��ֵ��Ȼ�����ɾ��y�Դﵽɾ��z��Ч�� 
        z->value=y->value; 
    } 
    if( y->color == BLACK ) //�����ɾ���Ľ��y����ɫΪ��ɫ����ô���ܻᵼ����Υ������4,����ĳ��·��������һ����ɫ 
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