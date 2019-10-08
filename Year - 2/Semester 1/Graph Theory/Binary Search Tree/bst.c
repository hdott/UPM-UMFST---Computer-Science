#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#define MAX 24


typedef struct arbore {
    int numar;
    char data[MAX];
    struct arbore *left;
    struct arbore *right;
} TREE;


TREE *NewElement (int numar, char *data) {
    TREE *newp = (TREE*) malloc(sizeof(TREE));

    newp -> numar = numar;
    memcpy(&newp -> data, data, strlen(data));
    newp -> left = NULL;
    newp -> right = NULL;

    return newp;   
}

int Insert (TREE *tracer, TREE *newp) {
    if (!(tracer)) {
        tracer = newp;
        return 1;
    } else if (newp->numar < tracer->numar) {
        Insert(&tracer->left, newp);
    } else {
        Insert(&tracer->right, newp);
    }

    return 0;
}

void InOrder (TREE *tracer) {
    if (tracer) {
        InOrder(&tracer->left);
        printf("%d - %s", tracer->numar, tracer->data);
        InOrder(&tracer->right);
    }
}

void PreOrder (TREE *tracer) {
    if (tracer) {
        printf("%d - %s", tracer->numar, tracer->data);
        PreOrder(&tracer->left);
        PreOrder(&tracer->right);
    }
}

void PostOrder (TREE *tracer) {
    if (tracer) {
        PostOrder(&tracer->left);
        PostOrder(&tracer->right);
        printf("%d - %s", tracer->numar, tracer->data);
    }
}

int Search (TREE *tracer, int numar) {
    if (!tracer)                        return 0;
    else if (tracer->numar == numar)    return 1;
    else if (numar < tracer->numar)
        Search(&tracer->left, numar);
    else
        Search(&tracer->right, numar);
}

int SearchNotKey (TREE *tracer, char *str) {
    if (!tracer)    return 0;
    else if (!strcmp(tracer->data, str))    return 1;
    else {
        SearchNotKey(tracer->left, str);
        SearchNotKey(tracer->right, str);
    }
}

void PrintNode (TREE *tracer) {
    printf("%d - %s\n", tracer->numar, tracer->data);
}

static TREE *FindSmallest(TREE *tracer) {
    TREE *_smallest = tracer;

    while (_smallest->left) _smallest = _smallest->left;

    return _smallest;
}

TREE *DeleteKey(TREE *tracer, int key) {
    if (!tracer)    return (tracer);

    if (tracer->numar > key)
        tracer->left = DeleteKey(tracer->left, key); 
    else if (tracer->numar < key)
        tracer->right = DeleteKey(tracer->right, key);
    else {
        if (!tracer->left) {
            TREE *_temp = tracer->right;
            
            free(tracer);
            return _temp;
        }
        else if (!tracer->right) {
            TREE *_temp = tracer->left;

            free(tracer);
            return _temp;
        }

        TREE *_temp = FindSmallest(tracer->right);

        tracer->numar = _temp->numar;

        tracer->right = DeleteKey(tracer->right, key);
    }

    return tracer;
}

int DeleteTree (TREE *tracer) {
    if (tracer) {
        DeleteTree(tracer->left);
        DeleteTree(tracer->right);

        free(tracer);
    }
}

void InOrderWithStack (TREE *tracer, STACK *head) {
    while (tracer || !IsEmptyStack(head)) {
        while (tracer) {
            Push(head, NewStack(tracer));
            tracer = tracer->left;
        }

        Pop(head);
        tracer = GetArb(head)->right;
    }    
}

void LevelOrderTraversal (TREE *tracer, QUEUE *head, QUEUE *tail) {
    Enqueue(head, tail, NewQueue(tracer));

    while (!IsEmptyQueue(head)) {
        tracer = GetArbQ(head)->arb;
        Dequeue(head);

        if (tracer->left)   Enqueue(head, tail, NewQueue(tracer->left));
        if (tracer->right)  Enqueue(head, tail, NewQueue(tracer->right));
    }
}