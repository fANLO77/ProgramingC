#include "translate.h"
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_LoadDict(void **state) { // Тест для проверки загрузки файла
    Translation *dict = NULL; // Инциализирую указатель на словарь как Null
    int size = 0; // Инициализирую размер словаря
    assert_int_equal(LoadDict("../test_dict.txt", &dict, &size), 0); // выполняю тест загрузки словаря из файла test_dict.txt
    assert_int_not_equal(size, 0); // Проверяю что размер словаря не равен нулю
    free(dict); // Освобождаю память
}

static void test_TranslateFile(void **state) { // Тест для проверки перевода текста
    Translation *dict = NULL;// Создаю временный словарь
    int size = 0;
    assert_int_equal(LoadDict("../test_dict.txt", &dict, &size), 0); // Загружаю словарь из файла

    FILE *in = fopen("test_input.txt", "w"); // Создаю временный входной файл с тестовыми данными
    fprintf(in, "Облако Мармелад Программирование");
    fclose(in);

    assert_int_equal(TranslateFile("test_input.txt", "test_output.txt", dict, size), 0); // Вызываю функцию перевода

    FILE *out = fopen("test_output.txt", "r");// Читаю результат из выходного файла
    char result[100] = {0};
    fgets(result, sizeof(result), out);
    fclose(out);

     // Удаляет перенос строки и лишние пробелы
    result[strcspn(result, "\n")] = 0; // Убирает перенос строки
    while (strlen(result) > 0 && result[strlen(result) - 1] == ' ') {
        result[strlen(result) - 1] = 0; // Убирает лишние пробелы с конца
    }

    const char *expected = "Wolke Marmelade Programmierung"; // Ожидаемый результат
    assert_string_equal(result, expected); // Проверяю что результат совпадает с ожидаемым

    free(dict); // Освобождаю память
    remove("test_input.txt"); // Удаляю временные файлы
    remove("test_output.txt");

}

int main() {
    const struct CMUnitTest tests[] = { // Определяю массив тестов
        cmocka_unit_test(test_LoadDict),
        cmocka_unit_test(test_TranslateFile),
    };
    return cmocka_run_group_tests(tests, NULL, NULL); //Запускаю тесты
}