#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char surname[50];
    char name[50];
    char phone[15];
    int age;
} Abonent;

Abonent phonebook[] = {
    {"Бобокулов", "Самир", "192-168-255", 22},
    {"Волевачин", "Павел", "383-654-234", 38},
    {"Клишкинов", "Димка", "679-888-228", 22},
    {"Бобокулов", "Данил", "431-654-892", 18},
    {"Ерофъевов", "Артём", "187-169-150", 43}
};

#define SIZE (sizeof(phonebook) / sizeof(phonebook[0]))

//Индексные массивы
int indexByName[SIZE];
int indexByPhone[SIZE];

//Функция для сравнения по фамилии и имени
int lessByName(const void *a, const void *b) {
    int idx1 = *(int *)a;
    int idx2 = *(int *)b;
    
    int cmpSurname = strcmp(phonebook[idx1].surname, phonebook[idx2].surname);
    if (cmpSurname != 0) return cmpSurname;
    return strcmp(phonebook[idx1].name, phonebook[idx2].name);
}

//Функция для сравнения по номеру телефона
int lessByPhone(const void *a, const void *b) {
    int idx1 = *(int *)a;
    int idx2 = *(int *)b;
    return strcmp(phonebook[idx1].phone, phonebook[idx2].phone);
}

void insertionSort(int *index, int (*less)(const void *, const void *)) {
    for (int i = 1; i < SIZE; i++) {
        int key = index[i];
        int j = i - 1;
        
        while (j >= 0 && less(&index[j], &key) > 0) {
            index[j + 1] = index[j];
            j--;
        }
        index[j + 1] = key;
    }
}

void shakerSort(int *index, int (*less)(const void *, const void *)) {
    int left = 0;
    int right = SIZE - 1;
    int swapped = 1;
    
    while (left < right && swapped) {
        swapped = 0;
        
        //Проход слева направо
        for (int i = left; i < right; i++) {
            if (less(&index[i], &index[i + 1]) > 0) {
                int temp = index[i];
                index[i] = index[i + 1];
                index[i + 1] = temp;
                swapped = 1;
            }
        }
        right--;
        
        //Проход справа налево
        for (int i = right; i > left; i--) {
            if (less(&index[i - 1], &index[i]) > 0) {
                int temp = index[i];
                index[i] = index[i - 1];
                index[i - 1] = temp;
                swapped = 1;
            }
        }
        left++;
    }
}

//Инициализация индексных массивов
void initIndexArrays() {
    for (int i = 0; i < SIZE; i++) {
        indexByName[i] = i;
        indexByPhone[i] = i;
    }
}

void printPhonebookByIndex(int *index, const char *sortType) {
    printf("Телефонная книга, отсортированная %s:\n", sortType);
    printf("%-5s|%-15s|%-15s|%-15s|%s\n", "Индекс", "Фамилия", "Имя", "Телефон", "Возраст");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        int idx = index[i];
        printf("[%d]  %-15s|%-15s|%-15s|%d\n", 
               idx,  //Выводим индекс исходного массива
               phonebook[idx].surname, 
               phonebook[idx].name, 
               phonebook[idx].phone, 
               phonebook[idx].age);
    }
    printf("\n");
}

void printIndexArray(int *index, const char *description) {
    printf("%s: [", description);
    for (int i = 0; i < SIZE; i++) {
        printf("%d", index[i]);
        if (i < SIZE - 1) printf(", ");
    }
    printf("]\n\n");
}

int main() {
    initIndexArrays();
    
    printf("Исходный массив:\n");
    printPhonebookByIndex(indexByName, "в исходном порядке");
    printIndexArray(indexByName, "Исходный индексный массив (по имени)");
    printIndexArray(indexByPhone, "Исходный индексный массив (по телефону)");

    insertionSort(indexByName, lessByName);    
    shakerSort(indexByPhone, lessByPhone);    
    
    printPhonebookByIndex(indexByName, "по фамилии и имени (сортировка вставками)");
    printIndexArray(indexByName, "Отсортированный индексный массив (по имени)");
    
    printPhonebookByIndex(indexByPhone, "по номеру телефона (шейкерная сортировка)");
    printIndexArray(indexByPhone, "Отсортированный индексный массив (по телефону)");
    
    return 0;
}