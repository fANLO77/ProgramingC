#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Train.h"

int main() {
    const char *filename = "Train.dat";
    int N, choice;

    //запрашиваю количество записей для создания
    printf("Сколько записей вы хотите добавить? ");
    scanf("%d", &N);
    clean_stdin();

    //создаю файл с записями
    create_file(filename, N);

    //основной цикл меню
    do {
        printf("\nМеню:\n");
        printf("1 - Поиск по файлу\n");
        printf("2 - Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        clean_stdin();

        switch (choice) {
            case 1:
                search_train(filename);
                break;
            case 2:
                printf("Выход\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 2);

    return 0;
}