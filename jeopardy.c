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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char buffer2[BUFFER_LEN] = { 0 };
    char stored_answer[BUFFER_LEN]; // New array to store the answer

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    initialize_players(players, NUM_PLAYERS);  // initialize each of the players in the array

    // Player selection
    char selected_player[MAX_LEN];
    printf("Enter the name of the player selected to pick the category: ");
    fgets(buffer, BUFFER_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    strcpy(selected_player, buffer);

    // Validate the selected player's name
    bool player_found = false;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (strcmp(players[i].name, selected_player) == 0) {
            player_found = true;
            break;
        }
    }

    if (!player_found) {
        printf("Error: Selected player not found. Exiting...\n");
        return EXIT_FAILURE;
    }

    // Game loop
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_QUESTIONS; j++) {
            // Display the remaining categories and question dollar amounts
            display_categories_with_values();

            // Prompt for category and dollar amount question
            printf("\nEnter the category and dollar amount question (e.g., 'programming 100'): ");
            fgets(buffer, BUFFER_LEN, stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

            // Tokenize the answer
            char* tokens[BUFFER_LEN] = { 0 };
            tokenize(buffer, tokens);
            char* category_token = strtok(buffer, " ");


            // Validate input format
            if (tokens[0] == NULL || tokens[1] == NULL || atoi(tokens[1]) == 0) {
                printf("Invalid input format. Please enter the category and dollar amount question.\n");
                continue;
            }

            // Check if the category and dollar amount question have been answered
            if (already_answered(tokens[0], atoi(tokens[1]))) {
                printf("Category and dollar amount question already answered. Please select another.\n");
                continue;
            }

            // Display the selected question
            int index_of_question = find_question_index(tokens[0], atoi(tokens[1]));
            if (index_of_question != -1) {
                display_question(tokens[0], atoi(tokens[1]));

            // Extract category and value from user input
            int value = atoi(tokens[1]);

            // Prompt the player for an answer
            printf("Enter your answer (start with 'what is' or 'who is'): ");
            fgets(buffer2, BUFFER_LEN, stdin);
            // Copy the content of buffer2 to stored_answer
            strcpy(stored_answer, buffer2);


            // Tokenize the answer
            char* answer_tokens[BUFFER_LEN] = { 0 };
            tokenize(buffer2, answer_tokens);

            // Check if the answer format is valid
            if ((strcmp(answer_tokens[0], "what") == 0 || strcmp(answer_tokens[0], "who") == 0) && answer_tokens[1] != NULL) {
                if (valid_answer(category_token, value, stored_answer)) {
                    printf("Correct!\n");
                    // Update the player's score
                    update_score(players, NUM_PLAYERS, selected_player, atoi(tokens[1]));
                }
                else {
                    printf("Incorrect! The correct answer is: %s\n", questions[index_of_question].answer);
                }
                // Mark the question as answered
                mark_answered(questions, tokens[0], atoi(tokens[1]));
            }
            else {
                printf("Invalid format for the answer.\n");
            }
            }
            else {
                printf("Question not found.\n");
            }
        }
    }
    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}

void tokenize(char* input, char** tokens) {
    // Tokenize the input string
    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
}

void show_results(player* players, int num_players) {
    // Sort players based on earnings (if necessary)
    // Display players and their earnings from first to last place
    for (int i = 0; i < num_players; i++) {
        printf("Player %d: %s - Earnings: %d\n", i + 1, players[i].name, players[i].score);
    }
}

// Function to find the index of the question based on the category and dollar amount
int find_question_index(char* category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return i; // Return the index of the question
        }
    }
    return -1; // Return -1 if the question is not found
}
