#include <stdio.h>
#include <stdlib.h>

#ifndef TRANSLATE_H
#define TRANSLATE_H

// Создаю структуру данных для хранения русского и немецкого языков
typedef struct {
    char Russian[50];
    char Germany[50];
} Translation;

// Объявляю функцию для загрузки словаря
int LoadDict (const char *filename, Translation **dict, int *size );

// Объявляю функцию перевода текста
int TranslateFile (const char *input, const char *output, Translation *dict, int size);

#endif // TRANSLATE_H