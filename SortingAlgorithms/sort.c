#include "sort.h"
//int heap_swaps = 0;
//int quick_swaps= 0;


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int * getArray(int size, int type){
    //Type
    // 0 - random , 1 - constant , 2 - increasing, 3 - decreasing
    // 4- A shape , 5 - V- Shape
    int* tab;
    tab = calloc(size, sizeof(int));

    int max = size*5; // maximum number is 5 times greater than number of elements

    if (type == 0) { //fill table with random numbers
        for (int i = 0; i < size; i++) {
            tab[i] = rand() % max;
        }
    }
    else if (type == 1) memset(tab, 0, size * sizeof(int)); // fill table with constant 0
    else if (type == 2) { //increasing
        for (int i = 0; i < size; i++) {
            tab[i] = i+1;
        }
    }
    else if (type == 3 ) { //increasing
        for (int i = 0; i < size; i++) {
            tab[i] = size - i;
        }
    }
    else if (type == 4) { //A shape
        for (int i = 0; i < size/2; i++) {
            tab[i] = 2*i + 1;
        }
        for (int i = size/2 ; i < size ; ++i) {
            tab[i] = 2*(size - i);
        }
    }
    else if(type==5){ //V shape
        for (int i = 0; i < size/2; i++) {
            tab[i] = 2*(size/2 - i - 1) + 1;
        }
        for (int i = size/2 ; i < size ; ++i) {
            tab[i] = 2*(i - size/2);
        }
    }
    return tab;
}



