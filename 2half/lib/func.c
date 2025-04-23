#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Train.h"

//создаю функцию очистки буфера ввода, она нужна для корректной работы scanf при последовательном вводе 
void clean_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//создаю функцию вывода информации о поезде
void PrintTrain(Train train) {
    printf("\nНайдена запись:\n");
    printf("Номер поезда: %d\n", train.number_train);
    printf("Пункт назначения: %s\n", train.destination);
    printf("Время отправления: %02d:%02d\n", train.deporttime[0], train.deporttime[1]);
}

//создаю функцию для создания файла с записями о поездах
void create_file(const char *filename, int N) {
    //открываю файл в бинарном режиме для записи
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    Train train;
    for(int i = 0; i < N; i++) {
        printf("\nЗапись %d:\n", i+1);
        
        //запрашиваю и сохраняю пункт назначения
        printf("Пункт назначения: ");
        scanf("%255s", train.destination);
        clean_stdin();
        
        //запрашиваю и сохраняю номер поезда
        printf("Номер поезда: ");
        scanf("%d", &train.number_train);
        
        //запрашиваю и сохраняю время отправления
        printf("Время отправления (часы:минуты): ");
        scanf("%d:%d", &train.deporttime[0], &train.deporttime[1]);
        clean_stdin();

        //записываю структуру в файл
        fwrite(&train, sizeof(Train), 1, file);
    }
    fclose(file);
}

//создаю функцию поиска поездов в файле 
void search_train(const char *filename) {
    //открываю файл для чтения
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    //предлагаю пользователю выбрать поле для поиска
    int field_choice;
    printf("\nПо какому полю выполнить поиск?\n");
    printf("1 - Пункт назначения\n");
    printf("2 - Номер поезда\n");
    printf("3 - Время отправления\n");
    printf("Выбор: ");
    scanf("%d", &field_choice);
    clean_stdin();

    Train train;
    int found = 0; //флаг для отслеживания найденных записей

    //в зависимости от выбора реализую поиск
    switch (field_choice) {
        case 1: { //поиск по пункту назначения
            char search_dest[256];
            printf("Введите пункт назначения: ");
            scanf("%255s", search_dest);
            clean_stdin();

            //читаю файл и ищу совпадения
            while(fread(&train, sizeof(Train), 1, file)) {
                if (strstr(train.destination, search_dest)) {
                    PrintTrain(train);
                    found = 1;
                }
            }
            break;
        }
        case 2: { //поиск по номеру поезда
            int search_num;
            printf("Введите номер поезда: ");
            scanf("%d", &search_num);
            clean_stdin();

            while(fread(&train, sizeof(Train), 1, file)) {
                if (train.number_train == search_num) {
                    PrintTrain(train);
                    found = 1;
                }
            }
            break;
        }
        case 3: { //поиск по времени отправления
            int hours, minutes;
            printf("Введите время отправления (часы:минуты): ");
            scanf("%d:%d", &hours, &minutes);
            clean_stdin();

            while(fread(&train, sizeof(Train), 1, file)) {
                if (train.deporttime[0] == hours && 
                    train.deporttime[1] == minutes) {
                    PrintTrain(train);
                    found = 1;
                }
            }
            break;
        }
        default:
            printf("Неверный выбор поля\n");
    }

    if (!found) {
        printf("\nЗаписи не найдены\n");
    }
    fclose(file);
}
