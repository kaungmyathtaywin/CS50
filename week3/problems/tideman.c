#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool makes_circle(int cycle_start, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Update rank index with candidate index in order
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Add votes to the prefered candidate
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Pair index
    int index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // Update winner and loser from preference arrays
                pairs[index].winner = i;
                pairs[index].loser = j;
                // Update number of pairs and pair index
                pair_count++;
                index++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort algorithm
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            // Left and right preference votes for each iteration
            int left_pair = preferences[pairs[j].winner][pairs[j].loser];
            int right_pair = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            // Check if left votes is lower than right
            if (left_pair < right_pair)
            {
                pair smaller = pairs[j];
                pair larger =  pairs[j + 1];

                // If so, switch them
                pairs[j] = larger;
                pairs[j + 1] = smaller;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!makes_circle(pairs[i].winner, pairs[i].loser))
        {
            // Lock the pair unless it makes a circle
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Recursive function to check if entry makes a circle
bool makes_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        // If the current loser is the cycle start
        // The entry makes a circle
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makes_circle(cycle_start, i))
            {
                // Forward progress through the circle
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // False count for each candidate
        int false_count = 0;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
            }
        }

        // Print winner if all pair counts are false
        if (false_count == pair_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
}