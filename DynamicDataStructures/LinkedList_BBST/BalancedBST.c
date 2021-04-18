#include "BalancedBST.h"

struct BalancedBST * createNode(struct student *s){
    struct BalancedBST * new = (struct BalancedBST *)malloc(sizeof(struct BalancedBST));

    new->data = s;
    new->left = NULL;
    new -> right = NULL;
    new ->height = 1;
    return new;
}

struct BalancedBST * balancedBSTfromLinked(struct node * linked, int length){
    if (length == 1) {
        struct BalancedBST * root = createNode(linked->s);
        //printf("%d\n",root->data->index);
        return root;
    }

    struct node* tmp = linked;

    int mid = (length) / 2 ;

    for (int i = 0; i < mid; ++i) {
        tmp = tmp->next;
    }

    struct BalancedBST * root = createNode(tmp->s);
    //printf("%d\n",root->data->index);
    tmp = tmp->next;
    root->left = balancedBSTfromLinked(linked, mid);
    if (length - mid - 1 > 0) root->right = balancedBSTfromLinked(tmp, length - mid - 1);


    return root;
}
int height(struct BalancedBST *N)
{
    if (N == NULL)
        return  0;
    return N->height;
}

int getMax(int a, int b){
    return (a > b) ? a : b;
}
int getHeight(struct BalancedBST* root){
    if(root == NULL) return 0;
    else return 1 + getMax(getHeight(root -> left), getHeight(root -> right));
}
int isBalanced(struct BalancedBST* root){
    if(root == NULL) return 1; //if node is empty it means it is balanced
    int leftHeight, rightHeight;

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) return 1; // order here matters because if height is not correct then
        //we won't even check if children are also balanced
    else return 0;


}
struct BalancedBST * minValueNode(struct BalancedBST* root){
    struct BalancedBST * tmp = root;
    while(tmp && tmp->left != NULL) {
        tmp = tmp->left;
    }
    return tmp;
}

int getBalance(struct BalancedBST *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int isBST(struct BalancedBST* root){
    if (root == NULL) return 1;

    if (root->right != NULL && root->right->data->index < root->data->index) return 0 ;

    if (root->left != NULL && root->left->data->index > root->data->index) return 0 ;

    if(!isBST(root->left) || !isBST(root->right)) return 0;

    return 1;
}

void preorder(struct BalancedBST * root){
    if(root != NULL) {
        printf("%s %s %d\n", root->data->first_name, root->data->second_name, root->data->index );
        preorder(root->left);
        preorder(root->right);
    }
}
struct BalancedBST *rightRotate(struct BalancedBST *y)
{
    struct BalancedBST *x = y->left;
    struct BalancedBST *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = getMax(height(y->left), height(y->right))+1;
    x->height = getMax(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}



struct BalancedBST *leftRotate(struct BalancedBST *x)
{
    struct BalancedBST *y = x->right;
    struct BalancedBST *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = getMax(height(x->left), height(x->right))+1;
    y->height = getMax(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}


struct BalancedBST * insertBBST(struct BalancedBST * node, struct student * s, int * c){
    (*c)++;
    //if we reach potential leaf we place the node there
    if (node == NULL)
        return(createNode(s));

    if (s->index < node->data->index)
        node->left  = insertBBST(node->left, s, c);
    else if (s->index > node->data->index)
        node->right = insertBBST(node->right, s, c);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + getMax(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && s->index < node->left->data->index)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && s->index  > node->right->data->index)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && s->index  > node->left->data->index)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && s->index  < node->right->data->index)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}
//struct BalancedBST * tmp = root;
//while (tmp != NULL && tmp->data->index != index){
//if (index > tmp->data->index) tmp = tmp->right;
//else tmp = tmp->left;
//}
//if(tmp) return tmp->data;
//else return NULL;
struct student * searchBBST(struct BalancedBST *root, int index){
    if (root== NULL) return NULL;
    else if (index > root->data->index) return searchBBST(root->right, index);
    else if (index < root->data->index) return searchBBST(root->left, index);
    else return root->data;
}

struct BalancedBST * deleteBBST(struct BalancedBST * root, int index){
    if (root == NULL) return root;

    if (index < root->data->index) root->left = deleteBBST(root->left, index);
    else if(index > root->data->index) root->right = deleteBBST(root->right, index);
    //if it is equal we delete
    else {
        //if we have only one child or no children
        if (root->left == NULL) {
            struct BalancedBST * tmp = root->right;
            free(root);
            return tmp;
        }
        else if (root ->right == NULL) {
            struct BalancedBST * tmp = root->left;
            free(root);
            return tmp;
        }
        // found minimum node in the right subtree
        struct BalancedBST * tmp = minValueNode(root->right);
        root->data = tmp->data;

        root->right = deleteBBST(root->right, tmp->data->index);
    }

    if (root == NULL) return root;

    root->height = 1 + getMax(height(root->left),
                              height(root->right));

    int balance = getBalance(root);

    // now we have to distinguish beetwen types of rotation we need to perform
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    //if tree is balanced just return root pointer
    return root;
}