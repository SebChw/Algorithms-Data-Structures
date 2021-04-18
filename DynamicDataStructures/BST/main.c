#include "BST.h"
#include <sys/time.h>

#define BILLION  1000000000.0
int main() {
    FILE *students;
    FILE * indices;
    FILE * outcomes;

    clock_t t;
    struct timeval  tv1, tv2;
    double measures[3][20];
    double measures300[2][60];
    int c = 0;

    char * buf = (char *)malloc(LENGTH * sizeof(char));
    indices = fopen("indices300k.txt", "r");
    if (indices == NULL){
        printf("failed to open the file!");
        return 1;
    }
    int amount = 300000;
    int depth[30];
    int index[amount];
    for (int i = 0; i < amount; ++i) {
        fgets(buf, LENGTH, indices);
        index[i] = atoi(buf);
    }
    //testing insert
    //struct node *root = create_BST(students);
    struct node * root = NULL;
    //measuring time of inserting

 //   Lets measure time of deleting
//    for (int i = 0; i < 6; ++i) {
//        printf("deleting %d\n", i);
//        students = fopen("sorted_students.txt","r");
//        if (students == NULL) {
//            printf("failed to open the file!");
//            return -1;
//        }
//        for (int j = 0; j < (i+1)*5000 ; ++j) {
//            fgets(buf, LENGTH, students);
//            struct student * s = (struct student *)malloc(sizeof(struct student));
//            char * token = strtok(buf," ");
//            strcpy(s->first_name, token);
//            token = strtok(NULL," ");
//            strcpy(s->second_name, token);
//            token = strtok(NULL, " ");
//            s->index = atoi(token);
//            root = insert(root, s, &c);
//        }
//        gettimeofday(&tv1, NULL);
//        int deleted = 0;
//        for (int j = 0; j < (i+1) * 5000; ++j) {
//            root = delete(root, index[j]);
//            if(root) deleted++;
//        }
//        if(!root) printf("Deleted all elements! \n");
//        gettimeofday(&tv2, NULL);
//        measures[2][i] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
//        printf("%lf\n", measures[2][i]);
//    }


    students = fopen("test_students300k.txt","r");
    if (students == NULL) {
        printf("failed to open the file!");
        return 1;
    }

    //int i = 0 ; //to count how many elements we've added
    int j = 0;
    // to count how many times we do insert function
    int power = 2;

    for (int i = 0; i < amount; ++i) {

        fgets(buf, LENGTH, students);
        if (i%5000 == 0){
            printf("Inserting %d", i);
            gettimeofday(&tv1, NULL);
        }
//        to measure in exponential steps
//        if (i % power == 0 && i != 0) {
//            power *=2;
//            printf("Tyle operacji sie wykonalo na 1 element %d \n", c/(i - i/2));
//            depth[j] = c/(i - i/2);
//            c = 0;
//            j++;
//
//        }

        struct student * s = (struct student *)malloc(sizeof(struct student));
        char * token = strtok(buf," ");
        strcpy(s->first_name, token);
        token = strtok(NULL," ");
        strcpy(s->second_name, token);
        token = strtok(NULL, " ");
        s->index = atoi(token);
        root = insert(root, s, &c);


//to measure TIME !!!
        if(i % 5000 == 4999 ){
            t = clock() - t;
            gettimeofday(&tv2, NULL);
            //printf("finish timer  power= %d\n", power);
            //printf("time needed to add one element %lf",);
            //printf("Tyle operacji sie wykonalo na 1 element %d\n", c/(power- power/2));
            if (j == 0)
                measures300[0][j] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
            else
                measures300[0][j] = measures300[0][j-1] + ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
            //now lets measure time of searching
            gettimeofday(&tv1, NULL);
            for (int k = 0; k < (j+1) * 5000 - 1; ++k) {
                search(root, index[k]);
            }
            gettimeofday(&tv2, NULL);
            measures300[1][j] = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +  (double) (tv2.tv_sec - tv1.tv_sec));
            j++;
        }

    }



   free(buf);



//    inorder(root);
   // preorder(root);
    //postorder(root);
    printf("Tree is Balanced: %d\n",isBalanced(root));
    printf("Tree is BST: %d\n" , isBST(root));
    free_memory(root);

    //Adding outcomes to file
    outcomes = fopen("outcomes300k.txt", "w");

    for (int j = 0; j < 60; ++j) {

       fprintf(outcomes,"%d %lf\n",j*5000 + 5000, measures300[0][j]);
       fprintf(outcomes,"%d %lf\n",j*5000 + 5000, measures300[1][j]);
      // fprintf(outcomes,"%d %lf\n",j*5000 + 5000, measures[2][j]);

    }
//    power = 2;
//    FILE * recursive_depth = fopen("recursive_BST.txt", "w");
//    for (int i = 0; i < 18; ++i) {
//        fprintf(recursive_depth, "%d %d\n", power , depth[i]);
//        power *= 2;
//    }
    return 0;
}
