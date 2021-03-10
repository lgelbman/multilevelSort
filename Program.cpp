#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include <chrono>
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;

//using namespace std;

void sort(int array[], int size);
bool isSorted(int array[], int size);
void bubbleSort(int array[], int size);
void swap(int* num1, int* num2);
double unsortedMetric(int array[], int size);
int* partition(int array[], int size);
void quickSort(int array[], int size);
int sizeOfSubArray(int* start, int* end);
void fillArrayWithRandomNumbers(int* array);
void runMySort();
void runStandardSort();
template <typename Func>
long long TimeFunc(Func f);

const int CUT_OFF = 100000000;
const int arraySize = 1000000;
int* array1;
int* array2;


int main() {
    array1 = new int[arraySize];
    array2 = new int[arraySize];
    fillArrayWithRandomNumbers(array1);
    fillArrayWithRandomNumbers(array2);
    long long time1 = TimeFunc(runStandardSort);
    long long time2 = TimeFunc(runMySort);

    std::cout << "time using library: " << time1 << std::endl;
    std::cout << "time using our sort: " << time2 << std::endl;

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
    if (size >= 1) {
        int* pivot = partition(array, size);
        quickSort(array, (sizeOfSubArray(array, pivot) ));
        quickSort(pivot + 1, (size - sizeOfSubArray(array, pivot) - 1));
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
    //swap(pivot, ptr1);
    swap(ptr1, &array[size - 1]);
    return ptr1;
}

int sizeOfSubArray(int* start, int* end) {
    int size = (int) (end - start);
    return size;
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

void fillArrayWithRandomNumbers(int* array) {
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand() % 100;
    }
}


void runMySort() {
    sort(array1, arraySize);
}

void runStandardSort() {
    std::sort(array2, array2 + arraySize);
}

//copied from canvas
template <typename Func>
long long TimeFunc(Func f) {
    auto begin = steady_clock::now();
    f();
    auto end = steady_clock::now();
    return duration_cast<milliseconds>(end - begin).count();
}

