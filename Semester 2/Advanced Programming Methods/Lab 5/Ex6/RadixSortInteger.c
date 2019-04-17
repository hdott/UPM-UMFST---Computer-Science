#include <stdio.h>
#include <stdlib.h>

static void CountingSortBytes(int *vector, int size, int bytePoz)
{
    int count[256] = {0};
    int *output = (int*) malloc(size * sizeof(int));
    int range = 256;
    __uint8_t *pI = NULL;

    for(int i=0; i<size; ++i)       
    {
        pI = (__uint8_t*) &vector[i];
        count[*(pI+bytePoz)]++;
    }

    for(int i=1; i<range; ++i)      count[i] += count[i-1];

    for(int i=size-1; i>=0; --i)    
    {
        pI = (__uint8_t*) &vector[i];
        output[--count[*(pI+bytePoz)]] = vector[i];
    }

    int index;
    for(index=0; index<size; ++index)
        if(output[index]<0) break;

    for(int i=0; i<size; ++i, ++index)
    {
        if(index==size) index=0;

        vector[i] = output[index];
    }

    free(output);
}

void RadixSort(int *vector, int size)
{
    for(int i=sizeof(int)-1; i>=0; --i)
        CountingSortBytes(vector, size, i);
}