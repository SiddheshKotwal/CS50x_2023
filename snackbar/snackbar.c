#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// PRACTICE PROBLEMS PSET3 : INCOMPLETE ANSWER !!

typedef struct snackbar
{
    char *menu;
    float price;
} snackbar;

float add_items(struct snackbar *ptr);

int main()
{
    snackbar list[9];
    list[0].menu = "Burger";
    list[0].price = 9.50;

    list[1].menu = "Vegan Burger";
    list[1].price = 11.00;

    list[2].menu = "Hot Dog";
    list[2].price = 5.00;

    list[3].menu = "Cheese Dog";
    list[3].price = 7.00;

    list[4].menu = "Fries";
    list[4].price = 5.00;

    list[5].menu = "Cold Pressed Juice";
    list[5].price = 7.00;

    list[6].menu = "Cold Brew";
    list[6].price = 3.00;

    list[7].menu = "Water";
    list[7].price = 2.00;

    list[8].menu = "Soda";
    list[8].price = 2.00;

    printf("\n");
    printf("Welcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n");
    printf("\n");

    // printing the menu list for customer
    for (int i = 0; i < 9; i++)
    {
        printf("%s : $%.2f\n", list[i].menu, list[i].price);
    }
    printf("\n");

    char *temp = malloc(20);
    for (int i = 0; i < 9; i++)
    {
        // converting the menu list to lowercase to compare with input and make it case insensitive
        for (int j = 0; j < strlen(list[i].menu); j++)
        {
            if (isupper(list[i].menu[j]))
            {
                strcpy(temp, list[i].menu);
                list[i].menu = malloc(strlen(list[i].menu));
                strcpy(list[i].menu, temp);
                list[i].menu[j] = tolower(list[i].menu[j]);
                // printf("%s\n", list[i].menu);
            }
        }
    }

    // calling a function after getting total order cost
    float total = add_items(list);
    printf("\n");
    // printing total price of food items
    printf("Your total cost is : %.2f\n", total);
}

float add_items(struct snackbar *ptr)
{
    // getting order from customer and adding the total amount

    float total = 0.00;
    string item;

    do
    {
        // getting input of food item from customer
        item = get_string("Enter a food item : ");

        int len = strlen(item);
        // converting the input to lowercase for comparing with menu list which makes it case insensitive
        for (int i = 0; i < len; i++)
        {
            if (item[i] > 'A'  &&  item[i] < 'Z')
            {
                item[i] = item[i] + 32;
                //    printf("%c\n", item[i]);
            }
        }

        // Getting total price of food item
        for (int i = 0; i < 9; i++)
        {
            if (item[0] == '\0')
            {
                return total;
            }

            // comparing strings to get the price of exact food item
            if (!(strcmp(item, ptr->menu)))
            {
                total += ptr->price;
                // printf("%.2f", total);
            }
            ptr++;
        }

        // returning to the first food item to compare for next input
        for (int i = 0; i < 9; i++)
        {
            ptr--;
        }

    }
    // completing order list by typing enter in prompt
    while (item[0] != '\0');

    return total;
}