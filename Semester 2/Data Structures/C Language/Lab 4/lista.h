#include <stdio.h>

typedef struct lista LIST;

extern LIST *head;

LIST *NewElement(unsigned number);

void ControlLink(int option1, int option2, unsigned key, LIST *newp);