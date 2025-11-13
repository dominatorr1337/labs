#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Использование: %s <файл>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    int N, M;
    fscanf(file, "%d %d", &N, &M);
    int** matrix = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    printf("Матрица %dx%d:\n", N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    long long product = 1;
    int has_positive = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i + j < M - 1 && matrix[i][j] > 0) {
                product *= matrix[i][j];
                has_positive = 1;
            }
        }
    }
    
    if (has_positive) {
        printf("Произведение положительных выше побочной диагонали: %lld\n", product);
    } else {
        printf("Нет положительных элементов выше побочной диагонали\n");
    }

    if (M >= 2) {
        int min_val = matrix[0][1];
        int min_row = 0;
        
        for (int i = 1; i < N; i++) {
            if (matrix[i][1] < min_val) {
                min_val = matrix[i][1];
                min_row = i;
            }
        }
        printf("Минимальный во 2-ом столбце: matrix[%d][1] = %d\n", min_row, min_val);

        if (N >= 4 && M >= 3) {
            printf("До обмена: %d <-> %d\n", matrix[min_row][1], matrix[3][2]);
            
            int temp = matrix[min_row][1];
            matrix[min_row][1] = matrix[3][2];
            matrix[3][2] = temp;
            
            printf("После обмена: %d <-> %d\n", matrix[min_row][1], matrix[3][2]);
        }
    }

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}