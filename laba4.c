#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int m[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (m[j] > m[j+1]) {
                int x = m[j];
                m[j] = m[j+1];
                m[j+1] = x;
            }
        }
    }
}

void insertion_sort(int m[], int n) {
    for (int i = 1; i < n; i++) {
        int q = m[i];
        int j = i-1;
        while (j >= 0 && m[j] > q) {
            m[j+1] = m[j];
            j--;
        }
        m[j+1] = q;
    }
}

void merge(int m[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) {
        printf("ошибка выделения памяти\n");
        return;
    }
    for (int i = 0; i < n1; i++) L[i] = m[left + i];
    for (int i = 0; i < n2; i++) R[i] = m[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) m[k++] = L[i++];
        else m[k++] = R[j++];
    }
    while (i < n1) m[k++] = L[i++];
    while (j < n2) m[k++] = R[j++];
    free(L);
    free(R);
}

void merge_sort(int m[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(m, left, mid);
        merge_sort(m, mid+1, right);
        merge(m, left, mid, right);
    }
}

void generate_array(int m[], int n) {
    for (int i = 0; i < n; i++) {
        m[i] = rand() % 1000;
    }
}
void copy_array(int ist[], int cop[], int n) {
    for (int i = 0; i < n; i++) {
        cop[i] = ist[i];
    }
}

int main() {
    srand(time(NULL));
    int s[] = {10, 1000, 10000, 100000};
    int ns = 4;
    printf("размер | пузырек | вставки | слияние\n");
    for (int i = 0; i < ns; i++) {
        int n = s[i];
        int* u = malloc(n * sizeof(int));
        generate_array(u, n);
        printf("%6d | ", n);
        if (n <= 10000) {
            int* m = malloc(n * sizeof(int));
            copy_array(u, m, n);
            clock_t start = clock();
            bubble_sort(m, n);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("%7.3f | ", time);
            free(m);
        } else {
            printf("  долго | ");
        }
        if (n <= 10000) {
            int* arr = malloc(n * sizeof(int));
            copy_array(u, m, n);
            clock_t start = clock();
            insertion_sort(m, n);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("%7.3f | ", time);
            free(m);
        } else {
            printf("  долго | ");
        }
        int* m = malloc(n * sizeof(int));
        copy_array(u, m, n);
        clock_t start = clock();
        merge_sort(m, 0, n-1);
        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%7.3f\n", time);
        
        free(m);
        free(u);
    }
    return 0;
}
