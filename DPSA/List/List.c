#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   

int n = 10; // Глобальная переменная - размер структур данных

// Структура для узла стека (односвязный список)
struct StackNode {
    int data;               // Данные узла
    struct StackNode* next; // Указатель на следующий узел
};

// Структуры для очереди (на основе односвязного списка)
struct QueueNode {
    int data;               // Данные узла
    struct QueueNode* next; // Указатель на следующий узел
};

struct Queue {
    struct QueueNode* front; // Указатель на начало очереди
    struct QueueNode* rear;  // Указатель на конец очереди
};

// Структура для узла списка (односвязный список)
struct ListNode {
    int data;              // Данные узла
    struct ListNode* next; // Указатель на следующий узел
};

// Функции для работы со стеком

// Создание стека с возрастающими значениями от 1 до n
struct StackNode* createStackAscending(int n) {
    struct StackNode* top = NULL; // Инициализация вершины стека
    for (int i = 1; i <= n; i++) {
        struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode)); // Выделение памяти под новый узел
        newNode->data = i;       // Заполнение данных
        newNode->next = top;     // Новый узел указывает на предыдущую вершину
        top = newNode;            // Новый узел становится вершиной
    }
    return top; // Возврат указателя на вершину стека
}

// Создание стека с убывающими значениями от n до 1
struct StackNode* createStackDescending(int n) {
    struct StackNode* top = NULL;
    for (int i = n; i >= 1; i--) {
        struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
        newNode->data = i;
        newNode->next = top;
        top = newNode;
    }
    return top;
}

// Создание стека со случайными значениями в диапазоне [minVal, maxVal]
struct StackNode* createStackRandom(int n, int minVal, int maxVal) {
    struct StackNode* top = NULL;
    for (int i = 0; i < n; i++) {
        int num = rand() % (maxVal - minVal + 1) + minVal; // Генерация случайного числа
        struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
        newNode->data = num;
        newNode->next = top;
        top = newNode;
    }
    return top;
}

// Освобождение памяти стека
void freeStack(struct StackNode* top) {
    struct StackNode* current = top;
    while (current != NULL) {
        struct StackNode* next = current->next; // Сохранение указателя на следующий узел
        free(current);                         // Освобождение текущего узла
        current = next;                        // Переход к следующему узлу
    }
}

// Печать стека
void printStack(struct StackNode* top) {
    struct StackNode* current = top;
    while (current != NULL) {
        printf("%d ", current->data); // Печать данных узла
        current = current->next;       // Переход к следующему узлу
    }
    printf("\n");
}

// Вычисление контрольной суммы (суммы всех элементов)
int stackCheckSum(struct StackNode* top) {
    int sum = 0;
    struct StackNode* current = top;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

// Подсчет количества серий (групп одинаковых элементов)
int stackCountSeries(struct StackNode* top) {
    if (top == NULL) return 0;
    int count = 1;
    struct StackNode* current = top->next;
    while (current != NULL) {
        if (current->data < top->data) { // Сравниваем с предыдущим элементом
            count++;
        }
        top = current;
        current = current->next;
    }
    return count;
}

// Функции для работы с очередью

// Создание очереди с возрастающими значениями
struct Queue* createQueueAscending(int n) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); // Выделение памяти под очередь
    q->front = q->rear = NULL; // Инициализация указателей
    for (int i = 1; i <= n; i++) {
        struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        newNode->data = i;
        newNode->next = NULL;
        if (q->rear == NULL) { // Если очередь пуста
            q->front = q->rear = newNode;
        } else {
            q->rear->next = newNode; // Добавление в конец
            q->rear = newNode;
        }
    }
    return q;
}

// Создание очереди с убывающими значениями
struct Queue* createQueueDescending(int n) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    for (int i = n; i >= 1; i--) {
        struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        newNode->data = i;
        newNode->next = NULL;
        if (q->rear == NULL) {
            q->front = q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
    }
    return q;
}

// Создание очереди со случайными значениями
struct Queue* createQueueRandom(int n, int minVal, int maxVal) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    for (int i = 0; i < n; i++) {
        int num = rand() % (maxVal - minVal + 1) + minVal;
        struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        newNode->data = num;
        newNode->next = NULL;
        if (q->rear == NULL) {
            q->front = q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
    }
    return q;
}

// Освобождение памяти очереди
void freeQueue(struct Queue* q) {
    struct QueueNode* current = q->front;
    while (current != NULL) {
        struct QueueNode* next = current->next;
        free(current);
        current = next;
    }
    free(q); // Освобождение самой структуры очереди
}

