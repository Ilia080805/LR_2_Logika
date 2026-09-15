#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

static int depth = 0;

void shell(int* items, int count) {
    int i, j, gap, k, x, a[5] = { 9, 5, 3, 2, 1 };
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

void qs_safe(int* items, int left, int right) {
    depth++;
    if (depth > 2500) {
        depth--;
        return;
    }

    int i = left, j = right;
    int x = items[(left + right) / 2], y;
    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i]; items[i] = items[j]; items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs_safe(items, left, j);
    if (i < right) qs_safe(items, i, right);

    depth--;
}

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void fill_arr(int* a, int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 0) a[i] = rand() % 10000;
        if (type == 1) a[i] = i;
        if (type == 2) a[i] = n - i;
        if (type == 3) a[i] = (i < n / 2) ? i : (n - i);
    }
}

double measure(void (*sort_fn)(int*, int), int* orig, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    memcpy(arr, orig, n * sizeof(int));

    depth = 0;
    clock_t start = clock();
    sort_fn(arr, n);
    clock_t end = clock();

    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void qs_wrap(int* a, int n) { qs_safe(a, 0, n - 1); }
void qsort_wrap(int* a, int n) { qsort(a, n, sizeof(int), compare_ints); }

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(NULL));

    int sizes[] = { 100, 1000, 10000 };

    printf("=== ÇÀÄÀÍÈÅ 2: ÒÀÁËÈÖÛ ÑÎÐÒÈÐÎÂÎÊ (ÏÎ ÄÎÑÊÅ) ===\n");

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        printf("\n---------------- N = %d ----------------\n", n);
        printf("+-----------+-----------+-----------+-----------+-----------+\n");
        printf("| data/sort | Ñëó÷àéíûé | Âîçðàñò.  | Óáûâàþù.  |   Ïèê     |\n");
        printf("+-----------+-----------+-----------+-----------+-----------+\n");

        int* orig_rand = (int*)malloc(n * sizeof(int)); fill_arr(orig_rand, n, 0);
        int* orig_asc = (int*)malloc(n * sizeof(int)); fill_arr(orig_asc, n, 1);
        int* orig_desc = (int*)malloc(n * sizeof(int)); fill_arr(orig_desc, n, 2);
        int* orig_peak = (int*)malloc(n * sizeof(int)); fill_arr(orig_peak, n, 3);

        printf("| Shell     | %9.4f | %9.4f | %9.4f | %9.4f |\n",
            measure(shell, orig_rand, n),
            measure(shell, orig_asc, n),
            measure(shell, orig_desc, n),
            measure(shell, orig_peak, n));

        printf("| qs        | %9.4f | %9.4f | %9.4f | %9.4f |\n",
            measure(qs_wrap, orig_rand, n),
            measure(qs_wrap, orig_asc, n),
            measure(qs_wrap, orig_desc, n),
            measure(qs_wrap, orig_peak, n));

        printf("| qsort     | %9.4f | %9.4f | %9.4f | %9.4f |\n",
            measure(qsort_wrap, orig_rand, n),
            measure(qsort_wrap, orig_asc, n),
            measure(qsort_wrap, orig_desc, n),
            measure(qsort_wrap, orig_peak, n));

        printf("+-----------+-----------+-----------+-----------+-----------+\n");

        free(orig_rand); free(orig_asc); free(orig_desc); free(orig_peak);
    }

    return 0;
}