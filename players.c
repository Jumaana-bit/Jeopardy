/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, Jumaana Aslam, Somya Babar
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

#define NUM_PLAYERS 4
#define MAX__LEN 256

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    for (int i = 0; i < num_players; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return true; // Player name matches an existing player
        }
    }
    return false; // Player name does not match any existing player
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score)
{
    for (int i = 0; i < num_players; i++) {
        if (strcmp(players[i].name, name) == 0) {
            // Update the score for the player
            players[i].score += score;
            break; // Exit the loop after updating the score
        }
    }
}

void initialize_players(player players[], int num_players) {
    printf("Enter the names of the four players:\n");

    for (int i = 0; i < num_players; i++) {
        printf("Enter name for Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        // Remove the newline character if present
        players[i].name[strcspn(players[i].name, "\n")] = '\0';
        players[i].score = 0; // Initialize earnings to 0
    }
}