#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//edge list will be represented as linked list e1->e2->e3
struct edge_list{
    int v1;
    int v2;
    struct edge_list *next;
};
//adj list will be represented as list of linked lists
//1: n1->n2->n3-n4 all these nodes are adjecent to node 1
struct adj_list{
    int node;
    struct adj_list *next;
};

//as we don't need to preserve any order we can just add next element at the beggining of the linked list every time
struct adj_list * add_adj_list(struct adj_list *head, int a){
    struct adj_list *x = malloc(sizeof(*x));
    x->node = a;
    x->next = head;
    return x;
//    if(*head == NULL){
//        *head = x;
//        return;
//    }
//    struct adj_list *curr = *head;
//    while(curr->next != NULL)
//        curr = curr -> next;
//    curr->next = x;
}

// of course we need to free the memory
void free_adj_list(struct adj_list *head){
    struct adj_list *curr = head;
    struct adj_list *tmp;
    while (curr != NULL){
        tmp = curr;
        curr = curr -> next;
        free(tmp);
    }
}

void print_adj_list(struct adj_list *head){
    struct adj_list *curr = head;
    while(curr != NULL){
        printf("%d\n", curr->node);
        curr = curr->next;
    }
}
//just linear search
int search_adj_list(struct adj_list *head, int x){
    struct adj_list *curr = head;
    while(curr != NULL){
        if(curr->node == x)
            return 1;
        curr = curr->next;
    }
    return 0;
}
//again as we don't need to preserve any order we can add at the beginning of the list
struct edge_list * add_edge_list(struct edge_list *head, int a, int b){
    struct edge_list *x = malloc(sizeof(*x));
    x->v1 = a;
    x->v2 = b;
    x->next = head;
    return x;
//    if(head == NULL){
//        head = x;
//        return head;
//    }
//    struct edge_list *curr = *head;
//    while(curr->next != NULL)
//        curr = curr -> next;
//    curr->next = x;
}

void print_edge_list(struct edge_list *head){
    struct edge_list *curr = head;
    while(curr != NULL){
        printf("%d %d\n", curr->v1, curr->v2);
        curr = curr->next;
    }
}

int search_edge_list(struct edge_list *head, int a, int b){
    struct edge_list *curr = head;
    while(curr != NULL){
        if((curr->v1 == a && curr->v2 == b) || (curr->v1 == b && curr->v2 == a))
            return 1;
        curr = curr->next;
    }
    return 0;
}

void free_edge_list(struct edge_list *head){
    struct edge_list *curr = head;
    struct edge_list *tmp;
    while (curr != NULL){
        tmp = curr;
        curr = curr -> next;
        free(tmp);
    }
}

