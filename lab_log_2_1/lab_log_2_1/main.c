#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

double multiply_matrices(int N) {
    int i, j, r;

    int* a = (int*)malloc((size_t)N * N * sizeof(int));
    int* b = (int*)malloc((size_t)N * N * sizeof(int));
    int* c = (int*)malloc((size_t)N * N * sizeof(int));

    if (!a || !b || !c) {
        printf("\n Ошибка: Не удалось выделить память для размера %d!\n", N);
        free(a); free(b); free(c);
        return -1.0;
    }

    for (size_t k = 0; k < (size_t)N * N; k++) {
        a[k] = rand() % 100 + 1;
        b[k] = rand() % 100 + 1;
        c[k] = 0;
    }

    printf("Идет расчет для N = %d (пожалуйста, подождите)...\n", N);

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

    free(a); free(b); free(c);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(NULL));

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("=== ЗАДАНИЕ 1: Измерение времени перемножения матриц ===\n\n");

    double results[7];

    for (int i = 0; i < count; i++) {
        results[i] = multiply_matrices(sizes[i]);
    }

    printf("\n\nИТОГОВАЯ ТАБЛИЦА РЕЗУЛЬТАТОВ:\n");
    printf("+-------------------+--------------------+\n");
    printf("|  Размер матрицы   |  Время счета (сек) |\n");
    printf("+-------------------+--------------------+\n");

    for (int i = 0; i < count; i++) {
        if (results[i] >= 0) {
            printf("|    %-5dx%-5d      |     %10.2f     |\n", sizes[i], sizes[i], results[i]);
        }
        else {
            printf("|    %-5dx%-5d      |     ОШИБКА ПАМЯТИ  |\n", sizes[i], sizes[i]);
        }
    }
    printf("+-------------------+--------------------+\n");

    return 0;
}