//--------------------------------------------------------
#include "header.h"
//--------------------------------------------------------
void createQueue(Queue *root)
{
    /* FUNCTION FOR INITIALIZING EXTREMUMS OF NEW QUEUE */

    root->numberOfElements = 0;
    root->head  = NULL;
    root->tail  = NULL;
}
//--------------------------------------------------------
int isQueueEmpty(Queue *root)
{
    /* FUNCTION TO CHECK IF QUEUE IS EMPTY */

    if(root->head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//--------------------------------------------------------
int sumQueue(QueueNode *node)
{
    /* FUNCTION TO DISPLAY QUEUE IN THE SCREEN */

    int sum=0;

    while(node != NULL)
    {
        sum += node->x;
        node = node->next;
    }

    return sum;
}
//--------------------------------------------------------
void enqueue(Queue *root, int elem)
{
    /* FUNCTION TO ADD ELEMENT TO THE QUEUE */

    /* ADDING ELEMENT AT THE END OF THE QUEUE */

    QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));

    temp->x = elem;
    temp->next = NULL;

    if(!isQueueEmpty(root))
    {
        root->tail->next = temp;
        root->tail = temp;
    }
    else
    {
        root->head = temp;
        root->tail  = temp;
    }
    root->numberOfElements++;
}
//--------------------------------------------------------
int dequeue(Queue *root)
{
    /* FUNCTION TO REMOVE ELEMENT FROM QUEUE */

    QueueNode *temp = root->head;

    if(root->head == NULL)
    {
        root->tail = NULL;
        free(temp);
        return 0;
    }

    int data = root->head->x;

    root->head = root->head->next;

    root->numberOfElements--;

    free(temp);

    return data;
}
//--------------------------------------------------------
void printQueue(QueueNode *node)
{
    /* FUNCTION TO DISPLAY QUEUE IN THE SCREEN */

    if(node == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d -> ",node->x);
        printQueue(node->next);
    }
}
//--------------------------------------------------------
void destroyQueue(Queue *root)
{
    /* FUNCTION TO DESTROY QUEUE */

    while(root->head != NULL)
    {
        dequeue(root);
    }
    free(root->head);
}
