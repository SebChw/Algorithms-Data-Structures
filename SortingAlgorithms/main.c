#include "sort.h"
#include <unistd.h>
#include <sys/time.h>



#define BILLION  1000000000.0

int main()
{
    //Initializing seed
    srand(time(NULL));

    createTest(); // creating file with sorted arrays

    struct timespec start, end; //variables needed to measure time

    int *to_sort; // we will use this array all the time

    //EXPERIMENT 1
    int measuring_points = 20;
    int size[measuring_points];

    for (int i = 0; i < measuring_points; ++i) {
        size[i] = i * 5000 + 100;
    }

//
    double measures1[4][measuring_points]; // aray to store times for each method we have 4 methods and for each we measure measuring_points time
    for(int i=0; i<measuring_points; i++){
        to_sort = getArray(size[i],0); //generating new array of greater size with type 0 - random distribution
        printf("Run %d\n", i+1); // debugging print

        clock_gettime(CLOCK_REALTIME, &start); // start of the interval
        bubbleSort(to_sort,size[i],0); // sorting
        clock_gettime(CLOCK_REALTIME, &end); // end of the interval

        measures1[0][i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION; // adding difference to the aaray
        //And we do the same for each Sorting method


        clock_gettime(CLOCK_REALTIME, &start);
        chooseSort(to_sort, size[i],0, 0);
        clock_gettime(CLOCK_REALTIME, &end);

        measures1[1][i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;


        clock_gettime(CLOCK_REALTIME, &start);
        countingSort(to_sort,size[i], 0);
        clock_gettime(CLOCK_REALTIME, &end);

        measures1[2][i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;


        clock_gettime(CLOCK_REALTIME, &start);
        shellSort(to_sort,size[i], 0);
        clock_gettime(CLOCK_REALTIME, &end);

        measures1[3][i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;


        free(to_sort); //free the array
    }

//EXPERIMENT 2

    int size2[measuring_points];

    //generating measuring points
    for (int j = 0; j < measuring_points; ++j) {
        size2[j] = j * 10000 + 1000;
    }


    double measures2[18][measuring_points]; // 18 rows since we have 3 methods and for each 6 kind of data
    for (int i = 0; i < 6; ++i) { // iterating over types of data

        for (int j = 0; j < 20; ++j) { //iterating over measuring points

            to_sort = getArray(size2[j],i);
            printf("RUN %d. %d\n", i,j);

            clock_gettime(CLOCK_REALTIME, &start);
            chooseSort(to_sort, size2[j],0, 0);
            clock_gettime(CLOCK_REALTIME, &end);

            measures2[i*3][j] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;


            clock_gettime(CLOCK_REALTIME, &start);
            chooseSort(to_sort, size2[j],1, 0);
            clock_gettime(CLOCK_REALTIME, &end);

            measures2[i*3  + 1][j] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;

            clock_gettime(CLOCK_REALTIME, &start);
            chooseSort(to_sort, size2[j],2, 0);
            clock_gettime(CLOCK_REALTIME, &end);

            measures2[i*3 + 2][j] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;


            free(to_sort);
        }


    }

//EXPERIMENT 3

FILE *filePointer3;
filePointer3 = fopen("pomiary3.txt", "w"); //creating file
double time = 0;
int size3[3] = {99999,100000,100001};
int types[3] = {0,4,5};
    fprintf(filePointer3, "0 - random , 4 - A shape, 5 - V shape\n");
    for (int i = 0; i < 3; ++i) { //iterating ofer sizes
        for (int j = 0; j < 3; ++j) { //iterating over types

            to_sort = getArray(size3[i], types[j]);

            printf("Run %d-%d\n", i, j);

            clock_gettime(CLOCK_REALTIME, &start);
            chooseSort(to_sort, size3[i], 1, 0);
            clock_gettime(CLOCK_REALTIME, &end);

            time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
            fprintf(filePointer3, "for %d elements and %d shape time: %lf\n", size3[i], types[j], time); //saving to file without safing to array
            free(to_sort);
        }
        fprintf(filePointer3, "\n");
    }
fclose(filePointer3);

//saving outcomes of first experiment
    FILE *filePointer;
    filePointer = fopen("pomiary1.txt", "w");



    if ( filePointer == NULL )
    {
        printf( "pomiary1.txt file failed to open." ) ;
    }
    else
    {
        // Write the dataToBeWritten into the file
        for(int i=0; i<4; i++){
            for(int j=0; j<measuring_points; j++){
                //printf("%lf\n", measures1[i][j]);
                fprintf(filePointer, "%lf\n", measures1[i][j]);
            }
            fprintf(filePointer, "\n\n");
        }

        // Closing the file using fclose()
        fclose(filePointer) ;

        printf("Data successfully written in file pomiary1.txt\n");
        printf("The file is now closed.") ;
    }


    FILE *filePointer2;
    filePointer2 = fopen("pomiary2.txt", "w");
    if ( filePointer2 == NULL )
    {
        printf( "pomiary2.txt file failed to open." ) ;
    }
    else
    {
        // Write the dataToBeWritten into the file
        for(int i=0; i<18; i++){
            for(int j=0; j<measuring_points; j++){
                //printf("%lf\n", measures2[i][j]);
                fprintf(filePointer2, "%lf\n", measures2[i][j]);
            }
            fprintf(filePointer2, "\n\n");
        }

        // Closing the file using fclose()
        fclose(filePointer2) ;

        printf("Data successfully written in file pomiary2.txt\n");
        printf("The file is now closed.") ;
    }

// chunk of code to run counting of swaps
//    //printf("Size of the array %d\n",size2[11]);
//    to_sort = getArray(size2[11],2);
//    chooseSort(to_sort, size2[11],0, 0);
//    chooseSort(to_sort, size2[11],1, 0);
    return 0;

}