//Definitions of sorting functions
void insertionSort(const int *arr, int size, int pisz){
    int *arr_cp; //we are copying the array so each algoritm has exatcly the same array
    arr_cp = calloc(size, sizeof(int));

    memcpy(arr_cp, arr, size* sizeof(int));

    if (pisz){ //if this flag is on we save outcomes to the file
        fprintf(test,"Before sorting Insertion Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }

    for(int i = 1; i < size ; ++i){ // we iterate over each element in the array
        int key = arr[i]; // All considered elements from 0 to current i has to be greater than this element so we
        //consequtively push all greater elements to the right untill we met smaller one then we insert our
        //key after the smaller and repeat until we do it for all elements.
        int j = i - 1; // pointer on first predecessor
        //until we find less element or we are to move into forbidden index we swap and go further to the left
        while (arr_cp[j] > key && j >= 0){
            arr_cp[j+1] = arr_cp[j];
            j--;
        }
        arr_cp[j+1] = key; // then we finally insert our currently considered element in correct possition
    }
    if (pisz){ //when flag is on we print outcomes
        fprintf(test,"After sorting Insertion Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    free(arr_cp);
}



void selectionSort(const int *arr, int size, int pisz){
    int *arr_cp;
    arr_cp = calloc(size, sizeof(int));

    memcpy(arr_cp, arr, size* sizeof(int));

    if (pisz){
        fprintf(test,"Before sorting Selection Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    // we iterate over array
    for(int i = 0; i < size ; ++i){
        // we have two pointers, first points on the minimum value in each iteration the second points on consecutive elements
        int index = i; // index of the minimum value
        int j = i + 1;
        // when current element is least than index element (element considered as minimum) we change index to j
        for (j; j < size; ++j) { // this loops goes n-1,n-2,n-3 .... 1 times so overall it is O(n^2)
            if (arr_cp[index] > arr_cp[j]){
                index = j;
            }
        }
        swap(&arr_cp[i], &arr_cp[index]);

    }
    if (pisz){
        fprintf(test,"After sorting Selection Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    free(arr_cp);
}



void bubbleSort(const int *arr, int size, int pisz){
    int *arr_cp;
    arr_cp = calloc(size, sizeof(int));

    memcpy(arr_cp, arr, size* sizeof(int));

    if (pisz){
        fprintf(test,"Before sorting Bubble Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    // here the greatest element will always "bubble" at the end of the unsorted part of array
    // In this method we start sorting from the end, whereas in previous two we were starting from the beginning
    for(int i = 0; i < size ; ++i){
        for (int j = 0; j < size - i - 1 ; ++j) {
            if(arr_cp[j] > arr_cp[j + 1]){
                swap(&arr_cp[j], &arr_cp[j+1]);
            }
        }

    }
    if (pisz){
        fprintf(test,"After sorting Bubble Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    free(arr_cp);
}


void heapify(int *arr, int n, int i){
    //printf("YEY");
    int largest_idx = i; // we consider current node as largest at the beginning
    int left = i*2 + 1; // left child
    int right = i*2 + 2; // right child

    //now we select greatest element from three
    if (left < n && arr[left] > arr[largest_idx]){
        largest_idx = left;
    }
    if (right < n && arr[right] > arr[largest_idx]){
        largest_idx = right;
    }
    // if largest is not the parent we swap and again run heapify procedure
    if (largest_idx != i){
        //printf("sth happen");
        swap(&arr[largest_idx], &arr[i]);
        //heap_swaps++;
        heapify(arr, n , largest_idx);

    }

}


void heapSort(int *arr, int n){
    // at first we have to build maxheap from scratch
    // Binary heap is a complete binary tree (every level except possibly the last one is completely filled) so it can be represented with array
    // when indexes of child can be 2n + 1 or 2n + 2 when we start indexing from 0
    //Max heap has following attribute - Every parent node is greater than its children nodes.

    //At first we have to build max heap from scratch so we have to run heapify process for each node starting from the last with succesors.
    for (int i = n/2 - 1; i >=  0 ; i--) { // n/2 - 1 is the position of first node in binaryTree that has a child
        heapify(arr, n, i); // is is the index of the root node
    }

    //then after we swap first node with the last one we know that only root node isn't hapified so we can run heapify only for it
    for (int i = n-1; i > 0 ; i--) {
//        for (int i = 0; i <n; ++i) {
//            printf("%d, ", arr[i]);
//        }
//        printf("\n");
        swap(&arr[0], &arr[i]);
        //heap_swaps++;
        heapify(arr, i, 0);
    }
    //At first we do max heap which takes O(n) then the rest of procedure takes O(nlogn) which gives overall O(nlogn) but this O(n) may be a drawback
}


int partition(int *arr, int start, int end){
    //the goal of partition function is to put pivot element in its correct position
    //and also place all smaller elements to the left and all greater to the right
    int pivot = arr[(start+end)/2]; // we select pivot as a middle element

    swap(&arr[end], &arr[(start+end)/2]); // put pivot to the end of the array

    //move all smaller to the left and greater to the right using "Hoare’s Partitioning scheme"
    int i=(start-1);
    for(int j=start; j<= end-1; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
            //quick_swaps++;
        }
    }
    swap(&arr[i+1], &arr[end]); // swap pivot with first greater element and now pivot is in the correct position
    //quick_swaps++;
    return i+1; // return current index of the pivot
}



void quickSort(int *arr, int start, int end){
//    if (start < end){
//        printf("DZIALAM\n");
//        int mid = partition(arr, start, end);
//
//        quickSort(arr, start, mid-1);
//        quickSort(arr, mid+1, end);
//    }
//Here we have to use Tail Recursion, because we obtained stack overflows in the worst cases
    while(start < end) {
        int mid = partition(arr, start, end);
        if (mid - start <= end-(mid+1)){
            quickSort(arr, start, mid);
            start = mid+1;
        }
        else{
            quickSort(arr, mid+1, end);
            end = mid;
        }
    }
}


void merge(int *arr, int left, int middle, int right){
    // we have to copy two subbarts into two new arrays

    int len1 = middle - left + 1; // length of the first array
    int len2 = right - middle; //length

    int leftArray[len1], rightArray[len2]; // we need copies of our partition

    for (int i = 0; i < len1; ++i) {
        leftArray[i] = arr[left+i]; //create left partition

    }

    for (int i = 0; i < len2; ++i) {
        rightArray[i] = arr[middle + 1 + i]; // create right partition
    }

    int i = 0, j = 0, k = left;
    //we compare element unless we "pop" all element from one partition
    while (i < len1 && j < len2){
        if(rightArray[j] > leftArray[i]){
            arr[k] = leftArray[i];
            i++;
        } else{
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    //then we know that one of the partition is empty we have to move all element from the second which is not
    //or sometimes it may happen that both will be empty
    while (i < len1){
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < len2){
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}


void mergeSort(int *arr, int left, int right){

    if(left < right){ // we constantly divide arrays into halves until we obtain arrays of size 1
        int m = left + ((right - left) / 2); // we can just write (left + right)/ 2 but when arrays are really huge it may led to errors
        //remember that integer division always floor the result
        mergeSort(arr, left, m);
        mergeSort(arr, m+1, right);

        merge(arr, left, m, right);
    }
}



void chooseSort(const int *arr, int size, int type, int pisz){
    int *arr_cp;
    arr_cp = calloc(size, sizeof(int));

    memcpy(arr_cp, arr, size* sizeof(int));
    //printf("Dostalem tablice");
    if (pisz){
        fprintf(test,"Before sorting\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }

    if(type == 0) heapSort(arr_cp, size);
    else if (type == 1) quickSort(arr_cp,0, size-1);
    else if (type == 2) mergeSort(arr_cp,0,size-1);
    if (pisz){
        fprintf(test,"After sorting\n");
        for (int i = 0; i < size; ++i) {
           fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }

    //if (quick_swaps != 0) printf("Heap swaps = %d   Quick swaps = %d\n", heap_swaps, quick_swaps);
    free(arr_cp);
}


void shellSort(const int *arr, int size, int pisz){
    int *arr_cp;
    arr_cp = calloc(size, sizeof(int));

    memcpy(arr_cp, arr, size* sizeof(int));

    if (pisz){
        fprintf(test,"Before sorting Shell Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    // this one works similarly to insertion sort but at first we compare elements that are far away from one another, and then we make tha gap
    //beetwen them smaller and smaller, eventually our gap will always reduce to 1
    // interval sequence N/2 , N/4 , N/8 .... 1
    for (int interval = size/2 ; interval > 0 ; interval/=2) {
        for (int i = interval; i < size ; ++i) {
            int temp = arr_cp[i];
            int j;
            // here we do sth similar as in the insertion sort
            for (j = i; j >=interval && arr_cp[j-interval] > temp ; j-= interval) {
                arr_cp[j] = arr_cp[j-interval];
            }
            arr_cp[j] = temp;
        }

    }

    if (pisz){
        fprintf(test,"After sorting Shell Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr_cp[i]);
        }
        fprintf(test,"\n");
    }
    free(arr_cp);
}


void countingSort(const int *arr, int size, int pisz){
    if (pisz){
        fprintf(test,"Before sorting Counting Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", arr[i]);
        }
        fprintf(test,"\n");
    }
    int *sorted ;
    sorted = calloc(size, sizeof(int));

    //create buckets, size of that array has to be equal to greates possible element in our array to sort
    //but we don't know greatest element so we have to create usually much greater one
    //and this is bigger drawback of counting sort
    int bucket_size = size * 5;
    int *buckets;
    buckets = calloc(bucket_size, sizeof(int));
    //we fill array with zeroes
    memset(buckets, 0, bucket_size * sizeof(int));
//    for (int i = 0; i < bucket_size; ++i) {
//        if(buckets[i] != 0){
//            printf("ERR");
//        }
//    }
    // sum occurances of each element
    for (int i = 0; i < size; ++i) {
        buckets[arr[i]] += 1;
    }
    //make sth like prefix sum to get proper indices
    for (int i = 1; i < bucket_size ; ++i) {
        buckets[i] += buckets[i-1];
    }
    //fill sorted array and every time decrease counter by 1
    for (int i = size - 1; i>=0; --i)
    {
        //printf("%d on position %d\n", arr[i], buckets[arr[i]]-1);
        sorted[buckets[arr[i]]-1] = arr[i];
        --buckets[arr[i]];
    }

    if (pisz){
        fprintf(test,"After sorting Counting Sort\n");
        for (int i = 0; i < size; ++i) {
            fprintf(test,"%d, ", sorted[i]);
        }
        fprintf(test,"\n");
    }
    free(buckets);
}


//Function to create file with sorted arrays by all methods
void createTest(){

    test = fopen("Test.txt", "w") ;

    int size = 100;
    int *to_sort = getArray(size,0);

    insertionSort(to_sort,size, 1);

    selectionSort(to_sort,size, 1);

    bubbleSort(to_sort,size, 1);

     chooseSort(to_sort, size,0, 1);
//
    chooseSort(to_sort, size,1, 1);

    chooseSort(to_sort, size,2, 1);

    shellSort(to_sort, size, 1);
//
    countingSort(to_sort, size, 1);

    fclose(test) ;
    free(to_sort);

}