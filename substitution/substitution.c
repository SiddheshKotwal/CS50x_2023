#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

// PSET2 Q.3) ANSWER :

int main(int argc, string argv[])
{
    char lowercase[26];
    char uppercase[26];

    if (argv[1] == (void *)0)
    {
        printf("Usage : ./substitution Key");
        return 1;
    }

    char key[strlen(argv[1])];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        key[i] = argv[1][i];
    }

    if (argv[2] != (void *)0)
    {
        printf("ERROR! : Only one command line argument is expected");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("ERROR! : Exactly 26 Alphabets are expected");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!((argv[1][i] >= 'a'  &&  argv[1][i] <= 'z')  || (argv[1][i] >= 'A'  &&  argv[1][i] <= 'Z')))
        {
            printf("ERROR! : Only alphabets are expected in command line arguments");
            return 1;
        }
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if ((key[i] >= 'A')  && (key[i] <= 'Z'))
        {
            lowercase[i] = key[i] + 32;
            // printf ("%c\n",lowercase[i]);
        }
        else if ((key[i] >= 'a')  && (key[i] <= 'z'))
        {
            uppercase [i] = key[i] - 32;
            // printf ("%c\n",uppercase[i]);
        }
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if ((key[i] >= 'a')  && (key[i] <= 'z'))
        {
            lowercase[i] = key[i];
            // printf ("lowercase : %c\n",lowercase[i]);
        }
        else if ((key[i] >= 'A')  && (key[i] <= 'Z'))
        {
            uppercase[i] = key[i];
            // printf ("uppercase : %c\n",uppercase[i]);
        }
    }

    int counter = 0;
    int zero = 0;
    int repeat;
    for (int i = 0; i < strlen(argv[1]) ; i++)
    {
        // printf ("%d",i);
        for (int j = 0; j < strlen(argv[1]) ; j++)
        {
            // printf ("%d",j);
            if (argv[1][i] == lowercase[j]  ||  argv[1][i] == uppercase[j])
            {
                counter++;
                // printf ("%d",counter);
            }

            repeat = counter;
            // printf ("%d",repeat);
            if (repeat > 1)
            {
                printf("ERROR! : All 26 alphabets are expected ,no repetition of alphabets is allowed");
                return 1;
            }
        }
        counter = zero;
    }

    // for (int i = 0; i < 26; i++)
    // {
    //     printf ("lowercase : %c\n",lowercase[i]);
    //     printf ("uppercase : %c\n",uppercase[i]);
    // }

    string p = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(p); i++)
    {
        if ((p[i] >= 'a')  && (p[i] <= 'z'))
        {
            int a = p[i];
            int index = a - 97;
            printf("%c", lowercase[index]);
        }
        else if ((p[i] >= 'A')  && (p[i] <= 'Z'))
        {
            int a = p[i];
            int index = a - 65;
            printf("%c", uppercase[index]);
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;
}