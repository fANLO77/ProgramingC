#include <stdio.h>

int main() {
    int A[6] = {1, 2, 3, 4, 5, 6};
    int B[6] = {-7, 8, 9, -10, 11, 12};
    int C[6];
    for (int i = 0;i<6;i++) {
        C[i] = A[i] + B[i];
    }

    int max_re_A = A[0];
    int kol_otr_im_B = 0;
    for (int i = 0;i<6;i++) {
        if (max_re_A < A[i])
            max_re_A = A[i];
    
        if (B[i] < 0){
            kol_otr_im_B++;
        }
    }

    int sum_re_C = 0;
    int sum_im_C = 0;
    for (int i = 0;i<6;i++){
        sum_re_C += C[i];
        sum_im_C += C[i];
    }

    float sr_re_C = sum_re_C / 6;
    float sr_im_C = sum_im_C / 6;
    float sr_C = sr_im_C || sr_re_C;
    printf("%d\n", max_re_A);
    printf("%d\n", kol_otr_im_B);
    printf("%f\n", sr_re_C);
    printf("%f\n", sr_im_C);
    printf("%f\n", sr_C);
} // 1+2*i