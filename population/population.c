#include <stdio.h>
#include <cs50.h>

// WEEK 1 LAB 1 : ANSWER :

int main()
{
    int start_size;
    int end_size;
    do
    {
        // TODO: Prompt for start size
        start_size = get_int("Start size : ");

    }
    while (start_size < 9);

    do
    {
        // TODO: Prompt for end size
        end_size = get_int("End size : ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int growth = start_size;
    int counter = 0;
    int years = 0;

    while (growth < end_size)
    {
        growth = growth + (growth / 3) - (growth / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d", years);
}