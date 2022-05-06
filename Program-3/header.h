#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
//--------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//--------------------------------------------------------
///---------------------------------------------------Queue
//--------------------------------------------------------
typedef struct QueueNode
{
    int x;
    struct QueueNode* next;

} QueueNode;
//--------------------------------------------------------
typedef struct Queue
{
    int numberOfElements;
    QueueNode *head;
    QueueNode *tail;

} Queue;
//--------------------------------------------------------
void createQueue(Queue *root);
int isQueueEmpty(Queue *root);
void enqueue(Queue *root, int value);
int dequeue(Queue *root);
void printQueue(QueueNode *node);
void destroyQueue(Queue *root);
int sumQueue(QueueNode *node);
///---------------------------------------------------Stack
typedef struct StackNode StackNode;
typedef struct Stack Stack;
//--------------------------------------------------------
struct StackNode
{
    int data;
    StackNode *next;
};
//--------------------------------------------------------
struct Stack
{
    StackNode *head;
    int size;
};
//--------------------------------------------------------
Stack createStack(); // Returns an empty Stack.
int isEmpty(Stack *stack); // Returns 1 (Stack is empty) or 0 (Stack is not empty).
int countElements(Stack stack); // Returns the size of the Stack.
int push(Stack *stack, int value); // Returns 1 if the operation has been successful. Returns -1 if an error has occurred.
int pop(Stack *stack); // Returns a pointer to the data of the removed StackNode. Returns NULL if the Stack the stack was empty.
int deleteStack(Stack *stack); // Returns 1 if the Stack was deleted successfully. Returns 2 if the Stack was already empty.
int peek(Stack *stack); // Returns a pointer to the data of the Stack head StackNode. Returns NULL if the Stack is empty.
int sumStack(StackNode *stack);
///---------------------------------------------------Program

#endif  HEADER_H_INCLUDED
