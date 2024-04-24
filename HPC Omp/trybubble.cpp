#include <iostream>
#include <vector>
#include <chrono>    // For std::chrono
#include <omp.h>    // OpenMP

// Sequential Bubble Sort
void bubbleSortSequential(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP
void bubbleSortParallel(int* arr, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int size;
    std::cout << "Enter the number of integers: ";
    std::cin >> size;

    int arr[size];

    // Taking input from the user
    std::cout << "Enter " << size << " integers:\n";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    // Measure sequential bubble sort time
    auto startSeqBubble = std::chrono::steady_clock::now();
    bubbleSortSequential(arr, size);
    auto endSeqBubble = std::chrono::steady_clock::now();
    double timeSeqBubble = std::chrono::duration<double>(endSeqBubble - startSeqBubble).count();

    // Measure parallel bubble sort time
    auto startParBubble = std::chrono::steady_clock::now();
    bubbleSortParallel(arr, size);
    auto endParBubble = std::chrono::steady_clock::now();
    double timeParBubble = std::chrono::duration<double>(endParBubble - startParBubble).count();

    // Print sorted array
    std::cout << "Sorted array:\n";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Print execution times
    std::cout << "Sequential Bubble Sort Time: " << timeSeqBubble << " seconds\n";
    std::cout << "Parallel Bubble Sort Time: " << timeParBubble << " seconds\n";

    return 0;
}

