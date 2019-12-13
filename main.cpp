#include <ctime>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>  // for high_resolution_clock

void bubbleSort(double* myArray, int size);
void selectionSort(double* myArray, int size);
void insertionSort(double* myArray, int size);
void quickSort(double* myArray, int low, int high);
int partition(double* myArray, int low, int high);
void swap(double* a, double* b);

int main(int argc, char** argv) {
    if(argc == 1) {
        std::cout << "Please provide a filename as a command argument" << std::endl;
        exit(0);
    }
	/*
    srand(std::time(0));
    //Generating 100000 unique doubles
    std::ofstream os(argv[1]);
    os << 100000 << std::endl;
    for(int i = 0; i < 100000; ++i) {
        os << rand() << '.' << rand() << std::endl;
    } */
    
    std::ifstream is(argv[1]);
    if(is.fail()) {
        std::cout << argv[1] << " could not be opened." << std::endl;
		exit(1);
    }
    int arraySize;
    is >> arraySize;
    if(is.fail()) {
        std::cout << "Could not read array size on first line" << std::endl;
		exit(2);
    }
    double* bubbleTestArray = new double[arraySize];
    double* selectionTestArray = new double[arraySize];
    double* insertionTestArray = new double[arraySize];
    double* quickTestArray = new double[arraySize];
    std::string temp;
    for(int i = 0; i < arraySize; ++i) {
        getline(is, temp);
        double data;
        is >> data;
        bubbleTestArray[i] = data;
        selectionTestArray[i] = data;
        insertionTestArray[i] = data;
        quickTestArray[i] = data;  
    }
    //Sort Arrays
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(bubbleTestArray, arraySize);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time of bubble sort: " << elapsed.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    selectionSort(selectionTestArray, arraySize);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Elapsed time of selection sort: " << elapsed.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    insertionSort(insertionTestArray, arraySize);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Elapsed time of insertion sort: " << elapsed.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    quickSort(quickTestArray, 0, arraySize-1);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Elapsed time of quick sort: " << elapsed.count() << " seconds." << std::endl;
    return 0;
}

void bubbleSort(double* myArray, int size) {
    int sizeMinusOne = size-1;
    double temp;
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < sizeMinusOne; ++j) {
            int jPlusOne = j+1;
            if(myArray[j] > myArray[jPlusOne]) {
                temp = myArray[jPlusOne];
                myArray[jPlusOne] = myArray[j];
                myArray[j] = temp;
            }
        }
    }
}

void selectionSort(double* myArray, int size) {
    int minIndex;
    double temp;
    for(int i = 0; i < size; ++i) {
        minIndex = i;
        for(int j = i + 1; j < size; ++j) {
            if(myArray[j] < myArray[minIndex]) {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            //swap(i, minIndex);
            temp = myArray[i];
            myArray[i] = myArray[minIndex];
            myArray[minIndex] = temp;
        }
    }
}

void insertionSort(double* myArray, int size) {
    for(int i = 1; i < size; ++i) {//marker
        double temp = myArray[i];  //Store marked item
        int j = i; //Where to start shifting
        while(j > 0 && myArray[j-1] >= temp) { //While the thing to the left is larger, shift
            myArray[j] = myArray[j-1];
            --j;
        }
        myArray[j] = temp;
    }
}

//Quick sort needs a partition as well
void quickSort(double* myArray, int low, int high) {
    if(low < high) {
        int pivotIndex = partition(myArray, low, high); //Element at pivotIndex is in the right place
        quickSort(myArray, low, pivotIndex-1);
        quickSort(myArray, pivotIndex+1, high);
    }
}

//Partition is existent as well I guess
int partition(double* myArray, int low, int high) {
    //Pivot is going to be last element in index
    int pivot = myArray[high];
    
    int numLess = 0;
    for(int i = low; i <= high; ++i) {
        if(myArray[high] > myArray[i]) {
            swap(&myArray[i], &myArray[numLess + low]);
            ++numLess;
        }
    }
    swap(&myArray[numLess + low], &myArray[high]);
    return numLess+low;
}

//The most complicated function of them all
void swap(double* a, double* b)  
{  
    double t = *a;  
    *a = *b;  
    *b = t;  
}  