#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void multiply_matrices(int N) {
    int i, j, r;

    int* a = (int*)malloc(N * N * sizeof(int));
    int* b = (int*)malloc(N * N * sizeof(int));
    int* c = (int*)malloc(N * N * sizeof(int));

    if (!a || !b || !c) {
        printf("Размер %d: Ошибка выделения памяти!\n", N);
        free(a); free(b); free(c);
        return;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i * N + j] = rand() % 100 + 1;
            b[i * N + j] = rand() % 100 + 1;
        }
    }

    clock_t start = clock();

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int elem_c = 0;
            for (r = 0; r < N; r++) {
                elem_c += a[i * N + r] * b[r * N + j];
            }
            c[i * N + j] = elem_c;
        }
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Размер матрицы: %4dx%-4d | Время перемножения: %f сек.\n", N, N, time_taken);

    free(a);
    free(b);
    free(c);
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(NULL));

    int sizes[] = { 100, 200, 400, 1000, 2000 };
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("=== Задание 1: Замер времени перемножения матриц ===\n\n");
    for (int i = 0; i < count; i++) {
        multiply_matrices(sizes[i]);
    }

    return 0;
}