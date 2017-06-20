/*
NAME:           SKUBENICH, ALINA
DATE:           2014 11 28
DATE REVISED:   2017 06 19
CISP PROJECT:   AVL

    PROJECT REQUIREMENTS
    Populate a tree via a text file (input.txt)
    After every insert, the tree must be balanced.
    At the end, display the tree in level format.
    Make sure to include the height and the balance factor of every node in your output.
    Redirect the display to  an output file (output.txt)

    GENERAL INFORMATION
    The height of a node is the length of the longest downward path to a leaf from that node.
    The height of the root is the height of the tree.
    The depth of a node is the length of the path to its root (i.e., its root path).
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
ifstream in;
ofstream out;

typedef struct node{
    int key;
    int height;
    node *left;
    node *right;

}node;

typedef struct queueNode {
    node *ptr;
    struct queueNode *next;
}queueNode;

void    queued      (node* root);
void    dequeue     (queueNode*& , queueNode*& );
void    enqueue     (queueNode*& , queueNode*& , node* );

node    *newNode    ( int );
node    *leftRotate ( node *);
node    *rightRotate( node *);
node    *insert     ( node*& , int );
node    *rebalance  ( node *&);
int     getBalance  ( node *);
int     max         ( node*, node*);

int main(){

    node    *root = NULL;
    int     key;
    in.open("input.txt");
    out.open("output.txt");

    if (!in){
        cout << "ERROR OPENING FILE, input.txt\n";
        return -2;
    }

    while(!(in.eof())){
        in >> key;
        insert(root,key);
    }

    queued(root); //outputs to file and console

    in.clear();
    in.close();
    out.close();
    return 0;
}


node * newNode(int value){

    node *nNode=new node;

    nNode->key=value;
    nNode->height=0;
    nNode->left=NULL;
    nNode->right=NULL;
    return nNode;
}

/* non-tail recursive algorithm because of rebalance

  IT TRAVELS DOWN UNTIL IT GETS TO THE BOTTOM OF THE TREE,
  CREATES A NODE
  AND THEN
  GOES BACK UP TO CONNECT IT TO THE TREE

*/
node* insert( node*& node, int key){

    //  recursive Code for inserting a node
    if (node == NULL){
      return node = newNode(key);  //  When insert happens set height to 0 for the node
    }

    if (key < node->key){
        node->left  = insert(node->left, key);
    }
    else{
        node->right = insert(node->right, key);
    }
    node=rebalance(node); // update heights and rebalance
    return node;
}

int max( node *L, node *R){

      if (L == NULL && R == NULL){
        return -1;
      }
      else if (L == NULL){
            return (R->height);
      }
      else{

        return (L->height);
      }
}

int getBalance(node * child){

    int balance=0;

    if ((child->left == NULL) && (child->right==NULL))
       return balance = 0;

    if (child->left == NULL){
        balance= (-1-(child->right->height));
    }
    else if (child->right == NULL){
        balance=(child->left->height)-(-1);
    }
    else
        balance = ((child->left->height) - (child->right->height));

    return balance;
}

//This is not a recursive algorithm
 node * rebalance( node *&node){

    int balance = getBalance(node);

    node->height = (max(node->left, node->right)) + 1;

    if ((node->left != NULL) && (node->right != NULL)){
        node->height = (max(node->left->height, node->right->height)) + 1;
    }

    if ( balance < -1){ // RIGHT HEAVY
        balance=getBalance(node->right); // IS CHILD LEFT HEAVY ?
        if(balance>0){
            // double rotation right , left
            node->right=rightRotate(node->right);
            return node=leftRotate(node); //  if node is left heavy > 1
         }
         else
             return node=leftRotate(node); //  if node is left heavy > 1
    }
   if( balance > 1){ // LEFT HEAVY
         balance=getBalance(node->left); // IS CHILD RIGHT HEAVY ?
         if(balance<0){
            // double rotation left, right
            node->left=leftRotate(node->left);
            return node=rightRotate(node); //  if node is left heavy > 1
         }
         else
             return node=rightRotate(node); //  if node is left heavy > 1
    }

    return node;
}

node *leftRotate( node *x){

    node *y=x->right;

    // add more code to rotate to the left,
    x->right=y->left;
    y->left=x;

    // update heights for x and y
    x->height = (max(x->left, x->right)) + 1;
    y->height = (max(y->left, y->right)) + 1;

   //return root of the tree
    return y;
}

node *rightRotate( node *x){

    node *y=x->left;
   //add more code to rotate to the right,
    x->left=y->right;
    y->right=x;

    //   update heights for x and y
    x->height = (max(x->left, x->right)) + 1;
    y->height = (max(y->left, y->right)) + 1;

    //   return root of the tree
    return y;
}
//function to remove things from the queue;
void dequeue(queueNode*& first, queueNode*& last)
{
    queueNode *temp;

    if(first)
    {
        temp = first;
        first = first->next;
        delete temp;
    }

    if (!first)
        last = NULL;
}
//put in queue
void enqueue(queueNode*& first, queueNode*& last, node* root)
{
    if(root != NULL)
    {
        queueNode *newNode = new queueNode;

        newNode->ptr = root;
        newNode->next = NULL;

        if(last)
        {
            last->next = newNode;
            last = newNode;
        }
        else
            first = last = newNode;
    }
}
//print tree
void queued(node* root)
{
    queueNode *currF = NULL, *currL = NULL, *nextF = NULL, *nextL = NULL;
    node *lSide = NULL, *rSide = NULL;

    if(root == NULL)
        return;

    enqueue(currF, currL, root);

    while (currF != NULL)
    {
        int balance = getBalance(currF->ptr); // get balance for output each level

        cout << currF->ptr->key << "  "  << "("<< currF->ptr->height << ","<< balance << ") ";
        out << currF->ptr->key << "  "  << "("<< currF->ptr->height << ","<< balance << ") ";

        lSide = currF->ptr->left;
        rSide = currF->ptr->right;
        dequeue(currF, currL);
        enqueue(nextF, nextL, lSide);
        enqueue(nextF, nextL, rSide);

        if(currF == NULL)
        {
            while(nextF != NULL)
            {
                enqueue(currF, currL, nextF->ptr);
                dequeue(nextF, nextL);
            }
            cout << endl;
            out << endl;
        }
    }
}
