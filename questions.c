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
#include <ctype.h>
#include "questions.h"

#define BUFFER_LEN 256

question questions[NUM_QUESTIONS];
 // Copy the initialized questions to the global array
void initialize_game(void)
{
    // Initialize the questions array
    question initial_questions[NUM_QUESTIONS] = {
        {"programming", "0 and 1", "what is binary", 100, false},
        {"programming", "Abstraction", "what is hiding details from the user", 200, false},
        {"programming", "First computer programmer", "who is Ada Lovelace", 300, false},
        {"programming", "Software entities should be open for extension, but closed for modification", "what is Open-Closed principle", 400, false},
        {"algorithms", "A sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order", "what is bubble sort", 100, false},
        {"algorithms", "A sorting algorithm that works by repeatedly selecting the smallest (or largest) element from the unsorted portion of the array and moving it to its final position.", "what is selection sort", 200, false},
        {"algorithms", "Breaking the given problem into subproblems of same type and then recursively solving them", "what is divide and conquer", 300, false},
        {"algorithms", "Father of algorithm", "who is Al-Khwarizmi", 400, false},
        {"databases", "A software system that is used to manage databases", "what is a database management system", 100, false},
        {"databases", "A unique key that can uniquely identify each record in a table", "what is a primary key", 200, false},
        {"databases", "One record in a table can be associated with multiple records in another table, but each record in the second table is associated with only one record in the first table", "what is a one-to-many relationship", 300, false},
        {"databases", "A technique used to bring together data from different tables is known as", "what is a join", 400, false}
    };

    printf("Welcome to Jeopardy!\n");
    printf("Let's get started...\n");

    // Copy the initialized questions to the global array
    memcpy(questions, initial_questions, sizeof(initial_questions));
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("Category: %s\n", categories[i]);

        // Iterate through the questions in the category
        for (int j = 0; j < NUM_QUESTIONS; j++) {
            // Check if the question has not been answered
            if (!questions[j].answered && strcmp(questions[j].category, categories[i]) == 0) {
                printf("  $%d\n", questions[j].value); // Display the question value
            }
        }
        printf("\n"); // Add a newline after displaying all questions in a category
    }
}

// Displays the question for the category and dollar value
void display_question(char* category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        // Check if the question matches the category and value
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            // Check if the question is unanswered
            if (!questions[i].answered) {
                // Display the question
                printf("Category: %s\n", questions[i].category);
                printf("Value: $%d\n", questions[i].value);
                printf("Question: %s\n", questions[i].question);
                return;
            }
            else {
                printf("Question already answered.\n");
                return;
            }
        }
    }
    // If the category is not found or the question is not available
    printf("Question not found.\n");
}

bool valid_answer(char* category, int value, char* answer) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        /*printf("Question category: %s\n", questions[i].category);
        printf("Provided category: %s\n", category);
        printf("Question value: %d\n", questions[i].value);
        printf("Provided value: %d\n", value);
        printf("Question answer: %s\n", questions[i].answer);
        printf("Provided answer: %s\n", answer);*/

        float percentage = 0.8;

        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            if (!questions[i].answered) {
                char correct_answer_lower[BUFFER_LEN];
                char user_answer_lower[BUFFER_LEN];
                // Convert both the correct answer and user's answer to lowercase for case-insensitive comparison
                strcpy(correct_answer_lower, questions[i].answer);
                strcpy(user_answer_lower, answer);
                // Convert to lowercase
                for (int j = 0; correct_answer_lower[j]; j++) {
                    correct_answer_lower[j] = tolower(correct_answer_lower[j]);
                }
                for (int j = 0; user_answer_lower[j]; j++) {
                    user_answer_lower[j] = tolower(user_answer_lower[j]);
                }
                // Check if the answers match
                if (strcmp_custom(correct_answer_lower, user_answer_lower, 0.8) == 0) {
                    // Mark the question as answered
                    questions[i].answered = true;
                    return true; // Answer is correct
                }
                else {
                    return false; // Answer is incorrect
                }
            }
            else {
                return false;  // Question already answered
            }
        }
    }
    // If the category is not found or the question is not available
    return false;
}

//Mark the questions that have already been answered
void mark_answered(question* questions, char* category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            questions[i].answered = true;
            break;
        }
    }
}

// Returns true if the question has already been answered
bool already_answered(char* category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        // Check if the question matches the category and value
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            // Check if the question is answered
            if (questions[i].answered) {
                return true; // Question has been answered
            }
            else {
                return false; // Question has not been answered
            }
        }
    }
    // If the category is not found or the question is not available
    printf("Question not found.\n");
    return false;
}

void display_categories_with_values() {
    int total_questions = 0; // Track the total number of questions displayed

    // Print categories and dollar values for each unanswered question in the questions array
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("Category: %s\n", categories[i]);

        int questions_displayed = 0; // Track the number of questions displayed for the current category

        // Loop through each question in the current category
        for (int j = 0; j < NUM_QUESTIONS; j++) {
            printf("  $%d\n", (j + 1) * 100);
            questions_displayed++;
            total_questions++;
            /*if (!questions[i].answered) {
                
                
            }*/
            // Break the loop if four questions have been displayed for the current category
            if (questions_displayed == 4) {
                break;
            }
        }

        printf("\n");

        // Break the loop if 12 questions have been displayed in total
        if (total_questions == 12) {
            break;
        }
    }
}

// Checks if all questions have been answered
bool all_questions_answered(question* questions) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            return false; // If any question is unanswered, return false
        }
    }
    return true; // If all questions have been answered, return true
}

int strcmp_custom(const char* s1, const char* s2, float percentage) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int min_len = len1 < len2 ? len1 : len2;
    int min_required = min_len * percentage;

    for (int i = 0; i < min_len; i++) {
        if (s1[i] != s2[i]) {
            return -1; // Strings are not identical
        }
    }

    if (min_len < min_required) {
        return -1; // Strings are not identical due to insufficient length
    }

    return 0; // Strings are considered identical
}