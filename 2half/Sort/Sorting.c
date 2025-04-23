#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int N = 100000; // объявляем константу кол-ва студентов

struct Student { // создаём структуру в которой хранится информация о студентах
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent (char name[], int math, int phy, int inf) { // создаём функцию заполнения информации о студентах
    struct Student newStudent;
    strcpy(newStudent.name, name);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
};

void printStudentInfo(struct Student student) { // создаём функцию вывода информации о студентах
    printf("\nИмя студента: %s\n", student.name);
    printf("Математика: %d\n", student.math);
    printf("Физика: %d\n", student.phy);
    printf("Информатика: %d\n", student.inf);
    printf("Общие баллы: %d\n", student.total);
    printf("\n");
}

void SelectionSort(struct Student students[], int N ) { // создаём функцию  сортировки выбором
    for (int i = 0; i < N; i++) { // пробегаемся по массиву 
        int maxstudent = i; // берём элемент и объявляем его максимальным
        for (int j = i+1; j<N; j++) { // пробегаемся по остальным элементам
            if (students[j].total > students[maxstudent].total) { // если какой-то из оставшихся элементов больше первого то записываем его максимальным
                maxstudent = j;
            }
        }
        if (maxstudent != i) { // не делаем перестановок однотипных элементов, например 21 и 21 не меняем местами
            struct Student temp = students[i]; // осуществляем перестановки
            students[i] = students[maxstudent];
            students[maxstudent] = temp;
        }
    }
}

void RadixSort(struct Student students[], int N) {
    int max = students[0].total;
    // Находим максимальный балл и узнаём сколько у него разрядов
    for(int i = 0; i<N; i++) {
        if (students[i].total > max) {
            max = students[i].total;
        }
    }

    struct Student* output = (struct Student*)malloc(N * sizeof(struct Student)); // Создаём временный массив для отсортированных данных, exp - текущий разряд
    // Сортируем по каждому разряду
    for(int exp = 1; max/exp > 0; exp*=10) { 
        int count[10] = {0}; // Создаём массив для подсчёта частоты цифр (0-9)

        // Подсчитываем, сколько раз встречается каждая цифра в текущем разряде
        for(int i = 0; i < N; i++) {
            count[(students[i].total / exp) % 10]++; // Извлекаем текущюю цифру и увеличиваем счётчик этой цифры
        }
        // Преобразуем массив для подсчёта частоты цифр, чтобы он хранил индекс последнего элемента с данной цифрой
        for(int i = 1; i <10; i++) {
            count[i] += count[i-1];
        }
        // Строим временный массив для отсортированных данных, размещая элементы в правильном порядке
        for(int i = N - 1; i >=0; i--) {
            output[count[(students[i].total / exp)% 10] - 1] = students[i]; // Вычисляем текущую цифру и её позицию в output, размещаем элемент в массив
            count[(students[i].total / exp)% 10]--; // Уменьшаем счётчик для этой цифры
        }
    // Копируем временный массив для отсортированных данных обратно в массив студентов
    for (int i = 0; i<N; i++) {
        students[i] = output[i];
    }
    }
    free(output);
}

void QuickSort(struct Student students[], int low, int high) {
    if (low < high) { // Условие выхода из рекурсии: если в подмасиве меньше двух элементов
        int pivot = students[high].total; // Опираемся на последний элемент
        int i = low - 1; // Индекс для эелементов больших чем pivot

        // Перемещаем элементы больше pivot влево
        for(int j = low; j < high; j++) { // Проходимся по эелементам 
            if (students[j].total > pivot) { // Сортируем по убыванию
            i++; // Сдвигаем границу элементов больших чем pivot
            struct Student temp = students[i]; // Выполняем перестановки
            students[i] = students[j];
            students[j] = temp;
        }
    }
    

        // Перемещаем pivot на его правильное место (i+1)
        struct Student temp = students[i+1];
        students[i+1] = students[high];
        students[high] = temp;

        // Рекурсивно сортируем левуб и правую части
        QuickSort(students, low, i); // Элементы больше pivot
        QuickSort(students, i+2, high); // Элемнты меньше pivot
    }
}

int main() {
    srand(time(NULL));
    struct Student students [N];

    for(int i = 0; i < N; i++) {
        char name[64];
        sprintf(name, "Student %d", i+1);
        students[i] = addStudent(name, rand() %101, rand() %101, rand()%101);
    }

    // printf("До сортировки: \n");
    // for (int i = 0; i<N; i++) {
    //     printStudentInfo(students[i]);
    // }

    clock_t start = clock();
    QuickSort(students, 0, N-1);

    // printf("\nПосле сортировки: \n");
    // for (int i = 0; i < N; i++) {
    //     printStudentInfo(students[i]);
    // }

    clock_t end = clock();
    double worktime = end - start;
    printf("Время работы сортировки: %lf секунд\n", worktime / CLOCKS_PER_SEC);

    printf("\nИнформация о процессоре\n");
    system("cat /proc/cpuinfo | grep 'model name' | head -1");
    system("cat /proc/cpuinfo | grep 'cpu MHz' | head -1 ");
}
// SelectSort:
// для 100 студентов 0.000007 секунд
// для 10000 студентов 0.0565897 секунд
// для 100000 студентов 5.737416 секунд

// QuickSort
// для 100 студентов 0.001736 секунд
// для 10000 студентов 0.164824 секунд
// для 100000 студентов 1.743486 секунд

// RadixSort
// для 100 студентов 0.002000 секунд
// для 10000 студентов 0.161936 секунд
// для 100000 студентов 2.806642 секунд