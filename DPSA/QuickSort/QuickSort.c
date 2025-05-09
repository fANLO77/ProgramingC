#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Глобальные переменные для отслеживания трудоемкости и глубины рекурсии
int trud = 0;       // Счетчик операций
int glub = 0;       // Текущая глубина рекурсии
int max_glub = 0;   // Максимальная глубина рекурсии

// Функция для печати массива
void PrintMas(int A[], int n) {
    for (int i = 1; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Первая версия быстрой сортировки (рекурсивная)
void qsort1(int A[], int L, int R) {
    glub++; // Увеличиваю глубину рекурсии
    if (max_glub < glub) {
        max_glub = glub; // Обновляю максимальную глубину
    }
    
    int x = A[L]; // Опорный элемент - первый в массиве
    int i = L, j = R;
    
    while (i <= j) {
        trud++; // Счетчик операций сравнения
        while (A[i] < x) {
            trud++; // Счетчик операций сравнения
            i++;
        }
        trud++; // Счетчик операций сравнения
        while (A[j] > x) {
            trud++; // Счетчик операций сравнения
            j--;
        }

        if (i <= j) {
            trud += 3; // Три операции для обмена элементов
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }

    // Рекурсивные вызовы для левой и правой частей
    if (L < j) {
        qsort1(A, L, j);
        glub--; // Уменьшаю глубину после возврата из рекурсии
    }
    if (i < R) {
        qsort1(A, i, R);
        glub--; // Уменьшаю глубину после возврата из рекурсии
    }
}

// Вторая версия быстрой сортировки (с оптимизацией рекурсии)
void qsort2(int A[], int L, int R) {
    glub++; // Увеличиваю глубину рекурсии
    if (max_glub < glub) {
        max_glub = glub; // Обновляю максимальную глубину
    }
    
    while (L < R) {
        int x = A[L]; // Опорный элемент
        int i = L, j = R;
        
        while (i <= j) {
            while (A[i] < x) i++;
            while (A[j] > x) j--;

            if (i <= j) {
                int temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                i++;
                j--;
            }
        }

        // Выбираю меньшую часть для рекурсивной обработки
        if ((j - L) > (R - i)) {
            qsort2(A, i, R);
            glub--; // Уменьшаю глубину после возврата из рекурсии
            R = j;  // Обрабатываю левую часть итеративно
        } else {
            qsort2(A, L, j);
            glub--; // Уменьшаю глубину после возврата из рекурсии
            L = i;  // Обрабатываю правую часть итеративно
        }
    }
}

// Заполнение массива убывающими значениями и сортировка
void FillDec(int A[], int n, int t1) {
    for (int i = 1; i < n; i++) {
        A[i] = n - i; // Заполняю массив в убывающем порядке
    }
    if (t1 == 0) {
        qsort1(A, 0, n - 1); // Сортирую первой версией
    } else {
        qsort2(A, 0, n - 1); // Сортирую второй версией
    }
}

// Заполнение массива случайными значениями и сортировка
void FillRand(int A[], int n, int t1) {
    for (int i = 1; i < n; i++) {
        A[i] = rand() % 1798; // Заполняю массив случайными числами
    }
    if (t1 == 0) {
        qsort1(A, 0, n - 1); // Сортирую первой версией
    } else {
        qsort2(A, 0, n - 1); // Сортирую второй версией
    }
}

// Заполнение массива возрастающими значениями и сортировка
void FillInc(int A[], int n, int t1) {
    for (int i = 1; i < n; i++) {
        A[i] = i; // Заполняю массив в возрастающем порядке
    }
    if (t1 == 0) {
        qsort1(A, 0, n - 1); // Сортирую первой версией
    } else {
        qsort2(A, 0, n - 1); // Сортирую второй версией
    }
}

// Функция для печати заголовка таблицы
void printHeader() {
    printf("----------------------------------------------------------------------------------------\n");
    printf(" %-20s | %-30s | %-30s | %-20s \n", "n", "Возрастающий", "Убывающий", "Случайный");
    printf("----------------------------------------------------------------------------------------\n");
}

// Функция для печати строки таблицы
void printRow(int n, int inc, int dec, int rand_val) {
    printf(" %-20d | %-20d | %-20d | %-20d \n", n, inc, dec, rand_val);
    printf("----------------------------------------------------------------------------------------\n");
}

// Основная функция для генерации таблиц с результатами
void tablee() {
    printf("\n\nТрудоемкость\n");
    printHeader();
    
    // Тестирую для разных размеров массивов (100, 200, ..., 500)
    for (int k = 1; k < 6; k++) {
        int n = k * 100;
        int* A = (int*)malloc(n * sizeof(int));
        
        // Тест с возрастающим массивом
        trud = 0;
        FillInc(A, n, 0);
        int inc = trud;
        
        // Тест с убывающим массивом
        trud = 0;
        FillDec(A, n, 0);
        int dec = trud;
        
        // Тест со случайным массивом
        trud = 0;
        FillRand(A, n, 0);
        int rand_val = trud;
        
        printRow(n, inc, dec, rand_val);
        free(A);
    }

//     // Тестирую глубину рекурсии для обеих версий сортировки
//     for (int t = 0; t < 2; t++) {
//         printf("\n\nГлубина рекурсии (%s)\n", t == 0 ? "версия 1" : "версия 2");
//         printHeader();
        
//         for (int k = 1; k < 6; k++) {
//             int n = k * 100;
//             int* A = (int*)malloc(n * sizeof(int));
            
//             // Тест с возрастающим массивом
//             glub = max_glub = 0;
//             FillInc(A, n, t);
//             int inc_depth = max_glub;
            
//             // Тест с убывающим массивом
//             glub = max_glub = 0;
//             FillDec(A, n, t);
//             int dec_depth = max_glub;
            
//             // Тест со случайным массивом
//             glub = max_glub = 0;
//             FillRand(A, n, t);
//             int rand_depth = max_glub;
            
//             printRow(n, inc_depth, dec_depth, rand_depth);
//             free(A);
//         }
//     }
}

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    tablee();
    return 0;
}