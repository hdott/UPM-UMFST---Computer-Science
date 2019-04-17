#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


double InsertionSort(int *vector, int size)
{
    clock_t t = clock();


    for(int i=1, j; i<size; ++i)
    {
        int temp = vector[i];

        for(j=i-1; j>=0 && vector[j] > temp; --j)
            vector[j+1] =   vector[j];

        vector[j+1] = temp;
    }    

    t = clock()-t;

    return (double)t/CLOCKS_PER_SEC;
}

double ShellSort(int *vector, int size)
{
    clock_t t = clock();

    for(int gap=size/2; gap>0; gap /= 2)
    {
        for(int i=gap, j; i<size; ++i)
        {
            int temp = vector[i];
            
            for(j=i; j>=gap && vector[j-gap] > temp; j-=gap)
                vector[j] = vector[i-gap];

            vector[j] = temp;
        }
    }

    t = clock()-t;

    return (double)t/CLOCKS_PER_SEC;
}

double SelectionSort(int *vector, int size)
{
    clock_t t = clock();

    for(int i=0; i<size-1; ++i)
    {
        int minI = i;

        for(int j=i+1; j<size; ++j)
            if(vector[j] < vector[minI])
                minI = j;

        int aux = vector[minI];
        vector[minI] = vector[i];
        vector[i] = aux;
    }

    t = clock()-t;

    return (double)t/CLOCKS_PER_SEC;
}

int findMaxArr(int *vector, int size)
{
    int max = vector[0];

    for(int i=1; i<size; ++i)
        if(max < vector[i])
            max = vector[i];

    return  max;
}

int findMinArr(int *vector, int size)
{
    int min = vector[0];

    for(int i=1; i<size; ++i)
        if(min > vector[i])
            min = vector[i];

    return min;
}

double CountingSort(int *vector, int size)
{
    clock_t t = clock();

    int max = findMaxArr(vector, size);
    int min = findMinArr(vector, size);
    int range = max-min+1;

    int *count = (int*) calloc(range, sizeof(int));
    int *output = (int*) malloc(size * sizeof(int));

    for(int i=0; i<size; ++i)       count[vector[i]-min]++;

    for(int i=1; i<range; ++i)      count[i] += count[i-1];

    for(int i=size-1; i>=0; --i)    output[--count[vector[i]-min]] = vector[i];

    for(int i=0; i<size; ++i)       vector[i] = output[i];

    free(count);
    free(output);

    t = clock()-t;

    return (double)t/CLOCKS_PER_SEC;
}

double BubbleSort(int *vector, int size)
{
    clock_t t = clock();
    
    for(int i=0; i<size-1; ++i)
        for(int j=0; j<size-i-1; ++j)
            if(vector[j] > vector[j+1])
            {
                int aux = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = aux;
            }

    t = clock()-t;

    return (double)t/CLOCKS_PER_SEC;
}

double CocktailSort(int *vector, int size)
{
    clock_t t = clock();

    _Bool swapped = 1;
    int start = 0;
    int end = size;

    while(swapped)
    {
        swapped = 0;

        for(int i=start; i<end-1; ++i)
            if(vector[i] > vector[i+1])
            {
                int aux = vector[i];
                vector[i] = vector[i+1];
                vector[i+1] = aux;
                swapped = 1;
            }

        if(!swapped)    break;

        swapped = 0;
        end--;

        for(int i=end-1; i>=start; --i)
            if(vector[i] > vector[i+1])
            {
                int aux = vector[i];
                vector[i] = vector[i+1];
                vector[i+1] = aux;
                swapped = 1;
            }

        start++;
    }

    t = clock()-t;

    return (double)t/CLOCKS_PER_SEC;
}

int Compare(const void *a, const void *b)
{
    const int *x = (const int*) a;
    const int *y = (const int*) b;

    if(*x > *y) return 1;
    if(*x < *y) return -1;

    return 0;
}

void printVector(int *vector, int size)
{
    for(int i=0; i<size; ++i)
        printf("%d ", vector[i]);
    puts("");
}

void autoGenerate(int *vector, int size)
{
    for(int i=0; i<size; ++i)
        vector[i] = (random() % (size*2)) - (random() % (size*2));
}

int main(void)
{
    int size;
    printf("Introduceti marimea vectorului: ");
    scanf("%d", &size);

    int *vectorInsertion = (int*) malloc(size * sizeof(int));
    int *vectorShell = (int*) malloc(size * sizeof(int));
    int *vectorSelection = (int*) malloc(size * sizeof(int));
    int *vectorCounting = (int*) malloc(size * sizeof(int));
    int *vectorBubble = (int*) malloc(size * sizeof(int));
    int *vectorCocktail = (int*) malloc(size * sizeof(int));
    int *vectorQSORT = (int*) malloc(size * sizeof(int));

    time_t t;
    srand((unsigned) time(&t));

    autoGenerate(vectorInsertion, size);

    for(int i=0; i<size; ++i)
    {
        vectorShell[i] = vectorInsertion[i];
        vectorSelection[i] = vectorInsertion[i];
        vectorCounting[i] = vectorInsertion[i];
        vectorBubble[i] = vectorInsertion[i];
        vectorCocktail[i] = vectorInsertion[i];
        vectorQSORT[i] = vectorInsertion[i];
    }

    clock_t tc = clock();
    qsort(vectorQSORT, size, sizeof(int), Compare);
    tc = clock()-tc;
    
    printf("qsort time          -> %lf\n", (double)tc/CLOCKS_PER_SEC);
    printf("InsertionSort time  -> %lf\n", InsertionSort(vectorInsertion, size));
    printf("ShellSort time      -> %lf\n", ShellSort(vectorShell, size));
    printf("SelectionSort time  -> %lf\n", SelectionSort(vectorSelection, size));
    printf("CountingSort time   -> %lf\n", CountingSort(vectorCounting, size));
    printf("BubbleSort time     -> %lf\n", BubbleSort(vectorBubble, size));
    printf("CocktailSort time   -> %lf\n", CocktailSort(vectorCocktail, size));


    free(vectorInsertion);
    free(vectorShell);
    free(vectorSelection);
    free(vectorCounting);
    free(vectorBubble);
    free(vectorCocktail);
    return 0;
}