#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

// Глобальные переменные для подсчета операций
int comparisons = 0; // Счетчик сравнений
int moves = 0;       // Счетчик перемещений

// Структура узла списка
typedef struct Node {
    int data;         // Данные узла
    struct Node* next; // Указатель на следующий узел
} Node;

// Создание нового узла
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Выделяем память под новый узел
    newNode->data = data;                        // Записываем данные
    newNode->next = NULL;                        // Инициализируем указатель на NULL
    return newNode;                              // Возвращаем созданный узел
}

// Добавление элемента в конец списка
void append(Node** head, int data) {
    Node* newNode = createNode(data);            // Создаем новый узел
    if (*head == NULL) {                         // Если список пуст
        *head = newNode;                         // Новый узел становится головой
        return;
    }
    Node* last = *head;                          // Находим последний узел
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;                        // Добавляем новый узел в конец
}

// Расщепление списка на две части
void splitList(Node* source, Node** aRef, Node** bRef) {
    Node* slow = source;                         // Медленный указатель
    Node* fast = source->next;                   // Быстрый указатель
    while (fast != NULL && fast->next != NULL) { // Пока не достигнем конца
        slow = slow->next;                       // Медленный указатель движется на 1 шаг
        fast = fast->next->next;                 // Быстрый указатель движется на 2 шага
    }
    *aRef = source;                              // Первая часть списка
    *bRef = slow->next;                          // Вторая часть списка
    slow->next = NULL;                           // Разрываем связь между частями
}

// Слияние двух отсортированных списков
Node* mergeLists(Node* a, Node* b) {
    Node dummy;                                  // Фиктивный узел для начала нового списка
    Node* tail = &dummy;                         // Указатель на конец нового списка
    while (a != NULL && b != NULL) {             // Пока оба списка не пусты
        comparisons++;                           // Увеличиваем счетчик сравнений
        if (a->data <= b->data) {                // Сравниваем элементы
            tail->next = a;                      // Добавляем меньший элемент
            a = a->next;                         // Переходим к следующему элементу
        } else {
            tail->next = b;                      // Аналогично для второго списка
            b = b->next;
        }
        moves++;                                 // Увеличиваем счетчик перемещений
        tail = tail->next;                       // Перемещаем указатель на конец
    }
    // Добавляем оставшиеся элементы из одного из списков
    if (a != NULL) {
        while (a != NULL) {
            tail->next = a;
            a = a->next;
            moves++;                             // Увеличиваем счетчик перемещений
            tail = tail->next;
        }
    } else {
        while (b != NULL) {
            tail->next = b;
            b = b->next;
            moves++;                             // Увеличиваем счетчик перемещений
            tail = tail->next;
        }
    }
    return dummy.next;                           // Возвращаем начало нового списка
}

// Merge Sort для списков
Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {    // Базовый случай: список пуст или содержит 1 элемент
        return head;
    }
    Node* a;                                     // Первая часть списка
    Node* b;                                     // Вторая часть списка
    splitList(head, &a, &b);                     // Разделяем список на две части
    a = mergeSort(a);                            // Рекурсивно сортируем первую часть
    b = mergeSort(b);                            // Рекурсивно сортируем вторую часть
    return mergeLists(a, b);                     // Сливаем отсортированные части
}

// Генерация списка
void generateList(Node** head, int size, int type) {
    *head = NULL;                                // Инициализируем пустой список
    switch (type) {
        case 1:                                   // Убывающий список
            for (int i = size; i >= 1; i--) {
                append(head, i);                 // Добавляем элементы в обратном порядке
            }
            break;
        case 2:                                   // Случайный список
            srand(time(NULL));                   // Инициализируем генератор случайных чисел
            for (int i = 0; i < size; i++) {
                append(head, rand() % 1000 + 1); // Добавляем случайные числа
            }
            break;
        case 3:                                   // Возрастающий список
            for (int i = 1; i <= size; i++) {
                append(head, i);                 // Добавляем элементы в прямом порядке
            }
            break;
    }
}

// Теоретическое значение M+C
double theoretical_M_C(int n) {
    return 3.0 * n * log2(n);                    // Формула для теоретической трудоемкости
}

// Главная функция
int main() {
    int sizes[] = {100, 200, 300, 400, 500};     // Размеры массивов
    int types[] = {1, 2, 3};                     // Типы данных: убыв., случ., возр.
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]); // Количество размеров
    int num_types = sizeof(types) / sizeof(types[0]); // Количество типов

    printf("Трудоемкость сортировки прямого слияния\n");
    printf("|  N  | M+C теоретич.    | M_факт+C_факт    | M_факт+C_факт    | M_факт+C_факт    |\n");
    printf("|     |                  | Убыв.            | Случ.            | Возр.            |\n");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_sizes; i++) {        // Для каждого размера массива
        int n = sizes[i];
        double theoretical = theoretical_M_C(n);  // Вычисляем теоретическую трудоемкость

        printf("| %3d | %16.2f |", n, theoretical); // Выводим теоретическое значение

        for (int j = 0; j < num_types; j++) {    // Для каждого типа данных
            Node* list = NULL;
            generateList(&list, n, types[j]);    // Генерируем список

            comparisons = 0;                     // Сбрасываем счетчики
            moves = 0;

            mergeSort(list);                     // Выполняем сортировку

            double actual = comparisons + moves; // Вычисляем фактическую трудоемкость
            printf(" %16.2f |", actual);         // Выводим фактическое значение
        }

        printf("\n");
    }

    printf("-----------------------------------------------------------------------------------\n");

    return 0;
}