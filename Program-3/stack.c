/// AUTHOR: Š.Griškus
/// YEAR:   2022
#include "header.h"
//--------------------------------------------------------
Stack createStack()
{
    Stack stack;
    stack.head = NULL;
    stack.size = 0;
    return stack;
}
//--------------------------------------------------------
int isEmpty(Stack *stack)
{
    if(stack->head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//--------------------------------------------------------
int countElements(Stack stack)
{
    return stack.size;
}
//--------------------------------------------------------
int sumStack(StackNode *stack)
{
    int sum=0;

    while(stack != NULL)
    {
        sum += stack->data;
        stack = stack->next;
    }

    return sum;
}
//--------------------------------------------------------
int push(Stack *stack, int value)
{
    StackNode *newElement = (StackNode*)malloc(sizeof(StackNode));
    if(!newElement)
    {
        return -1;
    }
    newElement->data = value;
    newElement->next = stack->head;

    stack->head = newElement;
    ++(*stack).size;

    return value;
}
//--------------------------------------------------------
int pop(Stack *stack)
{
    if(isEmpty(stack))
    {
        return 0;
    }
    StackNode *currentElement = stack->head;
    stack->head = currentElement->next;
    int value = currentElement->data;
    free(currentElement);
    --(*stack).size;
    return value;
}
//--------------------------------------------------------
int deleteStack(Stack *stack)
{
    if(isEmpty(stack))
    {
        return 2;
    }
    StackNode *currentElement = stack->head;
    StackNode *temp;

    while(currentElement != NULL)
    {
        temp = currentElement->next;
        free(currentElement);
        currentElement = temp;
    }

    stack->head = NULL;
    return 1;
}
//--------------------------------------------------------
int peek(Stack *stack)
{
    if(isEmpty(stack))
    {
        return 0;
    }
    return stack->head->data;
}
//--------------------------------------------------------
void printStack(StackNode *node)
{
    if(node == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d -> ",node->data);
        printStack(node->next);
    }
}
//--------------------------------------------------------
