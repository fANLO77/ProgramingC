#include "translate.h"
#include <string.h>

// Объявляю функцию для загрузки словаря
int LoadDict (const char *filename, Translation **dict, int *size) {
    FILE *fp = fopen(filename, "r"); // Открываю файл словаря с ключём для чтения
    if (!fp) {
        printf("Ошибка, не удалось открыть файл словаря %s\n", filename); // Если не удалось открыть файл вывожу ошибку
        return -1;
    }

    *size = 0; // размер словаря
    *dict = realloc(*dict, sizeof(Translation)); // Выделяю память под один элемент структуры
    if (!*dict) {
        fclose(fp); // Если не удалось выделять память закрываю файл
        return -1;
    }

    while (fscanf(fp, "%s %s", (*dict)[*size].Russian, (*dict)[*size].Germany) == 2) { // Читаю пары слов из фала
        (*size)++; // Увеличиваю счётчик
        *dict = realloc(*dict, (*size + 1)*sizeof(Translation)); //Перевыделяю память для нового элемента
        if (!*dict) {
            fclose(fp); // Если не удалось перевыделит память закрываю файл
            return -1;
        }
    }

    fclose(fp); //Закрываю фалй после чтения
    return 0;
}

// Объявляю функцию перевода текста
int TranslateFile (const char *input, const char *output, Translation *dict, int size) {
    FILE *in = fopen(input, "r"); // Открываю входной файл для чтения
    FILE *out = fopen(output, "w"); // Открываю выходной файл для записи
    if (!in || !out) { // Если не удалось открыть файлы вывожу ошибку и закрываю файлы
        printf("Ошибка, не удалось открыть один из файлов\n");
        if (!in) fclose(in);
        if (!out) fclose(out);
        return -1;
    }
    char word[50]; // Объявляю переменную для текущего слова
    while (fscanf(in, "%s ", word) == 1) { // Читаю слова из входного файла по одному
        int found = 0; // Объявляю переменную сизнализирующую найдено слово или нет
        for (int i = 0; i < size; i++) { // Прохожу по всем элементам словаря
            if (strcmp(word, dict[i].Russian) == 0) { // Если текущее слово == русское слово из словаря записываю перевод в выходной файл
                fprintf(out, "%s ", dict[i].Germany); 
                found = 1; // Слово найдено
                break;
            }
        }

        if (!found) { // Если слово не найдено записываю само слово
            fprintf(out, "%s ", word);
        }
    }

    fclose(in); //Закрываю входной файл
    fclose(out); //Закрываю выходной файл
    return 0;
}