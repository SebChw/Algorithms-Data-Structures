#ifndef BST_BST_H
#define BST_BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 40

struct student{
    char first_name[13];
    char second_name[13];
    int index;
};

struct node {
    struct student * data;
    struct node *left;
    struct node *right;
};


struct node* new_node(struct student *s); //Function that creates new node to be insterted into BST
struct node* insert(struct node *root, struct student *s, int * counter); //Function that insert new node to the tree
struct student* search(struct node* root, int index); //Function that search for the student
struct node * minValueNode(struct node* root); // Auxiliary function for delete, it searches for most left node in right subtree
struct node* delete(struct node* root, int index); // Function that delete given node
void inorder(struct node *root); //Function that does inorder traversal
void free_memory(struct node *root); // function that free the memory
struct node * create_BST(FILE * data); // functions that create BST given file pointer (works only for specific kind of input data)
void preorder(struct node * root); // function that does preorder traversal
void postorder(struct node* root); // function that doeas postorder traversal
int getMax(int a, int b); // function that just get maximum from 2 numbers
int getHeight(struct node* root); // Auxiliary function to isBalanced,  just returns height of given node
int isBalanced(struct node* root); //function that checks wheather tree is balanced or not
int isBST(struct node* root); //function that cheks if the tree is balanced
#endif //BST_BST_H
