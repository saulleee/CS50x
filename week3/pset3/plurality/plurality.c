#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct {
    string name;
    int votes;
}
candidate;

// Array of candidates (which is initiated with the data type "candidate")
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // candidate_count was declared an int above, and its value is auto set because of "argc - 1", since argv is taking all the names of the candidates.
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // for the following block, the array "candidate" is populated, and each of them are given zero votes. (second line in the for loop)
    // the program takes a CLA, and the number of candidates will then self populated into the array. (first line in the for loop)
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // now, it's asking for the total number of voters, since we'll have to figure out plurality.
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    // it's a for loop, so for the first voter, they'll input a name, which will get vetted by the function "vote"--iterate this through i < voter_count.
    for (int i = 0; i < voter_count; i++) {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name)) { // if (NOT true), ie, FALSE
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
//            candidates[i].votes += 1;
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void) {
    int largestNumber = 0;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > largestNumber) {
            largestNumber = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++) {
        if (largestNumber == candidates[i].votes) {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}