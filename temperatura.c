#include <stdio.h>

int main() {
    float temperature;
    char op;

    printf("Введите температуру: ");
    scanf("%f %c", &temperature, &op);

    if ( op == 'C' || op == 'c') {
        printf("%.2f градусов Цельсия = %.2f градусов Фаренгейта\n", temperature, (temperature * 9.0 / 5.0) + 32.0);
    } else if ( op == 'F' || op == 'f') {
        printf("%.2f градусов Фаренгейта = %.2f градусов Цельсия\n", temperature, (temperature - 32.0) * 5.0 / 9.0);
    } else {
        printf("Ошибка\n");
    }

    return 0;
}

