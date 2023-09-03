#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int byte = 8;

int main(void)
{
    // Getting Message
    string text = get_string("Message : ");

    int decimals[strlen(text)];
    for (int i = 0; i < strlen(text); i++)
    {
        decimals[i] = text[i];
        // printf ("%d\n",decimals[i]);
    }

    int binary [strlen(text) * byte];
    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 0; j < byte; j++)
        {
            binary[j] = decimals[i] % 2;
            decimals[i] = decimals[i] / 2;
        }

        // turning bits into bulbs
        for (int j = 7; j >= 0; j--)
        {
            if (binary[j] == 0)
            {
                // Dark emoji
                printf("\U000026AB");
            }
            else if (binary[j] == 1)
            {
                // Light emoji
                printf("\U0001F7E1");
            }
        }
        // Printing 8 bulbs in one row
        printf("\n");
    }
}