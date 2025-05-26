#include "translate.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc !=4) { // Если передано 3 аргумента вывожу сообщение об использовании программы
        printf("Использование: %s Russian.txt dict.txt Germany.txt\n", argv[0]);
        return 1;
    }

    Translation *dict = NULL; // Инициализирую указатель на словарь как NULL
    int size = 0; // Инициализирую размер словаря
    if (LoadDict(argv[2], &dict, &size) != 0) { // Если загружает словарь из файла, указанного во втором аргументе 
        free(dict); //освобождаю память в случае ошибки
        return 1;
    }

    if (TranslateFile(argv[1], argv[3], dict, size) !=0) { // Если выполняет перевод текста изтпервого файла в третий
        free(dict);//Освобождая память в случае ошибки
        return 1;
    }
    
    free(dict); //Освобождаю память для словаря
    return 0;
}