#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) {
        printf("ошибка выделения памяти\n");
        return;
    }
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

void generate_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}
void copy_array(int source[], int copied[], int n) {
    for (int i = 0; i < n; i++) {
        copied[i] = source[i];
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {10, 1000, 10000, 100000};
    int num_sizes = 4;
    printf("размер | пузырек | вставки | слияние\n");
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* original = malloc(n * sizeof(int));
        generate_array(original, n);
        printf("%6d | ", n);
        if (n <= 10000) {
            int* arr = malloc(n * sizeof(int));
            copy_array(original, arr, n);
            clock_t start = clock();
            bubble_sort(arr, n);
            clock_t end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("%7.3f | ", time);
            free(arr);
        } else {
            printf("  долго | ");
        }
        if (n <= 10000) {
            int* arr = malloc(n * sizeof(int));
            copy_array(original, arr, n);
            clock_t start = clock();
            insertion_sort(arr, n);
            clock_t end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("%7.3f | ", time);
            free(arr);
        } else {
            printf("  долго | ");
        }
        int* arr = malloc(n * sizeof(int));
        copy_array(original, arr, n);
        clock_t start = clock();
        merge_sort(arr, 0, n-1);
        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%7.3f\n", time);
        
        free(arr);
        free(original);
    }
    return 0;
}
