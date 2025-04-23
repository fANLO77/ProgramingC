#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Глобальная переменная для подсчета сравнений
int C = 0;

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000; // Ограничим диапазон для удобства
    }
}

long long CheckSum(int A[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

int RunNumber(int A[], int n) {
    int runs = 1;
    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {
            runs++;
        }
    }
    return runs;
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Функция для вычисления количества шагов
int K_Sort(int n) {
    int i = 2, j = 0;
    while (i <= n) {
        i *= 2;
        j++;
    }
    j--;
    return j;
}

// Итеративная версия бинарного поиска
void BSearch1(int A[], int n, int X) {
    C = 0;
    int L = 0, R = n - 1, Find = 0, m;
    while (L <= R) {
        m = (int)((L + R) / 2);
        C++;
        if (A[m] == X) {
            Find = 1;
            break;
        }
        C++;
        if (A[m] < X) L = m + 1;
        else R = m - 1;
    }
}

// Рекурсивная версия бинарного поиска
void BSearch2(int A[], int n, int X) {
    C = 0;
    int L = 0, R = n - 1, Find = 0, m;
    while (L < R) {
        m = (int)((L + R) / 2);
        C++;
        if (A[m] < X) L = m + 1;
        else R = m;
    }
    C++;
    if (A[R] == X) Find = 1;
    else Find = 0;
}

int CompareInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void TeorTable() {
    printf("%-5s | %-10s | %-10s\n", "N", "BinarySearch1", "BinerySearch2");
    printf("----------------------------------------\n");
}

void ZnachTable(int n, int T1, int T2) {
    printf("%-5d | %-10d | %-10d\n", n, T1, T2);
    printf("----------------------------------------\n");
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    TeorTable();

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];
        int *A = (int *)malloc(n * sizeof(int));
        FillRand(A, n);

        // Сортируем массив для бинарного поиска
        qsort(A, n, sizeof(int), CompareInt);

        int key = A[n / 2]; // Ищем элемент, который находится в середине массива


        BSearch1(A, n, key);
        int C1 = C;

        BSearch2(A, n, key);
        int C2 = C;

        ZnachTable(n, C1, C2);

        free(A);
    }

    return 0;
}