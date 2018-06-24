#ifndef List		/* any suggestive variable name is fine */
#define List
struct node    /* Structure*/
{
    char info;
    struct node *ptr;
}*top,*top1,*temp;
void createList(); /* Create empty List */
void addElement(char data); /* Insert element into List */
void deleteElement(); /* Delete element into List  */
#endif
