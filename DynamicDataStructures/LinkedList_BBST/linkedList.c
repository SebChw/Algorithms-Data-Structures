#include "linkedList.h"

//function to insert the node that always return a pointer to the head
void insert(struct node** head_ref, char * student) {
    struct node* current;
    struct node* new = newNode(student);

    //special case if our new node should be the head now
    if (*head_ref == NULL || (*head_ref)->s->index >= new->s->index) {
        new->next = *head_ref;
        *head_ref = new;
    }
    else {
        /* Locate the node before
the point of insertion */
        current = *head_ref;
        while (current->next != NULL
               && current->next->s->index < new->s->index) {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
    }
}

struct node* newNode(char * student)
{
    /* allocate node */
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    struct student * new_s = (struct student *)malloc(sizeof(struct student));

    //new_s->first_name = malloc(sizeof(char) * LENGTH);
    //new_s->second_name = malloc(sizeof(char) * LENGTH);
    char *token = strtok(student, " ");
    strcpy(new_s->first_name, token);
    token = strtok(NULL, " ");
    strcpy(new_s->second_name, token);
    token = strtok(NULL, " ");
    new_s->index = atoi(token);
    /* put in the data  */
    new_node->s = new_s;
    new_node->next = NULL;

    return new_node;
}


//function to delete the node
struct node * delete(struct node *h, int index){
    struct node* curr = h;
    //special case if we have to delete head of the list
    if (curr ->s->index == index){
        h = curr->next;
        //free(curr->s->first_name);
        //free(curr->s->second_name);
        free(curr->s);
        free(curr);
        return h;
    }
    //typical case when node to be deleted is in the middle
    while(curr->next->next != NULL){
        if(curr->next->s->index == index){
            struct node * tmp = curr->next;
            curr->next = curr->next->next;
            //free(tmp->s->first_name);
            //free(tmp->s->second_name);
            free(tmp->s);
            free(tmp);
            return h;
        }
        curr = curr-> next;
    }
    //another special case when our node to be deleted is tail
    if(curr->next->s->index == index){
        struct node *tmp = curr->next;
        curr->next = NULL;
        //free(tmp->s->first_name);
        //free(tmp->s->second_name);
        free(tmp->s);
        free(tmp);
        return h;
    }
    else{
        printf("doesn't find node to delete\n");
        return h;
    }; //If there is no such student

}

struct student * search(struct node *h, int index){
    struct node * curr = h;
    //goes linearly through the whole list
    while(curr != NULL){
        if(curr->s->index == index) return curr->s;
        curr = curr->next;
    }
    return NULL; //if doesn't find the element returns the null pointer
}

