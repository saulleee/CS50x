#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// voter[i]'s (row) preference[j] (column) for candidate (int), and the INT that gets stored into the array is the CANDIDATE.
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
    // because if user doesn't input an arg at the CL, then that means they didn't input any names.
    if (argc < 2) {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // candidate_count, declared above, is set as an int of "argc - 1".
    // and then if there are too many candidates submitted at the CL by the user (ie, > 100), return 2.
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES) {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // now, populate the array, "candidates". in index i, the name given in the CL is put into "i + 1", then given 0 votes, then given false for eliminated.
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // user inputs the number of voters.
    // "return 3" checks if the users inputs a greater num of voters than allowed.
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS) {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) {\
        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);
            // Record vote, unless it's invalid
            // BUT IF IT'S NOT TRUE (ie, if it returns FALSE at all without considering bang)
            if (!vote(i, j, name)) {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true) {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won) {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie) {
            for (int i = 0; i < candidate_count; i++) {
                if (!candidates[i].eliminated) {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++) {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name) {
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if (strcmp(name, candidates[candidateIndex].name) == 0) {
            preferences[voter][rank] = candidateIndex;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// look at all of the voters’ preferences and compute the current vote totals, by looking at each voter’s top choice candidate who hasn’t yet been eliminated.
void tabulate(void) {
    for (int voterIndex = 0; voterIndex < voter_count; voterIndex++) {
        for (int rankIndex = 0; rankIndex < candidate_count; rankIndex++) {
            int candidateIndex = preferences[voterIndex][rankIndex];
//            if (candidates[candidateIndex].eliminated == false) {
            if (candidates[candidateIndex].eliminated != true)
                candidates[candidateIndex].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void) {
    int majority = (voter_count / 2) + 1;
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if (candidates[candidateIndex].votes >= majority) {
            printf("%s\n", candidates[candidateIndex].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
// determine the fewest number of votes anyone still in the election received
int find_min(void) {
    int min = voter_count;
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
//        if (candidates[candidateIndex].eliminated == false) {
//            if (candidates[candidateIndex].votes < voter_count) {
        if (candidates[candidateIndex].eliminated !=true && candidates[candidateIndex].votes < voter_count)
            min = candidates[candidateIndex].votes;
        }
    }

    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if (min == candidates[candidateIndex].votes) {
            return min;
        }
    }
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min) {
    int remainingCandidates = 0;
    int tiedCandidates = 0;
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
//        if (candidates[candidateIndex].eliminated == false) {
        if (candidates[candidateIndex].eliminiated != true)
            remainingCandidates++;
            if (candidates[candidateIndex].votes == min)
                tiedCandidates++;
        }
    }
/*    if (remainingCandidates == tiedCandidates)
        return true;
    else
        return false;*/
    return (remainingCandidates == tiedCandidates);
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min) {
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if (candidates[candidateIndex].votes == min) {
            candidates[candidateIndex].eliminated = true;
        }
    }
    return;
}