#ifndef PROJECT2_BALANCEDBST_H
#define PROJECT2_BALANCEDBST_H
#include "linkedList.h"

struct BalancedBST{
    struct student * data;
    struct BalancedBST * left;
    struct BalancedBST * right;
    int height;
};

struct BalancedBST * createNode(struct student *s);
struct BalancedBST * balancedBSTfromLinked(struct node * linked, int length);
int getMax(int a, int b); // function that just get maximum from 2 numbers
int getHeight(struct BalancedBST* root); // Auxiliary function to isBalanced,  just returns height of given node
int isBalanced(struct BalancedBST* root); //function that checks wheather tree is balanced or not
int isBST(struct BalancedBST* root); //function that cheks if the tree is balanced
void preorder(struct BalancedBST * root); // function that does preorder traversal
int height(struct BalancedBST *N);
int getBalance(struct BalancedBST *N);
struct BalancedBST * minValueNode(struct BalancedBST* root); // Auxiliary function for delete, it searches for most left node in right subtree
struct BalancedBST * rightRotate(struct BalancedBST * node);
struct BalancedBST * leftRotate(struct BalancedBST * node);
struct BalancedBST * insertBBST(struct BalancedBST * root, struct student * s, int * c);
struct student * searchBBST(struct BalancedBST *root, int index);
struct BalancedBST * deleteBBST(struct BalancedBST * root, int index);
#endif //PROJECT2_BALANCEDBST_H
