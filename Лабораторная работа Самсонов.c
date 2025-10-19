#include <stdio.h>
#include <stdlib.h>

#define MAX_SEQUENCE_LENGTH 100

void find_sequences(int target, int numbers[], int m, 
                   int current_sequence[], int current_length,
                   int last_num) {
    
    if (target == 0) {
        printf("[");
        for (int i = 0; i < current_length; i++) {
            printf("%d", current_sequence[i]);
            if (i < current_length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        return;
    }
    
    if (target < 0) {
        return;
    }
    
    for (int i = 0; i < m; i++) {
        int num = numbers[i];
        
        if (num != last_num) {
            current_sequence[current_length] = num;
            find_sequences(target - num, numbers, m, 
                          current_sequence, current_length + 1, num);
        }
    }
}

int main() {
    int N, M;
    
    printf("Enter N: ");
    scanf("%d", &N);
    
    printf("Enter M: ");
    scanf("%d", &M);
    
    int* S = (int*)malloc(M * sizeof(int));
    if (S == NULL) {
        printf("Memory error!\n");
        return 1;
    }
    
    printf("Enter set S:\n");
    for (int i = 0; i < M; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &S[i]);
    }
    
    int* current_sequence = (int*)malloc(MAX_SEQUENCE_LENGTH * sizeof(int));
    if (current_sequence == NULL) {
        printf("Memory error!\n");
        free(S);
        return 1;
    }
    
    printf("\nSequences from {");
    for (int i = 0; i < M; i++) {
        printf("%d", S[i]);
        if (i < M - 1) printf(", ");
    }
    printf("} with sum %d:\n", N);
    
    find_sequences(N, S, M, current_sequence, 0, -1);
    
    free(S);
    free(current_sequence);
    
    return 0;
}
