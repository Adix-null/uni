#define ARRAY_SIZE 100

extern int read_counter;
extern int write_counter;

void saveToFile(char*, int [ARRAY_SIZE], int);

void loadFromFile(char*, int [ARRAY_SIZE], int*);

void fillArray(int [ARRAY_SIZE], int, int, int);

void printArray(int [ARRAY_SIZE], int);

void compArrays(int [ARRAY_SIZE], int [ARRAY_SIZE]);