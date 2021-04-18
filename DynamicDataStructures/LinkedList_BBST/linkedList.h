#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 50

#ifndef PROJECT2_LINKEDLIST_H
#define PROJECT2_LINKEDLIST_H

//content of the linked list
struct student {
    char first_name[13];
    char second_name[13];
    int index;
};
//create node of the linked list
struct node {
    struct node * next;
    struct student * s;

};

void insert(struct node** h, char * student);
struct node * delete(struct node *h, int index);
struct student * search(struct node *h, int index);

struct node* newNode(char * student);
#endif //PROJECT2_LINKEDLIST_H
