#ifndef TRAIN_H
#define TRAIN_H

typedef struct Train {
    char destination[256];
    int number_train;
    int deporttime[2]; 
} Train;

void clean_stdin();
void PrintTrain(Train train);
void create_file(const char *filename, int N);
void search_train(const char *filename);

#endif