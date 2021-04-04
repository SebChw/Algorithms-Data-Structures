#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef SORTING_SORT_H
#define SORTING_SORT_H

FILE *test;

extern int heap_swaps;
extern int quick_swaps;

int * getArray(int size, int type);
void insertionSort(const int *arr, int size, int pisz);
void selectionSort(const int *arr, int size, int pisz);
void bubbleSort(const int *arr, int size, int pisz);
void chooseSort(const int *arr, int size, int type, int pisz);
void heapSort(int *arr, int n);
void heapify(int *arr, int n, int i);
void quickSort(int *arr, int start, int end);
void mergeSort(int *arr, int left, int right);
void merge(int *arr, int left, int middle, int right);
void shellSort(const int *arr, int size, int pisz);
void countingSort(const int *arr, int size, int pisz);
void swap(int* a, int* b);

void createTest();

#endif //SORTING_SORT_H
