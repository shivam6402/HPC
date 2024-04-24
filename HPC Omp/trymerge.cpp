#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For clock()
#include <omp.h>    // OpenMP
#include <chrono>   // For std::chrono

// Sequential Merge Sort
void mergeSortSequential(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortSequential(arr, left, mid);
        mergeSortSequential(arr, mid + 1, right);

        // Merge the sorted halves
        int temp[right - left + 1];
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (int p = 0; p < k; p++) {
            arr[left + p] = temp[p];
        }
    }
}

// Parallel Merge Sort using OpenMP
void mergeSortParallel(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, left, mid);
            #pragma omp section
            mergeSortParallel(arr, mid + 1, right);
        }

        // Merge the sorted halves
        int temp[right - left + 1];
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (int p = 0; p < k; p++) {
            arr[left + p] = temp[p];
        }
    }
}

int main() {
    int size;
    std::cout << "Enter the number of elements: ";
    std::cin >> size;

    int arr[size];
    std::cout << "Enter " << size << " integers:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    auto startSeqMerge = std::chrono::steady_clock::now();
    mergeSortSequential(arr, 0, size - 1);
    auto endSeqMerge = std::chrono::steady_clock::now();
    double timeSeqMerge = std::chrono::duration<double>(endSeqMerge - startSeqMerge).count();

    auto startParMerge = std::chrono::steady_clock::now();
    mergeSortParallel(arr, 0, size - 1);
    auto endParMerge = std::chrono::steady_clock::now();
    double timeParMerge = std::chrono::duration<double>(endParMerge - startParMerge).count();

    // Print execution times
    std::cout << "Sequential Merge Sort Time: " << timeSeqMerge << " seconds" << std::endl;
    std::cout << "Parallel Merge Sort Time: " << timeParMerge << " seconds" << std::endl;

    for(int i = 0; i<size;i++){
        std :: cout << arr[i] << " ";
    }

    return 0;
}

