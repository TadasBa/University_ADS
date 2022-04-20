#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
//--------------------------------------------------------
typedef void* myType;
//--------------------------------------------------------
typedef struct QueueNode
{
    myType x;
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
void introduction();
void createQueue(Queue *root);
int isQueueEmpty(Queue *root);
void enqueue(Queue *root);
void dequeue(Queue *root);
void printQueue(QueueNode *node);
void destroyQueue(Queue *root);
void Menu(Queue *root, int QueueExists);
#endif // HEADER_H_INCLUDED
