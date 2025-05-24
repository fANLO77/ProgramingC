#include <pthread.h> 
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 
#include <unistd.h> 

#define MAX_MSG_LEN 128 // Максимальная длина сообщения
#define QUEUE_SIZE 10   // Размер очереди

// Структура очереди
typedef struct {
    char *messages[QUEUE_SIZE]; // Массив сообщений
    int head;                   // Индекс начала
    int tail;                   // Индекс конца
    int count;                  // Количество сообщений
    pthread_mutex_t mutex;      // Мьютекс
    pthread_cond_t not_full;    // Условная переменная для незаполненной очереди
    pthread_cond_t not_empty;   // Условная переменная для непустой очереди
} Queue;

// Инициализация очереди
void queue_init(Queue *q) {
    q->head = 0;  // Начальный индекс
    q->tail = 0;  // Конечный индекс
    q->count = 0; // Счетчик
    // Инициализация мьютекса
    pthread_mutex_init(&q->mutex, NULL);
    // Инициализация условных переменных
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

// Уничтожение очереди
void queue_destroy(Queue *q) {
    // Освобождение сообщений
    while (q->count > 0) {
        free(q->messages[q->head]);
        q->head = (q->head + 1) % QUEUE_SIZE;
        q->count--;
    }
    // Уничтожение мьютекса
    pthread_mutex_destroy(&q->mutex);
    // Уничтожение условных переменных
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->not_empty);
}

// Отправка сообщения
int msgSend(Queue *q, char *msg) {
    // Копирование сообщения
    char *msg_copy = strndup(msg, MAX_MSG_LEN);
    int len = strlen(msg_copy);

    // Блокировка мьютекса
    pthread_mutex_lock(&q->mutex);
    // Ожидание незаполненной очереди
    while (q->count >= QUEUE_SIZE) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }

    // Добавление сообщения
    q->messages[q->tail] = msg_copy;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;

    // Сигнал о непустой очереди
    pthread_cond_signal(&q->not_empty);
    // Разблокировка мьютекса
    pthread_mutex_unlock(&q->mutex);

    // Возврат длины
    return len;
}

// Получение сообщения
int msgRecv(Queue *q, char *buf, size_t bufsize) {
    // Блокировка мьютекса
    pthread_mutex_lock(&q->mutex);
    // Ожидание непустой очереди
    while (q->count == 0) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    // Извлечение сообщения
    char *msg = q->messages[q->head];
    // Копирование с обрезкой
    strncpy(buf, msg, bufsize - 1);
    buf[bufsize - 1] = '\0';
    int len = strlen(buf);

    // Освобождение сообщения
    free(msg);
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;

    // Сигнал о незаполненной очереди
    pthread_cond_signal(&q->not_full);
    // Разблокировка мьютекса
    pthread_mutex_unlock(&q->mutex);

    // Возврат длины
    return len;
}

// Функция клиента
void *client_func(void *arg) {
    Queue *q = (Queue *)arg;
    char msg[50];
    // Бесконечный цикл
    while (1) {
        // Формирование сообщения
        snprintf(msg, sizeof(msg), "Сообщение от клиента %ld", pthread_self());
        // Отправка
        msgSend(q, msg);
        // Случайная задержка
        usleep(rand() % 900000 + 100000);
    }
    return NULL;
}

// Функция сервера
void *server_func(void *arg) {
    Queue *q = (Queue *)arg;
    char buf[MAX_MSG_LEN];
    // Бесконечный цикл
    while (1) {
        // Получение сообщения
        int len = msgRecv(q, buf, MAX_MSG_LEN);
        // Вывод
        printf("Задание 10: [Сервер] %s\n", buf);
        // Случайная задержка
        usleep(rand() % 900000 + 100000);
    }
    return NULL;
}

void task10() {
    printf("Задание 10: Производитель-потребитель\n");
    Queue q; // Очередь
    queue_init(&q); // Инициализация

    // Создание 3 клиентов
    pthread_t clients[3];
    for (int i = 0; i < 3; i++) {
        // Создание клиента
        if (pthread_create(&clients[i], NULL, client_func, &q) != 0) {
            // Вывод ошибки
            fprintf(stderr, "Ошибка создания клиента %d\n", i);
            return;
        }
    }

    // Создание 2 серверов
    pthread_t servers[2];
    for (int i = 0; i < 2; i++) {
        // Создание сервера
        if (pthread_create(&servers[i], NULL, server_func, &q) != 0) {
            // Вывод ошибки
            fprintf(stderr, "Ошибка создания сервера %d\n", i);
            return;
        }
    }

    // Ожидание клиентов (в демонстрации ограничим время)
    sleep(5);

    // Прерывание клиентов и серверов
    for (int i = 0; i < 3; i++) {
        pthread_cancel(clients[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_cancel(servers[i]);
    }

    // Ожидание завершения
    for (int i = 0; i < 3; i++) {
        pthread_join(clients[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(servers[i], NULL);
    }

    // Уничтожение очереди
    queue_destroy(&q);
    printf("\n");
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    // Вызов задания
    task10();
    // Успешное завершение
    return 0;
}