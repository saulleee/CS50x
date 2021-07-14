#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
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

// Test and custom functions
void print_preferences(void);
int marginOfVictory(int pairsIndex);
void decreasingSwap(int firstPairsIndex, int secondPairsIndex);
bool checkCycle(int pairsIndex);

int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    // the array[i][j] here is voter x preference, and the int being filled in is the candidate's index.
    // then the array spits out an updated ranks array, which is filled with the candidate's index.
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();

    printf("===NON-SORTED PAIRS===\n");
    for (int i = 0 ; i < pair_count ; i++) {
        pair p = pairs[i];
        printf("winner:%d  loser:%d \n", p.winner, p.loser);
    }
    printf("\n");

    sort_pairs();

    printf("===SORTED PAIRS===\n");
    for (int i = 0 ; i < pair_count ; i++) {
        pair p = pairs[i];
        printf("winner:%d  loser:%d \n", p.winner, p.loser);
    }
    printf("\n");

    print_preferences();
    // you should get {2, 0}, {1, 2}, {1, 0}

    lock_pairs();

    printf("===LOCKED PAIRS===\n");
    for (int i = 0; i < pair_count; i++) {
        pair p = pairs[i];
        printf("%d\n", locked[p.winner][p.loser]);
    }

    print_winner();
    return 0;
}




// Update ranks given a new vote
// the candidate's index is being put into ranks[rank] (or, according to the if(!vote(j, name, ranks)) condition in main, ranks[j]).
bool vote(int rank, string name, int ranks[]) {
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if (strcmp(name, candidates[candidateIndex]) == 0) {
            ranks[rank] = candidateIndex;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// ranks[i], which references the candidate's index
// trying to make an array, preferences, where it's the candidate_count by the candidate_count, and the int inside is the number of people who prefer [1][0] to [0][1].
void record_preferences(int ranks[]) {
    for (int ranksIndex = 0; ranksIndex < candidate_count; ranksIndex++) {
        for (int ranksLowerIndex = ranksIndex + 1; ranksLowerIndex < candidate_count; ranksLowerIndex++) {
            // oops
            int winnerCandidate = ranks[ranksIndex];
            int loserCandidate = ranks[ranksLowerIndex];
            preferences[winnerCandidate][loserCandidate]++;
        }
    }
    return;
}

// custom function to print to check/debug.
void print_preferences(void) {
    printf("===PREFERENCES TABLE===\n");
    for (int i = 0 ; i < candidate_count ; i++) {
        for (int j = 0 ; j < candidate_count ; j++) {
          printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Record pairs of candidates where one is preferred over the other
// need to update 2 things: array pairs and int pair_count.
// 1. i want to make two variables: prefIVoteCount and prefJVoteCount. they will be assigned to a pair of candidates ([i][j] and [j][i]).
// 2. then, if the pair is not equivalent to each other (ie, one is greater than the other), i want to assign winners and losers to pairs[i].winner and pairs[i].loser.
// 3. then, add 1 to pair_count.
void add_pairs(void) {
    pair_count = 0;
    for (int candidateI = 0; candidateI < candidate_count; candidateI++) {
        for (int candidateJ = candidateI + 1; candidateJ < candidate_count; candidateJ++) {
            int prefIVoteCount = preferences[candidateI][candidateJ];
            int prefJVoteCount = preferences[candidateJ][candidateI];
            if (prefIVoteCount > prefJVoteCount) {
                pairs[pair_count].winner = candidateI;
                pairs[pair_count].loser = candidateJ;
                pair_count++;
            } else if (prefIVoteCount < prefJVoteCount) {
                pairs[pair_count].winner = candidateJ;
                pairs[pair_count].loser = candidateI;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// two for loops here because bubble sort is O(n^2), it's iterating through the array n times.
void sort_pairs(void) {
    for (int pairsIndex = 0; pairsIndex < pair_count - 1; pairsIndex++) {
        for (int pairsNextIndex = pairsIndex + 1; pairsNextIndex < pair_count; pairsNextIndex++) {
            if (marginOfVictory(pairsIndex) < marginOfVictory(pairsNextIndex)) {
                decreasingSwap(pairsIndex, pairsNextIndex);
            }
        }
    }
    return;
}

// custom function for sort_pairs.
// it's taking the value inside preferences[i][j] and getting the difference from its reciprocal, preferences[j][i].
// which pairs i get is already decided by the function add_pairs.
int marginOfVictory(int pairsIndex) {
    int margin = preferences[pairs[pairsIndex].winner][pairs[pairsIndex].loser] - preferences[pairs[pairsIndex].loser][pairs[pairsIndex].winner];
    return margin;
}

// custom function for sort_pairs.
// it's just swapping the pairs array.
void decreasingSwap(int firstPairsIndex, int secondPairsIndex) {
    pair temp = pairs[firstPairsIndex];
    pairs[firstPairsIndex] = pairs[secondPairsIndex];
    pairs[secondPairsIndex] = temp;
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// from line 11:
// locked[i][j] means i is locked in over j
// bool locked[MAX][MAX];
// making "bool locked[i][j]" true based off of the sorted pairs array.
// but somehow not creating a cycle.
void lock_pairs(void) {
    for (int pairsIndex = 0; pairsIndex < pair_count; pairsIndex++) {
        if (checkCycle(pairsIndex) != true) {
            locked[pairs[pairsIndex].winner][pairs[pairsIndex].loser] = true;
        }
    }
    return;
}

bool checkCycle(int pairsIndex) {
    int pairsIndexCC = pairsIndex;
    for (int i = 0; i <= pairsIndex; i++) {
        if (pairs[pairsIndexCC].winner == pairs[i].loser) {
            pairsIndexCC = i;
            if (pairsIndexCC == pairsIndex) {
                return true;
            }
            i = 0;
        }
    }
    return false;
}

// DRAFT 1
// bool checkCycle(int pairsIndex) {
//     if (pairsIndex == 0) {
//         return false;
//     }
//     for (int i = pairsIndex; i > 0; i--) {
//         if (pairs[i].winner != pairs[i - 1].loser) {
//             return false;
//         }
//     }
//     return true;
// }

// Print the winner of the election
void print_winner(void) {
    // TODO
    return;
}