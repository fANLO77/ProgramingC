// При сбокре не забываем слинковать с pthread
// gcc thread1.c -o thread1 -lpthread
//

#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>

#define NOF_THREADS 4
#define MAS 10

void DEAD(void *a){
    printf("DEAD %s\n", (char*) a);

}
void *Sleep(void *a) {
    pthread_t tid = pthread_self();
    pthread_cleanup_push(DEAD, a);
    usleep(*(int*)a*1000);
    printf("%d %ld\n", *(int*)a, tid);
    pthread_cleanup_pop(0);
    return NULL;
}

void SleapSort(int *sort){
    pthread_t tids[MAS];

    for (int i = 0; i < MAS; i++) {
        pthread_create(&tids[i], NULL, Sleep, &sort[i]);
    }


    for (int i = 0; i < MAS; i++) {
        pthread_join(tids[i], NULL);
  }
}


// void *routine(void *a) {
//     pthread_t tid = pthread_self();
//     pthread_cleanup_push(DEAD, a);
//     sleep(2);
//     printf("%s %ld\n", (char*)a, tid);
//     pthread_cleanup_pop(0);
//     return NULL;
// }

int main(void) {

    pthread_t tids[NOF_THREADS];

    int sort[MAS] = {5, 8, 22, 7, 12, 55, 1, 41, 72};

    char a[4][8] = {"one", "two", "three", "four"};

    // for (int i = 0; i < NOF_THREADS; i++) {
    //     pthread_create(&tids[i], NULL, routine, a[i]);
    // }

    //     sleep(1);

    // for (int i = 0; i < NOF_THREADS; i++) {
    //     pthread_cancel(tids[i]);
    // }
        
    SleapSort(sort);

   printf("hello from main thread %ld\n", pthread_self());

    // for (int i = 0; i < NOF_THREADS; i++) {
    //     pthread_join(tids[i], NULL);
    // }
    return 0;
}