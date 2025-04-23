#include <stdio.h>

double kramer(double matrix[4][4]){
       return matrix[0][0] * (matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2])
                          - matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1])
                          + matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]))
         - matrix[0][1] * (matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2])
                          - matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0])
                          + matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]))
         + matrix[0][2] * (matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1])
                          - matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0])
                          + matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]))
         - matrix[0][3] * (matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1])
                          - matrix[1][1] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0])
                          + matrix[1][2] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));
    
}

int main() {
    double matrix[4][4] = {
        {2, 5 , 4, 1},
        {1, 3, 2, 1},
        {2, 10, 9, 7},
        {3, 8, 9, 2}
    };
    
    double matrix_a[4][4] = {
        {20, 5 , 4, 1},
        {11, 3, 2, 1},
        {40, 10, 9, 7},
        {37, 8, 9, 2}
    };
    double matrix_b[4][4] = {
        {2, 20 , 4, 1},
        {1, 11, 2, 1},
        {2, 40, 9, 7},
        {3, 37, 9, 2}
    };
    double matrix_c[4][4] = {
        {2, 5 , 20, 1},
        {1, 3, 11, 1},
        {2, 10, 40, 7},
        {3, 8, 37, 2}
    };
    double matrix_d[4][4] = {
        {2, 5 , 4, 20},
        {1, 3, 2, 11},
        {2, 10, 9, 40},
        {3, 8, 9, 37}
    };

    double opred = kramer(matrix);
    double operd_a = kramer(matrix_a);
    double operd_b = kramer(matrix_b);
    double operd_c = kramer(matrix_c);
    double operd_d = kramer(matrix_d);
    
    double a = operd_a / opred;
    double b = operd_b / opred;
    double c = operd_c / opred;
    double d = operd_d / opred;

    printf("Определитель = %f\n", opred);
    printf("a = %f\n", a);
    printf("b = %f\n", b);
    printf("c = %f\n", c);
    printf("d = %f\n", d);
    
}