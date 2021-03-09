#include <stdlib.h>
#include <iostream>

using namespace std;

bool isSorted(int array[], int size);
void bubbleSort(int array[], int size);
void swap(int* num1, int* num2);
double unsortedMetric(int array[], int size);
int* partition(int array[], int size);
void quickSort(int array[], int size);
int sizeOfSubArray(int* start, int* end);

const int CUT_OFF = 100000000;


int main() {
    int array[] = {2,5,1,4,7,4,6,21,100,7,45,2,3,45,43,49,65,123,2,34,54};
    quickSort(array, 21);
    for (int i = 0; i < 21; i++) {
        cout << array[i] << endl;
    }
    return 0;
}

void sort(int array[], int size) {
    if (size > CUT_OFF) {
        quickSort(array, size);
    } else if (isSorted(array, size)) {
        return;
    } else if (unsortedMetric(array, size) < .2) {
        bubbleSort(array, size);
    } else {
        quickSort(array, size);
    }
}

void bubbleSort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        bool noSwap = true;
        for (int j = 0; j < size; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                noSwap = false;
            }
        }
        if (noSwap) {
            break;
        }
    }
}

bool isSorted(int array[], int size) {
    for (int i = 1; i < size; i++) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}


void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
    return;
}

//modified from pseudocode on https://en.wikipedia.org/wiki/Quicksort
void quickSort(int array[], int size) {
    if (size > 1) {
        int* pivot = partition(array, size);
        quickSort(array, sizeOfSubArray(array, pivot));
        quickSort(pivot + 1, (size - sizeOfSubArray(array, pivot)));
    }
}

int* partition(int array[], int size) {
    int* pivot = &array[size - 1];
    int* ptr1 = array;
    for (int i = 0; i < size; i++) {
        if (array[i] < *pivot) {
            swap(ptr1, &array[i]);
            ptr1++;
        }
    }
    swap(pivot, ptr1);
    return ptr1;
}

int sizeOfSubArray(int* start, int* end) {
    return (int) (end - start);
}





double unsortedMetric(int array[], int size) {
    int acc = 0;
    for (int i = 1; i < size; i++) {
        if (array[i - 1] > array[i]) {
            acc++;
        }
    }
    double metric = ( (double) acc) / ( (double) size);
    return metric;
}

