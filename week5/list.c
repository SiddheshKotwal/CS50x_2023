#include <stdio.h>
#include <stdlib.h>

// RESIZING THE ARRAY

int main()
{
    // making an array to store 3 integers
    int *list = malloc(3 * sizeof(int));
    if(list == NULL)
    {
        return 1;
    }

    // storing 3 integers
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    //...

    // we need one more integer in array but if there is some other data after the 3rd integer,
    // we need to make a new array for 4 integers and copy the previous array till 3rd int and add one more integer to it
    int *tmp = malloc(4 * sizeof(int));
    if(tmp == NULL)
    {
        free(list);
        return 1;
    }

    for(int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3] = 4;

    // freeing the previous array of 3 integers
    free(list);
    // assigning the list pointer to our new array of 4 integers
    list = tmp;

    // so at this moment list and tmp both arer pointing to the same array
    for(int i = 0; i < 4; i++)
    {
        printf("%d\n", list[i]);
    }

    // freeing the memory at which both are pointing
    // so we can free from any one pointer as they are pointing to the same memory location
    free(list);
    return 0;
}