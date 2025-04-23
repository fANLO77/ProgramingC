#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SURNAME_LEN 50
#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15

typedef struct {
    char surname[MAX_SURNAME_LEN];
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    int age;
} Abonent;

typedef enum {
    SORT_BY_SURNAME_AND_NAME,
    SORT_BY_PHONE,
    SORT_BY_SURNAME_AND_PHONE
} SortKey;

typedef enum {
    SORT_ASCENDING,
    SORT_DESCENDING
} SortOrder;

SortKey currentSortKey = SORT_BY_SURNAME_AND_NAME;
SortOrder currentSortOrder = SORT_ASCENDING;

int lessAbonents(const Abonent *a, const Abonent *b) {
    int result = 0;
    
    switch (currentSortKey) {
        case SORT_BY_SURNAME_AND_NAME: {
            int cmpSurname = strcmp(a->surname, b->surname);
            if (cmpSurname != 0) {
                result = cmpSurname;
            } else {
                result = strcmp(a->name, b->name);
            }
            break;
        }
        case SORT_BY_PHONE: {
            result = strcmp(a->phone, b->phone);
            break;
        }
        case SORT_BY_SURNAME_AND_PHONE: {
            int cmpSurname = strcmp(a->surname, b->surname);
            if (cmpSurname != 0) {
                result = cmpSurname;
            } else {
                result = strcmp(a->phone, b->phone);
            }
            break;
        }
    }
    
    return (currentSortOrder == SORT_DESCENDING) ? -result : result;
}


int lessBySurname(const Abonent *a, const Abonent *b) {
    int cmp = strcmp(a->surname, b->surname);
    return (currentSortOrder == SORT_DESCENDING) ? -cmp : cmp;
}

void printPhonebook(const Abonent *phonebook, int size) {
    printf("\n%-20s %-20s %-20s %-10s\n", "Фамилия", "Имя", "Телефон", "Возраст");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-20s %-20s %-20s %-10d\n", 
               phonebook[i].surname, 
               phonebook[i].name, 
               phonebook[i].phone, 
               phonebook[i].age);
    }
    printf("\n");
}

void insertionSort(Abonent *phonebook, int size) {
    for (int i = 1; i < size; i++) {
        Abonent key = phonebook[i];
        int j = i - 1;

        while (j >= 0 && lessAbonents(&key, &phonebook[j]) < 0) {
            phonebook[j + 1] = phonebook[j];
            j--;
        }
        phonebook[j + 1] = key;
    }
}

int binarySearchBySurname(const Abonent *phonebook, int size, const char *surname) {
    int left = 0;
    int right = size - 1;
    int result = -1;
    
    Abonent key;
    strncpy(key.surname, surname, MAX_SURNAME_LEN);
    key.surname[MAX_SURNAME_LEN - 1] = '\0';

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = lessBySurname(&key, &phonebook[mid]);

        if (cmp == 0) {
            result = mid;
            right = mid - 1;
        } 
        else if (cmp < 0) {
            right = mid - 1;
        } 
        else {
            left = mid + 1;
        }
    }
    return result;
}

void printFoundAbonent(const Abonent *abonent) {
    if (abonent != NULL) {
        printf("Найден абонент: %s %s, тел.: %s, возраст: %d\n",
               abonent->surname, abonent->name, abonent->phone, abonent->age);
    } else {
        printf("Абонент не найден.\n");
    }
}

int main() {
    Abonent phonebook[] = {
        {"Бобокулов", "Самир", "192-168-255", 22},
        {"Волевачин", "Павел", "383-654-234", 38},
        {"Клишкинов", "Димка", "679-888-228", 22},
        {"Бобокулов", "Данил", "431-654-892", 18},
        {"Ерофъевов", "Артём", "187-169-150", 43}
    };

    int size = sizeof(phonebook) / sizeof(phonebook[0]);

    printf("Исходная телефонная книга:");
    printPhonebook(phonebook, size);

    printf("Выберите ключ сортировки:\n");
    printf("1. По фамилии и имени\n");
    printf("2. По номеру телефона\n");
    printf("3. По фамилии и номеру телефона\n");
    printf("Введите номер: ");
    
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            currentSortKey = SORT_BY_SURNAME_AND_NAME;
            break;
        case 2:
            currentSortKey = SORT_BY_PHONE;
            break;
        case 3:
            currentSortKey = SORT_BY_SURNAME_AND_PHONE;
            break;
        default:
            printf("Неверный выбор. Используется сортировка по фамилии и имени.\n");
            currentSortKey = SORT_BY_SURNAME_AND_NAME;
    }

    printf("Выберите направление сортировки:\n");
    printf("1. По возрастанию\n");
    printf("2. По убыванию\n");
    printf("Введите номер: ");
    
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            currentSortOrder = SORT_ASCENDING;
            break;
        case 2:
            currentSortOrder = SORT_DESCENDING;
            break;
        default:
            printf("Неверный выбор. Используется сортировка по возрастанию.\n");
            currentSortOrder = SORT_ASCENDING;
    }

    insertionSort(phonebook, size);

    printf("\nОтсортированная телефонная книга:");
    printPhonebook(phonebook, size);

    bool canSearchBySurname = (currentSortKey == SORT_BY_SURNAME_AND_NAME || 
                              currentSortKey == SORT_BY_SURNAME_AND_PHONE);
    
    if (canSearchBySurname) {
        char searchSurname[MAX_SURNAME_LEN];
        printf("Введите фамилию для поиска: ");
        scanf("%s", searchSurname);

        int foundIndex = binarySearchBySurname(phonebook, size, searchSurname);
        
        if (foundIndex != -1) {
            printf("\nНайденные абоненты с фамилией '%s':\n", searchSurname);
            for (int i = foundIndex; i < size && strcmp(phonebook[i].surname, searchSurname) == 0; i++) {
                printFoundAbonent(&phonebook[i]);
            }
        } else {
            printf("Абоненты с фамилией '%s' не найдены.\n", searchSurname);
        }
    } else {
        printf("\nБинарный поиск по фамилии недоступен при текущей сортировке.\n");
        printf("Для поиска по фамилии отсортируйте данные по фамилии.\n");
    }

}