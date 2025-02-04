/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Sean Muniz
Student ID#: 102411188
Email      : smuniz@myseneca.ca
Section    : BTP 100 NAA
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

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
int inputInt(void)
{
    char newLine = 'X';
    int value;
    int exit = 0;

    do 
    {
        scanf("%d%c", &value, &newLine);/*recieves user input and assigns it to 'value' 
                                        and 'newLine'. */

        if (newLine == '\n') /*if 'newLine does equal the newline character "\n" the 
                            loop exits. This means that a valid integer was entered.*/
           exit = 1;

        else
        {
            clearInputBuffer(); // function clears input buffer. 
            printf("Error! Input a whole number: "); /* if newline chracater is not entered, that means a valid integer 
                                                    was not entered. */
        }
    }while(exit == 0);
    return value; /*value that is stored in 'value' variable gets returned. 
                  user expected to enter '-100'. if '-100' is entered, pass message prints from 
                  a1ms1.c  */
}

int inputIntPositive(void)
{
    int posValue;
    do
    {
        posValue = inputInt();/* result of the function call gets assigned to 'posValue'
                                variable. */

        if (posValue <=0)/* if result of function call is NOT a positive integer, error
                            message gets printed. */
        {
            printf("ERROR! Value must be > 0: ");
         }
    } while (posValue <= 0);
    return posValue;/*value in this variable gets returned. user is expected to enter '200'. 
                    if '200' is entered, pass message prints from a1ms1.c*/
}

int inputIntRange(int lowerBoud, int upperBound)
{
    int validInput;
    do
    {
        validInput = inputInt();/*result of function call gets assigned to 'valudInput'*/

        if (validInput < lowerBoud || validInput > upperBound)/* if result of function call is not between 
                                                                the lower and upper bound, error message gets printed. */
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBoud, upperBound);

    } while (!(validInput>= lowerBoud && validInput <= upperBound));
    return validInput;/*value of this variable gets returned. user is expected to enter -3 and 14 
                    (function gets called twice). if the expected values are entered, pass message from 
                    a1ms1.c gets printed. */
}

char inputCharOption (const char* str)
{
    char charVal, retVal;
    int i = 0, exit = 0;
    do
    {
        scanf(" %c%c", &charVal, &retVal);/*result of function call, gets assigned to 'charVal'.
                            getChar() recieves user input.*/
        if (retVal == '\n')
        {
            for (i = 0 ; str[i] != '\0' ; i++)
            {
                if (str[i] == charVal)
                {
                    exit = 1;
                }
            }
        }
        else
        {
            printf("ERROR: Character must be one of [%s]: ", str);
        }

    } while (exit != 1);
    return charVal;    /*charVal gets returned. if the user enters the expected value (r), 
                        the pass message will be printed from a1ms1.c*/
}

void inputCString(char* str, int minChar, int maxChar)/*this function checks to see if 
                                                        the string that is entered is of a certain length.*/
{ 
   char cString[256]; 
   int exit = 0, count;
    
   do 
   {
    scanf(" %[^\n]", cString);/*accepts user input and assigns it to cString array.*/
    count = 0;
    while (cString[count] != '\0')/*this while loop gets the size of the cString array. */
    {
        count++;/*count increments by 1 until the null terminator is reached. the value of count
                represents the size of the cString Array and the size of the string that the user 
                entered. */
    }
    //for when the user is expected to enter a string of a specified length
    //=========================================================================
    if (minChar == maxChar) 
    {
        if (count == minChar && count == maxChar)
        {
            exit = 1;
           strcpy(str, cString);
        }
        else if (count != maxChar && count != minChar)/*logic for when the entered string 
                                                        is not the same as the specified lentgh. */
        {
            printf("Invalid %d-digit number! Number: ", maxChar);
        }
    }
    //for when the user is expected to enter a string that is between the minChar and maxChar parameters
    //=========================================================================
    else if (count <= maxChar&& count >=minChar)
    {
        exit = 1;
        strcpy(str, cString);
        clearInputBuffer();
    }
    //error messages for when the entered string does not fit within the minChar and macChar
    //=========================================================================
    else if (count > maxChar)
    {
        printf("ERROR: String length must be no more than %d chars: ", maxChar);
    }
    else if (count < minChar)
    {
        printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
    }
   } while (exit == 0);
}

void displayFormattedPhone(const char *phone)
{
    const int maxDigits = 10;
    //const char validChars[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    int i, count, error =0;

    if (phone == NULL)/*if array has Null value, error message gets printed.*/
    {
        printf("(___)___-____");
    }
    else if (phone != NULL)
    {
        count = 0; 
        while (phone[count] != '\0')/*while loop gets the size of the array.*/
        {
            count++;/* the value of count represnts the size of the array.*/
        }

        if (count != maxDigits)/*if 'count' (size of the array) is not the same as 'maxDigits'
                                error message gets printed.*/
        {
            printf("(___)___-____");
        }
        else if (count == maxDigits) /* for when 'count' and 'maxDigits' are the same.*/
        {
            for (i = 0 ; i < maxDigits ; i ++) /* for loop iterates through the character array.*/
            {
                if (phone[i] < '0' || phone[i] > '9' )/*if the character is not a digit between 0 and 9
                                                        'error' variable gets initialized to 1.*/
                    {
                        error = 1;
                    }
            }
            if (error == 1) /*if 'error' equals 1, that means that there was a character that IS NOT 
                            a digit between 0 and 9. Error message gets printed.*/
            {
                printf("(___)___-____");
            }
            else if (error == 0)/*if error still equals 0, that means that there was no invalid character
                                detected. This will print the characters of the array in the specified 
                                format. */
            {
                printf("(%c%c%c)%c%c%c-%c%c%c%c", phone[0], phone[1], phone[2],
                                                phone[3], phone[4], phone[5], 
                                                phone[6], phone[7], phone[8], 
                                                phone[9]);
            } 
        }
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
