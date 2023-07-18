/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Jenny Kim
Student ID#: 139787220
Email      : ykim314@myseneca.ca
Section    : NMM
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include "core.h"
#include <string.h>
//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

int inputInt(void) {

    int number = 0;
    char space = ' ';


    do {
        scanf("%d%c", &number, &space);

        if (space != '\n') {

            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }

    } while (space != '\n');

    return number;
}

int inputIntPositive(void) {

    int number;
    char space = ' ';


    do {
        scanf("%d%c", &number, &space);

        if (space != '\n') {
            clearInputBuffer();
            printf("Error! Input a number: ");
        }

        else if (number <= 0) {
            printf("ERROR! Value must be > 0: ");
        }

    } while (number <= 0);

    return number;
}


int inputIntRange(int lower_bound, int  upper_bound) {

    int user_input = lower_bound - 1;

    do {
        user_input = inputInt();

        if (user_input < lower_bound || user_input > upper_bound) {
            printf("ERROR! Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
        }

    } while ((user_input < lower_bound) || (user_input > upper_bound));

    return user_input;
}




char inputCharOption(const char Cstring_list[]) {

    char user_input;

    while (1 == 1) {
        scanf("%c", &user_input);

        int i = 0;
        int size = strlen(Cstring_list);


        for (i = 0; i < size; i++) {
            if (user_input == Cstring_list[i]) {

                clearInputBuffer();
                return Cstring_list[i];
            }
        }
        
        printf("ERROR: Character must be one of [%s]: ", Cstring_list);
        clearInputBuffer();
    }
}



void inputCString(char* cString, int min_char_number, int max_char_number){
    int flag = 1;
    char character = 'c';

    while (flag) {

        int length = 0;
        
        while(length <= max_char_number && character != '\n'){

            character = getchar();
            cString[length] = character;
            length++;
        };

        if (length <= (max_char_number +1) && character == '\n'){

            length--;
            cString[length] = '\0';
        }
     
        else {

            cString[max_char_number] = '\0';
            clearInputBuffer();
        }

        if(length != min_char_number && min_char_number== max_char_number){

            printf("ERROR: String length must be exactly %d chars: ", min_char_number);
            character = 'c';
        }
        else if (length < min_char_number || length > max_char_number) {

            if (length > max_char_number) {

                printf("ERROR: String length must be no more than %d chars: ", max_char_number);
                character = 'c';
            }
            else if (length < min_char_number) {

                printf("ERROR: String length must be between %d and %d chars: ", min_char_number, max_char_number);
                character = 'c';
            }
        }
        else {
            flag = 0;
        }
    }
}

//Function exclusively for input numbers
void inputNumbers(char* string, int min_number, int max_number) {
    int flag = 1;
    char character = 'c';

    while (flag) {
        int len = 0;
        
        while(len<=max_number && character != '\n'){

            character = getchar();
            string[len] = character;
            len++;
        };

       
        if(len <= (max_number+1) && character =='\n'){
            len--;
            string[len] = '\0';
        }
     
        else {
            string[max_number] = '\0';
            clearInputBuffer();
        }
        if(len != min_number && min_number == max_number){
            printf("Invalid 10-digit number! Number: ");
            character = 'c';
        }

        else {
            flag = 0;
        }
    }
}

void displayFormattedPhone(const char* arr) {

    int i = 0;
    int size = strlen(arr);

    if (arr == NULL) {
        printf("(___)___-____"); return;
    }

    if (size != 10) {
        printf("(___)___-____"); return;
    }

    for (i = 0; i < 10; ++i) {

        if (
            !(arr[i] == '0' ||
                arr[i] == '1' ||
                arr[i] == '2' ||
                arr[i] == '3' ||
                arr[i] == '4' ||
                arr[i] == '5' ||
                arr[i] == '6' ||
                arr[i] == '7' ||
                arr[i] == '8' ||
                arr[i] == '9')
            )
        {
            printf("(___)___-____");
            return;
        }
    }

    printf(
        "(%c%c%c)%c%c%c-%c%c%c%c",

        arr[0], arr[1], arr[2], arr[3], arr[4],
        arr[5], arr[6], arr[7], arr[8], arr[9]
    );
}