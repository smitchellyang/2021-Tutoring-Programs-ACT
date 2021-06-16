// File Name:   / 0_TestCode_______Math_Operations_Limited.cpp /
// Program Name: [Math Tutor]
// Purpose: Example file to see how a c++ program works on another computer 
// Author: [Scarlett Mitchell-Yang]
// Date Last Modified: T/08/06/21
// ________ Chapter: (5), Loops and Files
// ________ Textbook: Gaddis, Tony. (2018). Starting Out with C++ from Control Structures to Objects
// Cr23D0521

/**************  PROGRAM CONTENTS *********************************************************************|  
    Declare Variables
      -- supplied controllers -- verify input variables --
      -- declare the randomized variables -- equation display --

    LOOP - Menu repeats:
       > Display Menu
       > IF State: Valid Answer Selected
            + Decide Equation
            + Display Question
            + Validate Results
       > IF ELSE:  Error Message
       > ELSE:  End the program

    End Program

*******************************************************************************************************/


// Required Libraries
#include <cstdlib>      // rand(), srand() 
#include <ctime>        // FUNC(time)
#include <iomanip>      // fixes the number of spaces

// Standard Libraries
#include <iostream>
using namespace std;


// Running Program _____________________________________________________________________________________
int main() 
{   
    // DECLARE VARIABLES
    // ---- supplied controllers
    const int MIN = 50;
    const int MAX = 450;
    unsigned seed = time(0);  // Obtaining system time
    srand(seed);              // Seeding the random-generator
    // ---- verify input variables
    char fetchMenuSelection;  
    int userAnswer; 
    // ---- declare the randomized variables
    int addend1, addend2; 
    int dividend, divisor;  
    int val1, val2;
    int newAnswer;    // CALCULATE RESULT
    // ---- equation display
    string symbEquation; 
    string option1 = " + "; 
    string option2 = " / ";


    // LOOP - Menu repeats +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    do 
    {   // DISPLAY MENU  << 0 >>
        cout << endl << "  " << "------------------------------"
             << endl << "  " << "1. Addition problem"
             << endl << "  " << "2. Division problem"
             << endl << "  " << "3. Quit this program"
             << endl << "  " << "------------------------------";
        cout << endl << "  " << "Enter your choice (1-3):  "; 
        cin >> fetchMenuSelection;
        cin.get();

        // VALID ANSWER SELECTED
        if (fetchMenuSelection == '1' || fetchMenuSelection == '2')
        {   // DECIDE EQUATION
            if (fetchMenuSelection == '1') 
            {   val1 = addend1 = ((rand() % (MAX-MIN+1)) + MIN); 
                val2 = addend2 = ((rand() % (MAX-MIN+1)) + MIN);           
                newAnswer = (addend1 + addend2);
                symbEquation = option1;
            }
            else if (fetchMenuSelection == '2')
            {   val2 = divisor = ((rand() % ((9-1)+1)) + 1);           
                val1 = dividend = ((((rand() % (MAX-divisor+1)) + divisor) / divisor) * divisor); 
                newAnswer = (dividend / divisor);
                symbEquation = option2; 
            }

            // DISPLAY QUESTION  << 1 >>
            cout << endl << "  " << val1 << symbEquation << val2 << " =  ";
            // ---- User Input
            cin >> userAnswer;
            cin.get();

            // VALIDATE RESULTS 
            cout << endl << "  " 
                 << ((userAnswer == newAnswer) 
                   ? "Congratulations! That's right." : "Your answer was incorrect.") 
                 << endl << "  " << "The answer is:  " << newAnswer << endl;
            cin.get();
        }
        // ERROR MESSAGE
        else if (fetchMenuSelection != '3')
        {   cout << endl << "  " << "This answer is not valid. Please try again."; 
            cin.get();
        }
        // END THE PROGRAM
        else    cout << "  " << "Thank you for using Math Tutor." << endl; 
    }   
    // LOOP END - Menu repeats +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    while (fetchMenuSelection != '3');


    // End Program 
    return 0; 
}