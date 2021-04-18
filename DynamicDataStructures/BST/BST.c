#include "BST.h"

struct node* new_node(struct student *s){
    struct node * new;
    new = (struct node *)malloc(sizeof(struct node));
    new->data = s;
    new->left =NULL;
    new->right = NULL;

    return new;
}

struct node* insert(struct node *root, struct student *s, int * counter){
    //(*counter)++;
    if(root == NULL)
        return new_node(s);
    else if(s->index> root->data->index){
        root->right = insert(root->right, s, counter);
    }
    else{
        root->left = insert(root->left, s, counter);
    }
    return root;
}
//if (root== NULL) return NULL;
//else if (index > root->data->index) return search(root->right, index);
//else if (index < root->data->index) return search(root->left, index);
//else return root->data;
struct student* search(struct node* root, int index){
    struct node * tmp = root;
    while (tmp != NULL && tmp->data->index != index){
        if (index > tmp->data->index) tmp = tmp->right;
        else tmp = tmp->left;
    }
    if(tmp) return tmp->data;
    else return NULL;
}

struct node * minValueNode(struct node* root){
    struct node * tmp = root;
    while(tmp && tmp->left != NULL) {
        tmp = tmp->left;
    }
    return tmp;
}
struct node* delete(struct node* root, int index){

    if (root == NULL) return root; //Base case

    if (index < root->data->index)  root->left = delete(root->left, index); // if key is in left subtree our current root is untouched

    else if(index > root->data->index) root->right = delete(root->right, index);

    //if key is the same we can delete the root
    else {
        //if we have case that node have only one child or no children
        if (root->left == NULL){
            struct node * tmp = root->right;
            //This is on the stack not on the heap
//            free(root->data->first_name);
//            free(root->data->second_name);
            free(root->data);
            free(root);
            return tmp;
        }
        else if (root->right == NULL){
            struct node * tmp = root->left;
            //This is also on the stack not on the heap
//            free(root->data->first_name);
//            free(root->data->second_name);
            free(root->data);
            free(root);
            return tmp;
        }
        //if not we search fot the minimum element and replece it with root and delete found element recursively

        struct node  * tmp = minValueNode(root->right); //we always find lowest value in right child
        root->data->index = tmp->data->index;

        root->right = delete(root->right, tmp->data->index);
    }
    return root;

}

struct node * create_BST(FILE * students){
    char * buf = (char *)malloc(LENGTH * sizeof(char));

    //char *token = (char *)malloc(LENGTH * sizeof(char) / 3);

    struct node *next;
    struct student *s;

    fgets(buf, LENGTH +1, students);

    struct node *root;

    //creating BST

    s = (struct student *)malloc(sizeof(struct student));
// We don't allocate memory dynamically
//    s->first_name = (char *)malloc(LENGTH * sizeof(char) / 3);
//    s->second_name = (char *)malloc(LENGTH * sizeof(char) / 3);

    char * token = strtok(buf, " ");
    strcpy(s->first_name, token);

    token = strtok(NULL, " ");
    strcpy(s->second_name, token);

    token = strtok(NULL, " ");
    s->index = atoi(token);

    root = new_node(s);

    int i = 0; // we want to read only 100 lines

    while(fgets(buf, LENGTH +1, students) != NULL){
        next = (struct node *)malloc(sizeof(struct node));

        s = (struct student *)malloc(sizeof(struct student));
//        We don't allocate memory dynamically
//        s->first_name = (char *)malloc(LENGTH * sizeof(char) / 3);
//        s->second_name = (char *)malloc(LENGTH * sizeof(char) / 3);

        token = strtok(buf, " ");
        strcpy(s->first_name, token);

        token = strtok(NULL, " ");
        strcpy(s->second_name, token);

        token = strtok(NULL, " ");
        s->index = atoi(token);
        insert(root, s,NULL);
        if (++i >=100) break;
    }
    free(buf);
    return root;
}

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left); // visiting left child
        printf("%s %s %d\n",root->data->first_name, root->data->second_name, root->data->index ); // printing data at root
        inorder(root->right);// visiting right child
    }
}

void preorder(struct node * root){
    if(root != NULL) {
        printf("%s %s %d\n", root->data->first_name, root->data->second_name, root->data->index );
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node* root){
    if(root !=NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s %s %d\n", root->data->first_name, root->data->second_name, root->data->index );
    }
}
int getMax(int a, int b){
    return (a >= b) ? a : b;
}
int getHeight(struct node* root){
    if(root == NULL) return 0;
    else return 1 + getMax(getHeight(root -> left), getHeight(root -> right));
}
int isBalanced(struct node* root){
    if(root == NULL) return 1; //if node is empty it means it is balanced
    int leftHeight, rightHeight;

    leftHeight = getHeight(root->left);
    rightHeight = getHeight(root->right);

    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) return 1; // order here matters because if height is not correct then
        //we won't even check if children are also balanced
    else return 0;


}
int isBST(struct node* root){
        if (root == NULL) return 1;

        if (root->right != NULL && root->right->data->index < root->data->index) return 0 ;

        if (root->left != NULL && root->left->data->index > root->data->index) return 0 ;

        if(!isBST(root->left) || !isBST(root->right)) return 0;

        return 1;
    }

void free_memory(struct node *root){
    if(root == NULL) return;
    if (root->left == NULL && root->right == NULL){

//        free(root->data->second_name);
//        free(root->data->first_name);
        free(root->data);
        free(root);
        return;
    }
    else if (root->left ==NULL){
        free_memory(root->right);
    }
    else if (root->right == NULL){
        free_memory(root->left);
    }
    else{
        free_memory(root->left);
        free_memory(root->right);
    }

}