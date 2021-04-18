#include "BalancedBST.h"
#include <sys/time.h>
int main() {
    FILE * students; //creates file handler for students list
    FILE * indices_file = fopen("indices300k.txt", "r");
    FILE * outcomes;
    FILE * outcomes2;


    struct timeval  tv1, tv2;
    double measures[3][20];
    double measures2[3][20];


    double measures300[2][60];

    int depth[60];

    int amount = 300000;
    int indices[amount];

    char * buf = (char *)malloc(LENGTH * sizeof(char));
    char * buf2 = (char *)malloc(LENGTH * sizeof(char));
    for (int i = 0; i < amount; ++i) {

        fgets(buf,LENGTH, indices_file);
        indices[i] = atoi(buf);
    }

    int j = 0;

    struct node * head, * tmp;
    struct BalancedBST * root = NULL;
    int n = 300000;

    head = NULL;
    //MEASURING TIME OF DELETING 
//    for (int i = 0; i < 20 ; ++i) {
//        printf("deleting %d\n", i);
//        students = fopen("test_students.txt","r");
//        if (students == NULL) {
//            printf("failed to open the file!");
//            return -1;
//        }
//        for (int k = 0; k < (i+1) * 5000; ++k) {
//            fgets(buf, LENGTH, students);
//            strcpy(buf2, buf);
//            insert(&head, buf);
//
//            struct student * s = (struct student *)malloc(sizeof(struct student));
//            char * token = strtok(buf2, " ");
//            strcpy(s->first_name, token);
//            token = strtok(NULL, " ");
//            strcpy(s->second_name, token);
//            token = strtok(NULL, " ");
//            s->index = atoi(token);
//            root = insertBBST(root, s);
//        }
//        gettimeofday(&tv1, NULL);
//        //delete linked list
//        for (int k = 0; k < (i+1) * 5000 -1 ; ++k) {
//            //printf("%d\n",indices[k]);
//            head = delete(head, indices[k]);
//        }
//        gettimeofday(&tv2, NULL);
//        measures[2][i] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
//
//        //delete BBST
//        gettimeofday(&tv1, NULL);
//        //int deleted = 0;
//        for (int k = 0; k < (i+1) * 5000; ++k) {
//            root= deleteBBST(root, indices[k]);
//
//            //if(root) deleted++;
//        }
//        //if(!root) printf("DELETED ALL ELEMENTS, deleted %d elements\n", deleted);
//        gettimeofday(&tv2, NULL);
//        measures2[2][i] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
//        //printf("Time measured %lf\n", measures2[2][j]);
//        fclose(students);
//    }
//    free(buf2);

    students = fopen("test_students300k.txt","r");
    if (students == NULL) {
        printf("failed to open the file!");
        return -1;
    }

    //MEASURING TIME OF INSERTING
    //LINKED LIST
//    for (int i = 0; i < n; ++i) {
//
//        if (i%5000 == 0){
//            printf("inserting Linked %d\n",i);
//            gettimeofday(&tv1, NULL);
//        }
//        fgets(buf, LENGTH, students);
//        insert(&head, buf);
//
//        if(i % 5000 == 4999 ){
//            t = clock() - t;
//            gettimeofday(&tv2, NULL);
//            //printf("finish timer  power= %d\n", power);
//            //printf("time needed to add one element %lf",);
//            //printf("Tyle operacji sie wykonalo na 1 element %d\n", c/(power- power/2));
//            if (j == 0)
//                measures[0][j] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
//            else
//                measures[0][j] = measures[0][j-1] + ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
//            //Now lets search for those 5k elements
//            gettimeofday(&tv1, NULL);
//            for (int k = 0; k < (j+1)*5000 - 1 ; ++k) {
//                search(head,indices[k]);
//            }
//            gettimeofday(&tv2, NULL);
//            measures[1][j] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
//
//            j++;
//        }
//
//    }
//
//


    printf("NOW BBST!\n");
    fclose(students);
    students = fopen("test_students300k.txt","r");
    j=0;
    printf("INSERTING!\n");
    // to count how many times we do insert function
    int power = 2;
    int c = 0; //counting recursion depth

    for (int i = 0; i < n; ++i) {
        //measuring time
        if (i%5000 == 0){
            printf("inserting BBST %d\n",i);

            gettimeofday(&tv1, NULL);
        }
//measuring depth
//        if (i % power == 0 && i != 0) {
//            power *=2;
//            printf("Tyle operacji sie wykonalo na 1 element %d \n", c/(i - i/2));
//            depth[j] = c/(i - i/2);
//            c = 0;
//            j++;
//
//        }
        fgets(buf, LENGTH, students);
        struct student * s = (struct student *)malloc(sizeof(struct student));
        char * token = strtok(buf, " ");
        strcpy(s->first_name, token);
        token = strtok(NULL, " ");
        strcpy(s->second_name, token);
        token = strtok(NULL, " ");
        s->index = atoi(token);
        root = insertBBST(root, s, &c);

        //measuring time
        if(i % 5000 == 4999 ){

            gettimeofday(&tv2, NULL);
            if (j == 0)
                measures300[0][j] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
            else
                measures300[0][j] = measures300[0][j-1] + ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
                //Now lets search for those 5k elements
            gettimeofday(&tv1, NULL);
            for (int k = 0; k < (j+1)*5000 - 1 ; ++k) {
                struct student * s = searchBBST(root,indices[k]);
            }
            gettimeofday(&tv2, NULL);
            measures300[1][j] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));

            j++;
        }
    }
    printf("Tree is BST %d\n", isBST(root));
    printf("Tree is balanced %d", isBalanced(root));


 //   freeing the memory
    while(head!= NULL){
        tmp = head;
        head = head->next;
        //we allocate statically
        //free(tmp->s->second_name);
        //free(tmp->s->first_name);
        free(tmp->s);
        free(tmp);

    }
    free(buf);
//    outcomes = fopen("outcomesLinkedList.txt", "w");
//    //power = 2;
//    for (int j = 0; j < 20; ++j) {
//
//        fprintf(outcomes,"%d %lf\n",j*5000 + 5000,measures[0][j]);
//        fprintf(outcomes,"%d %lf\n",j*5000 + 5000,measures[1][j]);
//        fprintf(outcomes,"%d %lf\n",j*5000 + 5000,measures[2][j]);
//        //power *= 2;
//    }

    outcomes2 = fopen("outcomesBBST300.txt", "w");

    //power = 2;
    for (int j = 0; j < 60; ++j) {

        fprintf(outcomes2,"%d %lf\n",j*5000 + 5000,measures300[0][j]);
        fprintf(outcomes2,"%d %lf\n",j*5000 + 5000,measures300[1][j]);
        //printf("Measured time %lf\n" , measures2[2][j]);
        //fprintf(outcomes2,"%d %lf\n",j*5000 + 5000,measures2[2][j]);
        //power *= 2;
    }
   // fclose(outcomes);
   fclose(outcomes2);

//    power = 2;
//    FILE * recursive_depth = fopen("recursive_BBST.txt", "w");
//    for (int i = 0; i < 18; ++i) {
//        fprintf(recursive_depth, "%d %d\n", power , depth[i]);
//        power *= 2;
//    }
//    fclose(recursive_depth);
    return 0;

}
