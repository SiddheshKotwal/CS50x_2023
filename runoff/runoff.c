#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Filling the preference list of voters
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i].name))
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    // Invalid candidate name
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Calculating votes of non-eliminated candidates
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[preferences[i][0]].eliminated == 0)
        {
            candidates[preferences[i][0]].votes++;
        }
        else if (candidates[preferences[i][1]].eliminated == 0)
        {
            candidates[preferences[i][1]].votes++;
        }
        else if (candidates[preferences[i][2]].eliminated == 0)
        {
            candidates[preferences[i][2]].votes++;
        }
        else if (candidates[preferences[i][3]].eliminated == 0)
        {
            candidates[preferences[i][3]].votes++;
        }
        else if (candidates[preferences[i][4]].eliminated == 0)
        {
            candidates[preferences[i][4]].votes++;
        }
        else if (candidates[preferences[i][5]].eliminated == 0)
        {
            candidates[preferences[i][5]].votes++;
        }
        else if (candidates[preferences[i][6]].eliminated == 0)
        {
            candidates[preferences[i][6]].votes++;
        }
        else if (candidates[preferences[i][7]].eliminated == 0)
        {
            candidates[preferences[i][7]].votes++;
        }
        else
        {
            candidates[preferences[i][8]].votes++;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int total = 0;
    // Calculating total number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        total += candidates[i].votes;
    }

    // Printing winner with maximum votes
    for (int j = 0; j < candidate_count; j++)
    {
        if ((total / 2) + 1 == candidates[j].votes)
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Calculating minimum number of votes to eliminate candidates
    int voteCount = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < voteCount && candidates[i].eliminated == false)
        {
            voteCount = candidates[i].votes;
        }
    }
    return voteCount;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Checking for tie between candidates with maximum votes
    int zero = 0;
    int count = zero;
    int counter, num = zero, save;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == 0)
        {
            num++;
            if (min == candidates[i].votes)
            {
                count++;
            }
            else
            {
                return false;
            }
        }
        save = candidate_count - num;
        counter = count;
    }
    if (counter == candidate_count - save)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Eliminating candidates with lowest votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}