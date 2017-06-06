#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct A {
    char* name;
    int i;
    struct A* prev;
} A;

typedef struct B {
    char* name;
    char c;
    struct B* prev;
} B;

void* newStruct(char* type, int c){
    void* temp;
    if(strcmp(type,"A")==0){
        A* temp = (A*)malloc(sizeof(A));
        temp->name = "A";
        temp->i = c;
    }else{
        B* temp = (B*)malloc(sizeof(B));
        temp->name = "B";
        temp->c = c;
    }
    return temp;
}
void push(void* stack, void* elem){
    elem->prev = stack;
    stack = elem;
}

void* pop(void* stack){
    void* temp = stack;
    stack = stack->prev;
    temp->prev = NULL;
    return temp;
}
