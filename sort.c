void BubbleSort (int A[], int n) {
    for (int i = 0; i < n -1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j+1]) {
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
} // добавил комментарий
 // добавил ещё один комментраий

int main (){
    int A[] = {4,0};
    BubbleSort(A,3);
    printf("Hello Git\n");
}