int main() {

    double creating_representations[10][4]; //here we store time needed to create a representation
    double searching[10][4]; // here we store time needed to search
    //we have 10 measuring points starting from 100 nodes to 1000 nodes
    for (int c = 1; c <= 10 ; ++c) {
        printf("Run %d\n", c);
        int n, m; //nodes and edges
        int lenght =20;
        char name[30];
        sprintf(name, "data_%d.txt", c);

        struct timeval  tv1, tv2;

        ////EDGE LIST
        printf("Edge list\n");
        FILE *f = fopen(name, "r");
        if(f==NULL){
            printf("Fail\n");
            return 1;
        }
        char *buf = malloc(sizeof(char) * lenght);
        fgets(buf, lenght, f);
        //printf("%s\n", buf);
        n = atoi(strtok(buf, " ")); //first line of the file contains amount of nodes
        m = atoi(strtok(NULL, " ")); // and amount of edges
        printf("n=%d m=%d\n", n, m);
        int a, b;
        gettimeofday(&tv1, NULL); //start measuring at this point
        struct edge_list *head = NULL;

       //then we read the whole file and append each edge to the edge list
        while(fgets(buf, lenght, f)){
            a = atoi(strtok(buf, " "));
            b = atoi(strtok(NULL, " "));
            head = add_edge_list(head, a , b); //this operation takes O(1) so overall complexity of adding all elements is O(m) so O(n^2)
        }
        gettimeofday(&tv2, NULL); //end measuring at this point
        creating_representations[c-1][0] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
        // printf("%d \n", creating_representations[0]);
         //print_edge_list(head);
        fclose(f);

        ////NEIGHBORHOOD MATRIX
        printf("NEIGHBORHOOD MATRIX\n");
        f = fopen(name, "r");
        if(f==NULL){
            printf("Fail\n");
            return 1;
        }
        fgets(buf, lenght, f); //to get rif of n and m, already read
        gettimeofday(&tv1, NULL);
        //we need to create nxn matrix that each cell in it represents one possible edge
        int * *neighborhood = malloc(sizeof(int *) * n);
        for(int i=0; i<n; i++){
            neighborhood[i] = calloc(n, sizeof(int)); //calloc sets all values at 0 and this operation is not linear but faster
        }
        //now getting all edges and just updating matrix entries
        while(fgets(buf, lenght, f)){
            a = atoi(strtok(buf, " "));
            b = atoi(strtok(NULL, " "));
            neighborhood[a-1][b-1] = 1;
            neighborhood[b-1][a-1] = 1;
        }
        gettimeofday(&tv2, NULL);
        creating_representations[c-1][1] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
        //// PRINT MATRIX
//    for(int i=0; i<n; i++){
//        for(int j=0; j<n; j++)
//            printf("%d\t", neighborhood[i][j]);
//        printf("\n");
//    }

        fclose(f);
        ////INCIDENCE MATRIX
        printf("Incidence matrix\n");
        f = fopen(name, "r");
        if(f==NULL){
            printf("Fail\n");
            return 1;
        }
        fgets(buf, lenght, f); //to get rif of n and m, already read
        gettimeofday(&tv1, NULL);
        //here we create matrix that is nxm so it has many more columns as m approximetely may be n^2/2 in undirected graph
        int * *incidence = malloc(sizeof(int *) * n);
        for(int i=0; i<n; i++){
            incidence[i] = calloc(m, sizeof(int));
        }
        int cnt = 0;
        while(fgets(buf, lenght, f)){
            a = atoi(strtok(buf, " "));
            b = atoi(strtok(NULL, " "));
            incidence[a-1][cnt] = 1;
            incidence[b-1][cnt] = 1;
            cnt ++;
        }
        gettimeofday(&tv2, NULL);
        creating_representations[c-1][2] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
        //// PRINT MATRIX
//    for(int i=0; i<n; i++){
//        for(int j=0; j<m; j++)
//            printf("%d\t", incidence[i][j]);
//        printf("\n");
//    }

        fclose(f);
        ///ADJ
        printf("adj list\n");
        f = fopen(name, "r");
        if(f==NULL){
            printf("Fail\n");
            return 1;
        }
        fgets(buf, lenght, f); //to get rid of n and m, already read
        gettimeofday(&tv1, NULL);
        //here we create linked list for each node but it is hard to tell how long each will be
        struct adj_list **adj = malloc(sizeof(**adj) * n);
        for(int i=0; i<n; i++){
            adj[i] = NULL;
        }

        while(fgets(buf, lenght, f)){
            a = atoi(strtok(buf, " "));
            b = atoi(strtok(NULL, " "));
            adj[a-1] = add_adj_list(adj[a-1], b); //this operation takes O(1)
            adj[b-1] = add_adj_list(adj[b-1], a); //this operation takes O(1)
        }
        gettimeofday(&tv2, NULL);
        creating_representations[c-1][3] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
        ////PRINT ADJ
//    for(int i=0; i<n; i++){
//        printf("Node %d\n", i+1);
//        print_adj_list(adj[i]);
//    }

        for(int i=0; i<4; i++)
            printf("Time for adding for %d representation:  %f\n", i, creating_representations[c-1][i]);

        char name2[30];
        sprintf(name2, "all_comb_%d.txt", c);
        FILE * fp = fopen(name2, "r");
        fgets(buf, lenght, fp);
        int k = atoi(buf);
        int **pairs = malloc(sizeof(int *) * k);
        for(int i=0; i<k; i++)
            pairs[i] = calloc(2, sizeof(int));
        cnt = 0;
        while(fgets(buf, lenght, fp)){
            pairs[cnt][0] = atoi(strtok(buf, " "));
            pairs[cnt][1] = atoi(strtok(NULL, " "));
            cnt++;
        }
        fclose(fp);

        //// EDGE LIST SEARCHING
        int ok = 0;
        gettimeofday(&tv1, NULL);
        for(int i=0; i<k; i++){
            int found = search_edge_list(head, pairs[i][0], pairs[i][1]);
            if(found)
                ok ++;
        }
        gettimeofday(&tv2, NULL);
        searching[c-1][0] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec)) / k;
        printf("For edge list found: %d, time=%f\n", ok, searching[c-1][0]);

        //// NEIGHBORHOOD MATRIX SEARCHING
        ok = 0;
        gettimeofday(&tv1, NULL);
        for(int i=0; i<k; i++){
            a = pairs[i][0];
            b = pairs[i][1];
            if(neighborhood[a-1][b-1] == 1)
                ok ++;
        }
        gettimeofday(&tv2, NULL);
        searching[c-1][1] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec)) / k;
        printf("For neighborhood matrix found: %d, time=%f\n", ok, searching[c-1][1]);

        //// INCIDENCE MATRIX SEARCHING
        ok = 0;
        gettimeofday(&tv1, NULL);
        for(int i=0; i<k; i++){
            a = pairs[i][0];
            b = pairs[i][1];
            //remark m = n^2
            for(int x=0; x<m; x++){
                if(incidence[a-1][x] == 1 && incidence[b-1][x] == 1){
                    ok++;
                    break;
                }
            }
        }
        gettimeofday(&tv2, NULL);
        searching[c-1][2] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec)) / k;
        printf("For incidence matrix found: %d, time=%f\n", ok, searching[c-1][2]);

        //// INCIDENCE ADJ SEARCHING
        ok = 0;
        gettimeofday(&tv1, NULL);
        for(int i=0; i<k; i++){
            a = pairs[i][0];
            b = pairs[i][1];
            int found = search_adj_list(adj[a-1], b);
            if(found)
                ok ++;
        }
        gettimeofday(&tv2, NULL);
        searching[c-1][3] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec)) / k;
        printf("For adj list found: %d, time=%f\n", ok, searching[c-1][3]);



        for(int i=0; i<k; i++){
            free(pairs[i]);
        }
        free(pairs);
        free_edge_list(head);
        for(int i=0; i<n; i++){
            free(neighborhood[i]);
        }
        free(neighborhood);
        for(int i=0; i<n; i++){
            free(incidence[i]);
        }
        free(incidence);
        for(int i=0; i<n; i++){
            free_adj_list(adj[i]);
        }
        free(adj);
        free(buf);
        fclose(f);
    }

//    double creating_representations[10][4];
//    double searching[10][4];


    FILE * f = fopen("adding.txt", "w");

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            fprintf(f, "%f\n", creating_representations[j][i]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
//    f = fopen("searching.txt", "w");
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            fprintf(f, "%f\n", searching[j][i]);
//        }
//        fprintf(f, "\n");
//    }
//    fclose(f);

    return 0;
}
