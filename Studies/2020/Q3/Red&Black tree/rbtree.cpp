#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>

#define COUNT 10
typedef int T; /* type of item to be stored */
#define compLT(a, b) (a < b)
#define compEQ(a, b) (a == b)
#define blackColor(x) ("\033[\033[1;48;5;7;38;5;0m" + std::to_string(x) + "\033[0m")
#define redColor(x) ("\033[\033[1;48;5;7;38;5;196m" + std::to_string(x) + "\033[0m")

/* Red-Black tree description */
typedef enum
{
    BLACK,
    RED
} nodeColor;

typedef struct Node_
{
    struct Node_* left;   /* left child */
    struct Node_* right;  /* right child */
    struct Node_* parent; /* parent */
    nodeColor color;      /* node color (BLACK, RED) */
    T data;               /* data stored in node */
} Node;

#define NIL &sentinel /* all leafs are sentinels */
Node sentinel = {NIL, NIL, 0, BLACK, 0};

Node* root = NIL; /* root of Red-Black tree */

void rotateLeft(Node* x)
{

    /**************************
     *  rotate node x to left *
     **************************/

    Node* y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL)
        y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else
    {
        root = y;
    }

    /* link x and y */
    y->left = x;
    if (x != NIL)
        x->parent = y;
}

void rotateRight(Node* x)
{

    /****************************
     *  rotate node x to right  *
     ****************************/

    Node* y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if (y->right != NIL)
        y->right->parent = x;

    /* establish y->parent link */
    if (y != NIL)
        y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else
    {
        root = y;
    }

    /* link x and y */
    y->right = x;
    if (x != NIL)
        x->parent = y;
}

void insertFixup(Node* x)
{

    /*************************************
     *  maintain Red-Black tree balance  *
     *  after inserting node x           *
     *************************************/

    /* check Red-Black properties */
    while (x != root && x->parent->color == RED)
    {
        /* we have a violation */
        if (x->parent == x->parent->parent->left)
        {
            Node* y = x->parent->parent->right;
            if (y->color == RED)
            {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                /* uncle is BLACK */
                if (x == x->parent->right)
                {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft(x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent);
            }
        }
        else
        {

            /* mirror image of above code */
            Node* y = x->parent->parent->left;
            if (y->color == RED)
            {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                /* uncle is BLACK */
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node* insertNode(T data)
{
    Node *current, *parent, *x;

    /***********************************************
     *  allocate node for data and insert in tree  *
     ***********************************************/

    /* find where node belongs */
    current = root;
    parent = 0;
    while (current != NIL)
    {
        if (compEQ(data, current->data))
            return (current);
        parent = current;
        current = compLT(data, current->data) ? current->left : current->right;
    }

    /* setup new node */
    x = new Node;
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    /* insert node in tree */
    if (parent)
    {
        if (compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    }
    else
    {
        root = x;
    }

    insertFixup(x);
    return (x);
}

void deleteFixup(Node* x)
{

    /*************************************
     *  maintain Red-Black tree balance  *
     *  after deleting node x            *
     *************************************/

    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        }
        else
        {
            Node* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void deleteNode(Node* z)
{
    Node *x, *y;

    /*****************************
     *  delete node z from tree  *
     *****************************/

    if (!z || z == NIL)
        return;

    if (z->left == NIL || z->right == NIL)
    {
        /* y has a NIL node as a child */
        y = z;
    }
    else
    {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y->left != NIL)
            y = y->left;
    }

    /* x is y's only child */
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != z)
        z->data = y->data;

    if (y->color == BLACK)
        deleteFixup(x);

    free(y);
}

Node* findNode(T data)
{

    /*******************************
     *  find node containing data  *
     *******************************/

    Node* current = root;
    while (current != NIL)
        if (compEQ(data, current->data))
            return (current);
        else
            current = compLT(data, current->data) ? current->left : current->right;
    return (0);
}

void printNode(Node* root)
{
    if (root)
    {
        if (root->color == RED)
        {
            std::cout << redColor(root->data) << std::endl;
        }
        else
        {
            std::cout << blackColor(root->data) << std::endl;
        }
    }
    else
    {
        std::cout << "Root not found" << std::endl;
    }
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(Node* root, int space)
{
    // Base case
    if (root == NIL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    printNode(root);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int main(int argc, char** argv)
{
    int a, maxnum, ct;
    Node* t;

    /* command-line:
     *
     *   rbt maxnum
     *
     *   rbt 2000
     *       process 2000 records
     *
     */

    maxnum = atoi(argv[1]);
    try
    {
        for (ct = maxnum; ct; ct--)
        {
            a = rand() % maxnum + 1;
            if ((t = findNode(a)) != NULL)
            {
                deleteNode(t);
            }
            else
            {
                insertNode(a);
            }
        }
    }
    catch (std::bad_alloc)
    {
        std::cerr << "Insufficient memory for tree allocation" << std::endl;
    }
    printNode(findNode(-1));
    print2D(root);
}