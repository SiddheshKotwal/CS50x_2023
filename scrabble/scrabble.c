#include <stdio.h>
#include <cs50.h>
#include <string.h>

// WEEK2 LAB 2 : ANSWER :

void compute_score(string word1, string word2, int *score1, int *score2);

// Points assigned to each letter of the alphabet
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char lowercase[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char uppercase[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main()
{
    // Get input words from both players
    string word1 = get_string("Player 1 : ");
    string word2 = get_string("Player 2 : ");

    int score1 = 0 ;
    int score2 = 0 ;

    // Score both words
    compute_score(word1, word2, &score1, &score2);
}

void compute_score(string word1, string word2, int *score1, int *score2)
{
    // TODO: Compute and return score for string
    int ans1, ans2;

    for (int i = 0; i < strlen(word1); i++)
    {
        for (int j = 0; j <= 26; j++)
        {
            if (word1[i] == lowercase[j]  ||  word1[i] == uppercase[j])
            {
                *score1 += points[j];
                ans1 = *score1;
            }
        }
    }

    for (int i = 0; i < strlen(word2); i++)
    {
        for (int j = 0; j <= 26; j++)
        {
            if (word2[i] == lowercase[j]  ||  word2[i] == uppercase[j])
            {
                *score2 += points[j];
                ans2 = *score2;
            }
        }
    }

    // TODO: Print the winner
    if (ans1 > ans2)
    {
        printf("Player 1 wins!\n");
    }
    else if (ans1 < ans2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("tie!\n");
    }
}