#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name: "); //declare a string with 'name' variable

    printf("hello, %s\n", name); //then print the name with %s
}