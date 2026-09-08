#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define SIZE 10000

void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) {
    int i, j;
    int x, y;
    i = left; j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void run_test(const char* test_name, int* original, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    clock_t start, end;

    printf("--- Тест: %s ---\n", test_name);

    memcpy(arr, original, n * sizeof(int));
    start = clock();
    shell(arr, n);
    end = clock();
    printf("Shell:  %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    memcpy(arr, original, n * sizeof(int));
    start = clock();
    qs(arr, 0, n - 1);
    end = clock();
    printf("QS:     %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    memcpy(arr, original, n * sizeof(int));
    start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    end = clock();
    printf("qsort:  %f сек.\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(arr);
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(NULL));

    int* arr_rand = (int*)malloc(SIZE * sizeof(int));
    int* arr_asc = (int*)malloc(SIZE * sizeof(int));
    int* arr_desc = (int*)malloc(SIZE * sizeof(int));
    int* arr_half = (int*)malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++) {
        arr_rand[i] = rand() % 10000;
        arr_asc[i] = i;
        arr_desc[i] = SIZE - i;

        if (i < SIZE / 2)
            arr_half[i] = i;
        else
            arr_half[i] = SIZE - i;
    }

    printf("=== Задание 2: Сравнение сортировок (Размер %d) ===\n\n", SIZE);

    run_test("1. Случайный массив", arr_rand, SIZE);
    run_test("2. Возрастающий массив", arr_asc, SIZE);
    run_test("3. Убывающий массив", arr_desc, SIZE);
    run_test("4. Половина возрастает, половина убывает", arr_half, SIZE);

    free(arr_rand); free(arr_asc); free(arr_desc); free(arr_half);

    return 0;
}