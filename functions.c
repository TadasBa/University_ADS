//--------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
//--------------------------------------------------------
void introduction()
{
    /* FUNCTION FOR USER INTERFACE */

    printf("Hello,\n\nThis program lets you to create a simple queue and modify it.\n");
    printf("A queue is basically a linear data structure to store and manipulate the data elements.\n");
    printf("In queues, the first element entered into the array is the first element to be removed from the array.\n");
    printf("Bellow you can find option list.\n\n");
    printf(".........................................................................\n");
    printf("MENU:\n\nEnter 0 to create empty queue\nEnter 1 to add one element to your queue\n");
    printf("Enter 2 to remove one element from your queue\nEnter 3 to print elements of your queue\n");
    printf("Enter 4 to check if queue is empty\nEnter 5 to print number of elements in your queue\n");
    printf("Enter 6 to destroy current queue\nEnter 7 to print information about the first element of the queue\n");
    printf("Enter 8 to exit the program\n");
    printf(".........................................................................\n");
}
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
void enqueue(Queue *root)
{
    /* FUNCTION TO ADD ELEMENT TO THE QUEUE */

    myType elem;
    char   endLine;
    printf("\nEnter element you want to add to the queue: ");

    /* VALIDATING USER INPUT */

    fgets(&elem, 5, stdin);
    //scanf("%c", &elem);

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
void dequeue(Queue *root)
{
    /* FUNCTION TO REMOVE ELEMENT FROM QUEUE */

    QueueNode *temp = root->head;

    if(root->head == NULL)
    {
        root->tail = NULL;
        free(temp);
        return;
    }

    myType data = root->head->x;

    root->head = root->head->next;

    root->numberOfElements--;

    free(temp);

    //return data;
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
        printf("%c -> ",node->x);
        printQueue(node->next);
    }
}
//--------------------------------------------------------
void destroyQueue(Queue *root)
{

    while(root->head != NULL)
    {
        dequeue(root);
    }
    free(root->head);
}

void Menu(Queue *root, int QueueExists)
{
    int   option = 0;

    while(1)
    {
        printf("\nEnter your option here: ");

        while(1)
        {
            int  checkOption; // VARIABLE TO CHECK IF SCANF WORKED CORRECTLY
            char endLine;     // CHAR TO STORE ENDLINE SYMBOL

            checkOption = scanf("%d%c", &option, &endLine);

            if(checkOption != 2 || endLine != '\n')
            {
                printf("\nERROR: Wrong input, please chose options from menu\n\nEnter your option here: ");
                scanf("%*[^\n]");
            }
            else
            {
                break;
            }
        }
        /* MENU */
///----------------------------------------------------------------------------------------------------
        switch(option)
        {
        case 0:     /* USER CHOSE TO CREATE EMPTY QUEUE */
            if(QueueExists>0)
            {
                destroyQueue(root);
                QueueExists--;
            }
            createQueue(root);
            printf("\nEmpty queue successfully created\n");
            QueueExists++;
            break;
///----------------------------------------------------------------------------------------------------
        case 1:     /* USER CHOSE TO ADD ELEMENT TO THE QUEUE */
            if(QueueExists > 0)
            {
                enqueue(root);
                printf("\nElement successfully inserted\n");
            }
            else
            {
                printf("\nERROR: Please create empty queue first\n");
            }
            break;
///----------------------------------------------------------------------------------------------------
        case 2:     /* USER CHOSE TO REMOVE ELEMENT FROM THE QUEUE */
            if(QueueExists > 0)
            {
                dequeue(root);

                if(root->head == NULL)
                {
                    printf("\nQueue is empty\n");
                    break;
                }
                printf("\nElement successfully removed\n");
            }
            else
            {
                printf("\nERROR: Please create empty queue first\n");
            }
            break;
///----------------------------------------------------------------------------------------------------
        case 3:     /* USER CHOSE TO PRINT QUEUE */
            if(QueueExists > 0)
            {
                printf("\n");
                printQueue(root->head);
            }
            else
            {
                printf("\nERROR: Please create empty queue first\n");
            }
            break;
///----------------------------------------------------------------------------------------------------
        case 4:     /* USER CHOSE TO CHECK IF QUEUE IS EMPTY */
            if(QueueExists > 0)
            {
                if(isQueueEmpty(root) == 1)
                {
                    printf("\nQueue is empty\n");
                }
                else
                {
                    printf("\nQueue is not empty\n");
                }
            }
            else
            {
                printf("\nERROR: Queue does not exists. Please create empty queue first\n");
            }

            break;
///----------------------------------------------------------------------------------------------------
        case 5:     /* USER CHOSE TO PRINT NUMBER OF ELEMENTS IN THE QUEUE */
            if(QueueExists > 0)
            {
                printf("\nNumber of elements in queue: %d\n", root->numberOfElements);
            }
            else
            {
                printf("\nERROR: Queue does not exists. Please create empty queue first\n");
            }
            break;
///----------------------------------------------------------------------------------------------------
        case 6:      /* USER CHOSE TO DESTROY QUEUE */
            destroyQueue(root);
            printf("\nQueue destroyed successfully\n");
            break;
///----------------------------------------------------------------------------------------------------
        case 7:     /* USER CHOSE TO PRINT VALUE OF THE FIRST ELEMENT IN QUEUE */
            if(QueueExists > 0)
            {
                printf("\nFirst elem of your queue: %c\nPoints to address: %d\n", root->head->x, root->head->next);
            }
            else
            {
                printf("\nERROR: Please create empty queue first\n");
            }
            break;
///----------------------------------------------------------------------------------------------------
        case 8:     /* USER CHOSE TO EXIT THE PROGRAM */
            printf("\nThank you for using this program, have a nice day\n");
            exit(0);
///----------------------------------------------------------------------------------------------------
        default:    /* USER CHOSE INVALID OPTION */
            printf("\nERROR: No such option, please try again\n");
            break;
        }
///----------------------------------------------------------------------------------------------------
    }
}
