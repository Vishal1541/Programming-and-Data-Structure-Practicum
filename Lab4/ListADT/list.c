#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/* Create empty List */
void createList()
{
    top = NULL;
}

/* Insert element into List */
void addElement(char data)
{
    if (top == NULL)
    {
        top =(struct node *)malloc(1*sizeof(struct node));
        top->ptr = NULL;
        top->info = data;
    }
    else
    {
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = top;
        temp->info = data;
        top = temp;
    }
}

/* Delete element from List  */
void deleteElement()
{
    top1 = top;
 
    if (top1 == NULL)
    {
        printf("\n Error : Trying to delete from empty list");
        return;
    }
    else
        top1 = top1->ptr;
    printf("\n Delete Value : %c", top->info);
    free(top);
    top = top1;
}