// Печать очереди
void printQueue(struct Queue* q) {
    struct QueueNode* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Вычисление контрольной суммы очереди
int queueCheckSum(struct Queue* q) {
    int sum = 0;
    struct QueueNode* current = q->front;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

// Подсчет количества серий в очереди
int queueCountSeries(struct Queue* q) {
    if (q->front == NULL) return 0;
    int count = 1;
    struct QueueNode* current = q->front->next;
    while (current != NULL) {
        if (current->data < q->front->data) { // Сравниваем с предыдущим элементом
            count++;
        }
        q->front = current;
        current = current->next;
    }
    return count;
}

// Функции для работы со списком

// Печать списка
void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Вычисление контрольной суммы списка
int checkSum(struct ListNode* head) {
    int sum = 0;
    struct ListNode* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

// Подсчет количества серий в списке
int countSeries(struct ListNode* head) {
    if (head == NULL) return 0;
    int count = 1;
    struct ListNode* current = head->next;
    while (current != NULL) {
        if (current->data < head->data) { // Сравниваем с предыдущим элементом
            count++;
        }
        head = current;
        current = current->next;
    }
    return count;
}

// Удаление списка и освобождение памяти
void deleteList(struct ListNode** head) {
    struct ListNode* current = *head;
    while (current != NULL) {
        struct ListNode* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL; // Установка указателя на NULL после удаления
}

// Рекурсивная печать списка в прямом порядке
void printRecursiveForward(struct ListNode* node) {
    if (node == NULL) return; // Базовый случай рекурсии
    printf("%d ", node->data); // Печать текущего элемента
    printRecursiveForward(node->next); // Рекурсивный вызов для следующего
}

// Рекурсивная печать списка в обратном порядке
void printRecursiveBackward(struct ListNode* node) {
    if (node == NULL) return; // Базовый случай рекурсии
    printRecursiveBackward(node->next); // Сначала рекурсивный вызов
    printf("%d ", node->data); // Печать после возврата из рекурсии
}

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Демонстрация работы со стеком
    printf("1. Работа со стеком:\n");
    printf("1.1. Стек с числами 1-10 (возрастающие):\n");
    struct StackNode* stackAsc = createStackDescending(n);
    printStack(stackAsc);
    printf("Контрольная сумма: %d\n", stackCheckSum(stackAsc));
    printf("Количество серий: %d\n\n", stackCountSeries(stackAsc));

    printf("1.2. Стек с числами 10-1 (убывающие):\n");
    struct StackNode* stackDesc = createStackAscending(n);
    printStack(stackDesc);
    printf("Контрольная сумма: %d\n", stackCheckSum(stackDesc));
    printf("Количество серий: %d\n\n", stackCountSeries(stackDesc));

    printf("1.3. Стек со случайными числами (10 чисел 10-20):\n");
    struct StackNode* stackRand = createStackRandom(n, 10, 20);
    printStack(stackRand);
    printf("Контрольная сумма: %d\n", stackCheckSum(stackRand));
    printf("Количество серий: %d\n\n", stackCountSeries(stackRand));

    freeStack(stackAsc);
    freeStack(stackDesc);
    freeStack(stackRand);

    // Демонстрация работы с очередью
    printf("\n2. Работа с очередью:\n");
    printf("2.1. Очередь с числами 1-10 (возрастающие):\n");
    struct Queue* queueAsc = createQueueAscending(n);
    printQueue(queueAsc);
    printf("Контрольная сумма: %d\n", queueCheckSum(queueAsc));
    printf("Количество серий: %d\n\n", queueCountSeries(queueAsc));

    printf("2.2. Очередь с числами 10-1 (убывающие):\n");
    struct Queue* queueDesc = createQueueDescending(n);
    printQueue(queueDesc);
    printf("Контрольная сумма: %d\n", queueCheckSum(queueDesc));
    printf("Количество серий: %d\n\n", queueCountSeries(queueDesc));

    printf("2.3. Очередь со случайными числами (10 чисел 10-20):\n");
    struct Queue* queueRand = createQueueRandom(n, 10, 20);
    printQueue(queueRand);
    printf("Контрольная сумма: %d\n", queueCheckSum(queueRand));
    printf("Количество серий: %d\n\n", queueCountSeries(queueRand));

    freeQueue(queueAsc);
    freeQueue(queueDesc);
    freeQueue(queueRand);

    // Демонстрация работы со списком
    printf("\n3. Работа со списком:\n");
    // Создание списка вручную
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->data = 1;
    head->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->data = 2;
    head->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->data = 2;
    head->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->data = 3;
    head->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->data = 3;
    head->next->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->next->data = 3;
    head->next->next->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->next->next->data = 4;
    head->next->next->next->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->next->next->next->data = 5;
    head->next->next->next->next->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->next->next->next->next->data = 5;
    head->next->next->next->next->next->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->next->next->next->next->next->data = 6;
    head->next->next->next->next->next->next->next->next->next->next = NULL;

    printf("3.1. Список: ");
    printList(head);
    printf("Контрольная сумма: %d\n", checkSum(head));
    printf("Количество серий: %d\n\n", countSeries(head));

    printf("3.2. Печать в прямом порядке: ");
    printRecursiveForward(head);
    printf("\n3.3. Печать в обратном порядке: ");
    printRecursiveBackward(head);
    printf("\n");

    deleteList(&head);
    printf("\n3.4. Список после удаления: ");
    printList(head);

    return 0;
}