#include <cs50.h>
#include <string.h>
#include <stdio.h>

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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    // look for a candidate called name
    // if candidate found, update ranks and return true. ranks[i] is the voter's ith preference.
    // if no candidate found, don't update any ranks and return false.
    for (int i = 0; i < candidate_count; i++)
    {
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
    // Update the preferences array based on the current voter's ranks.
    // preferences[i][j] is number of voters who prefer i over j
    // int preferences[MAX][MAX];
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //printf("ranks i: %d - ranks j : %d\n", ranks[i], ranks[j]);
            preferences[ranks[i]][ranks[j]] += 1;
        }

    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("votes : %d ", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Add each pair of candidates to pairs array if one candidate is preferred over the other.
    // Update global variable 'pair_count' to be the total number of pairs.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

/*    for (int i = 0; i < pair_count; i++)
    {
        printf("winner : %d, loser: %d\n", pairs[i].winner, pairs[i].loser);
    }
    return;*/
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swap_winner, swap_loser, place = 0;
    // Sort pairs of candidates in decreasing strengh of victory
    for (int i = 0; i < pair_count; i++)
    {
        int cpt_votes = -1;

        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > cpt_votes)
            {
                cpt_votes = preferences[pairs[j].winner][pairs[j].loser];
                place = j;
                swap_winner = pairs[j].winner;
                swap_loser = pairs[j].loser;
            }

        }
        pairs[place] = pairs[i];
        pairs[i].winner = swap_winner;
        pairs[i].loser = swap_loser;
    }
/*    for (int i = 0; i < pair_count; i++)
    {
        printf("winner : %d, loser: %d\n", pairs[i].winner, pairs[i].loser);
    }*/
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Update locked to create the locked graph by adding all edges in decreasing order of victory
    // strengh, as long as there is no cycle
    // locked[i][j] means i is locked in over j
    // bool locked[MAX][MAX];
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Print out the winner of the election, who will be the source of the graph
    // You may assume there will not be more than one source.
    for (int i = 0; i < candidate_count; i++)
    {
        int cpt_true = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                cpt_true++;
                if (cpt_true == 2)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

