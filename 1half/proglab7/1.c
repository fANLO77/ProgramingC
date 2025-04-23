#include <stdio.h>

int main() {
    char text[] = "Lorem ipsum   dolor sit amet,     consectetur adipiscing elit, sed do eiusmod tempor  incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int a = 0;
    int b = 0;
    int kolvoprobelov = 0;
    while (text[a]!='\0') { // символ конца строки
        if (text[a]!=' ') { // если символ не равен пробелу то он записывается в новую строку где нет пробелов
            text[b++]=text[a];
        } 
        else { // если есть пробелы то в переменную с пробелами добавляем 1
            kolvoprobelov++;
        }
        a++;// добавляет к а все символы включая пробелы
    }
    text[b]='\0'; // завершает новую строку где нету пробелов
    printf("Преобразованный текст: %s\n", text);
    printf("Число удаленных пробелов: %d\n", kolvoprobelov);
}
