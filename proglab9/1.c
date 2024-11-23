#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocMatrix(int stroki, int stolbtsi) { // выделяем память под матрицу; 
    int **matrix = (int **)malloc(stroki * sizeof(int *));
    for (int i = 0; i<stroki;i++) {
        matrix[i] = (int *)malloc(stolbtsi * sizeof(int));
    }

    return matrix;
}

void freeMatrix(int **matrix, int stroki) { // освобождаем память под матрицы
    for (int i = 0; i<stroki;i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void VvodMatrix(int **matrix, int stroki, int stolbtsi) { // вводим матрицу
    for(int i = 0; i<stroki; i++) {
        for( int j =  0; j<stolbtsi; j++){
            int oshibka = 0;
            while(!oshibka){
                printf("Элемент [%d][%d]: ", i, j);
                if (scanf("%d", &matrix[i][j]) !=1 ){
                    printf("Надо ввсети число, переделывай\n");
                    while (getchar() != '\n'); // очищаем буфер ввода
                } else {
                    oshibka = 1; //ввод коректен
                }
            }
        }
    }
} 

void RandomMatrix(int **matrix, int stroki, int stolbtsi) { // заполняем матрицу рандомными числами от -10 до 10
    for( int i = 0; i<stroki;i++) {
        for( int j = 0; j<stolbtsi;j++) {
            matrix[i][j] = rand() % 21 - 10;
        }
    }
}

int **Matrix_C(int **A, int **B, int m, int n, int k) { // умножаем 2 матрицы и результат записываем в матрицу С
    int **C = allocMatrix(m ,k);
    for(int i = 0; i<m; i++) {
        for( int j = 0; j<k; j++) {
            C[i][j] = 0;
            for(int l = 0; l<n; l++) { 
            C[i][j] += A[i][l] * B[l][j];
            }
        }
    }
    return C; // возвращаем указатель на матрицу С
}

int FindMaxNegativeStrok(int **matrix, int stroki, int stolbtsi){ // поиск строки с наибольшим количеством отрицательных чисел
    int maxNegative = 0;
    int indexStroki = -1;
    for(int i = 0; i<stroki;i++) {
        int countNegative = 0;
        for(int j = 0; j<stolbtsi;j++) {
            if( matrix[i][j] < 0) {
                countNegative++;
            }
        }
        if (countNegative > maxNegative) {
        maxNegative = countNegative;
        indexStroki = i;
        }    
    }
    return indexStroki;
}

void ZamenaNegative(int **matrix, int stroki, int stolbtsi, int indexStroki) { // заменяем отрицательные числа их количеством
    int countNegative = 0;
    for (int j = 0; j < stolbtsi; j++) {
        if (matrix[indexStroki][j] < 0) {
            countNegative++; // считаем количество отрицательных чисел в выбранной строке
        }
    }
    for (int j = 0; j < stolbtsi; j++) { // заменяем отрицательные числа на их количество
        if (matrix[indexStroki][j] < 0) {
            matrix[indexStroki][j] = countNegative;
        }
    }
}


void ReversStroki(int *stroki, int stolbtsi) { // переворачиваем строку в обратном порядке
    for(int i = 0, j = stolbtsi - 1; i<j; i++, j-- ) {
        int temp = stroki[i];
        stroki[i] = stroki[j];
        stroki[j] = temp;
    }
}

void printMatrix(int **matrix, int stroki, int stolbtsi) { // выводим полученную матрицу
    for(int i = 0; i<stroki;i++) {
        for(int j = 0; j < stolbtsi; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n, k;
// wrong input scanf
    printf("Введи размер матрицы А (m x n): "); // вводим размеры матриц
    while(scanf("%d %d", &m, &n) !=2 || m <= 0 || n <= 0){
        printf("Ошибка, надо ввести 2 положительных числа, переделывай\n");
        while (getchar() != '\n');
    }
    printf("Введи размер матрицы B (n x k): ");
    while(scanf("%d", &k) !=1 || k<=0){
        printf("Ошибка, надо ввести положительное число, переделывай\n");
        while (getchar() != '\n');
    }

    int **A = allocMatrix(m, n); // выделяем память под матрицы
    int **B = allocMatrix(n, k);

    int sposobi; // выбираем способ заполнения матрицы
    printf("Выбери способ заполнения матриц:\n1 Ввод с клавиатуры\n2 Рандомные числа\nТвой выбор: ");
    while(scanf("%d", &sposobi) !=1 || (sposobi!=1 && sposobi !=2)){
        printf("Ошибка надо ввести 1 или 2, переделывай\n");
        while (getchar() != '\n');
    }
    
    if (sposobi == 1) {
        printf("Введите матрицу A:\n");
        VvodMatrix(A, m, n); 
        printf("Введите матрицу B:\n");
        VvodMatrix(B, n, k); 
    } else if (sposobi == 2) {
        srand(time(NULL)); // если ввод рандомных чисел
        RandomMatrix(A, m, n);
        RandomMatrix( B, n, k);
    } else {
        printf("Не балуйся, выберать надо было 1 или 2, а теперь я заполню матрицы случайными числами\n");
        srand(time(NULL));
        RandomMatrix(A, m, n);
        RandomMatrix( B, n, k);
    }

    printf("Матрица A:\n"); // выводим исходные матрицы
    printMatrix(A, m, n);
    printf("Матрица B:\n");
    printMatrix(B, n, k);

    int **C = Matrix_C(A, B, m, n, k); // выводим результирующую матрицу С = А * В
    printf("Результирующая матрица С:\n");
    printMatrix(C, m, k);

    int indexstroki = FindMaxNegativeStrok(C, m, k); // анализируем матрицу С: выводим строку с максимальным количеством отрицательных чисел 
    if (indexstroki != -1) {
        printf("Строка с наибольшим количеством отрицательных чисел: %d\n", indexstroki);
    } else {
        printf("В матрице нет отрицательных чисел\n");
    }

    ZamenaNegative(C, m, k, indexstroki); // выводим матрицу с заменой отрицательных элементов
    printf("Матрица С помле замены отрицательных чисел:\n");
    printMatrix(C, m, k);    

    if (indexstroki != -1) { // переворот строки
        ReversStroki(C[indexstroki], k);
        printf("Строка %d после переворота:\n", indexstroki);
        for(int i = 0; i <k; i++) {
            printf("%d ", C[indexstroki][i]);
        }
        printf("\n");
    }

    freeMatrix(A, m); // освобождаем память
    freeMatrix(B, n);
    freeMatrix(C, m);
}