#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct list{
    int node;
    struct list *next;
};

void add_list(struct list **head, int a){
    struct list *x = malloc(sizeof(*x));
    x->node = a;
    x->next = NULL;
    if(*head == NULL){
        *head = x;
        return;
    }
    struct list *curr = *head;
    while(curr->next != NULL)
        curr = curr -> next;
    curr->next = x;
}

void free_list(struct list *head){
    struct list *curr = head;
    struct list *tmp;
    while (curr != NULL){
        tmp = curr;
        curr = curr -> next;
        free(tmp);
    }
}

void print_list(struct list *head){
    struct list *curr = head;
    while(curr != NULL){
        printf("%d\n", curr->node);
        curr = curr->next;
    }
}

void pop(struct list **head){
    struct list *x = *head;
    *head =( *head)->next;
    free(x);
}

int main() {
    int ns[20] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};
    double times[20];
    for(int it=0; it<20; ++it){
        int n = ns[it];
        struct list **adj = malloc(sizeof(**adj) * n);
        for(int i=0; i<n; i++){
            adj[i] = NULL;
        }

        char name[30];
        sprintf(name, "dag_%d.txt", it);

        FILE * f = fopen(name, "r");
        struct timeval  tv1, tv2;

        int length = 200*n;
        char * line = malloc(sizeof(char) * length);
        int *in = calloc(n, sizeof(int));

        while(fgets(line, length, f)){
            if(line[0] == '#')
                continue;
            char *p;
            p = strtok(line, " ");
            int a, node;
            node = atoi(p);
            int first = 1;
            while(p){
                if(first){
                    first = 0;
                }
                else{
                    a = atoi(p);
                    add_list(&adj[node], a);
                    ++in[a]; //in degree to node a
                }
                p = strtok(NULL, " ");
            }
        }

        fclose(f);


        ////DO TOPO SEARCH
        gettimeofday(&tv1, NULL);

        struct list *q = NULL;
        struct list *topo = NULL;

        for(int i=0; i<n; ++i){
            if(in[i] == 0)
                add_list(&q, i);
        }

        while(q != NULL){
            int tmp = q->node;
            pop(&q);
            add_list(&topo, tmp);
            struct list *curr = adj[tmp];
            while(curr != NULL){
                int node = curr->node;
                --in[node];
                if(in[node] == 0) add_list(&q, node);
                curr = curr->next;
            }
        }
        gettimeofday(&tv2, NULL);
        //if(it==7) print_list(topo);
        double tmp = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
        printf("Time measured for n=%d - \t %.10f\n", ns[it], tmp);
        times[it] = tmp;

        for(int i=0; i<n; i++){
            free_list(adj[i]);
        }
        free(adj);
        free_list(q);
        free_list(topo);
        free(line);
        free(in);
    }

    FILE *fp = fopen("dag_times.txt", "w");

    for(int i=0; i<20; ++i){
        fprintf(fp, "%f\n", times[i]);
    }

    fclose(fp);
    return 0;
}
