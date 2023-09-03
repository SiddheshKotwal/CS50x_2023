#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Usage: ./linked_list numbers_to_store_in_list\n");
        return 1;
    }

    node *list = NULL;

    for(int i = 1; i < argc; i++)
    {
        int num = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return 1;
        }

        n->number = num;
        n->next = list;
        list = n;
    }

    for(node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\n", ptr->number);
    }

    node *ptr = list;
    while(ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    return 0;
}