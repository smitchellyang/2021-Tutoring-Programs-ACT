// File Name:   / 1__MathTutoring_RapidCalculations.cpp /
// Program Name: [Math Tutor]
// Purpose: Example file to see how a c++ program works on another computer 
// Author: [Scarlett Mitchell-Yang]
// Date Last Modified: W/16/06/21
// Date Created: T/08/06/21


// Required File Libraries
#include <cstdlib>      // rand(), srand() 
#include <ctime>        // FUNC(time)
#include <iomanip>      // fixes the number of spaces
#include <cstdlib>      // atoi("~");
#include <string>

// Standard File Libraries
#include <iostream>
using namespace std;

// Structure 
struct stats
{   // ---- automatic calculations
    short answers_correct = 0;
    short answers_incorr = 0; 
    short answers_unansw = 0; 
    double percent_corr = 0;
    double percent_incor = 0;
    // ---- optional calculations
    int time = -2;
    float seconds_perQuest = 0; 
};

struct arrElems
{   // element descriptors for array navigation
    const int ACCURACY = 0;
    const int STUD_ANS = 1; 
    const int EQUATION = 2;
    const int VALUE1 = 3; 
    const int VALUE2 = 4;
    const int SOLUTION = 5;
    // pieces for building string literals
    string times = " * ";
    string divided_by = " / ";
    string equals = " =  \0";
    string closeStr = "\0"; 
    // extra variables for specification
    int val1; 
    int val2;
    int solution;
};

// DECLARED FUNCTIONS
void showMenu(int *inpReturn, int *size, bool *endProg);
void createTrial(int selection, int crnt, string **equationInfo);
stats getInput_equations(int numEquations, string **equation); 
int getInput_timetaken();
void displayResults(stats crntTrial, int numEquations, string **equationInfo);
// ---- test algorithm
void displayQuestions(int path, int arrSize, string **equationInfo);


// Running Program _____________________________________________________________________________________
int main() 
{
    // DECLARE VARIABLES
    // ---- supplied controllers
    unsigned seed = time(0);  // Obtaining system time
    srand(seed);              // Seeding the random-generator
    // ---- verify input variables
    int fetchMenuSelection;  
    int trialSize; 
    bool endMenu;
    // ---- declare the randomized variables
    int val1, val2;
    // ---- "trial" breakdown
    const int TRIAL_arrELEMS = 6;
    int studAnsw_corr = -1; 
    /*  rows :    each equation in particular
        trial[0]   - student accuracy
        trial[1]   - student answer
        trial[2]   - equation
        trial[3]   - equation's first value
        trial[4]   - equation's second value
        trial[5]   - equation answer
    */   


    // LOOP - Menu repeats +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    do 
    {   // SETTINGS INPUT
        endMenu = false;    // Flag Reset 
        studAnsw_corr = -1; 
        showMenu(&fetchMenuSelection, &trialSize, &endMenu);

        // FLAG BUMPER
        if (fetchMenuSelection != '3')
        {   // PROCESSING 
            string **trial = new string*[trialSize];
            for (int c = 0; c < trialSize; c++)
            {   trial[c] = new string[TRIAL_arrELEMS];
                createTrial(fetchMenuSelection, c, trial);
            }
            
            // INPUT
            stats results = getInput_equations(trialSize, trial);

            // RESULTS
            displayResults(results, trialSize, trial);
            /*
            */
            // DISPLAY ALL
            //displayQuestions(1, trialSize, trial);


            // CLEAN UP
            for (int c = 0; c < trialSize; c++)
                delete [] trial[c];        
            delete [] trial;
        }
    } 
    while (!endMenu);

    cin.get();
    return 0;
}
// Running Program End _________________________________________________________________________________

void displayResults(stats crntTrial, int numEquations, string **equationInfo)
{   arrElems a;
    // PROCESSING - establish other values
    crntTrial.percent_corr = 1.00 * (100 * crntTrial.answers_correct / numEquations); 
    crntTrial.percent_incor = 1.00 * (100 * crntTrial.answers_incorr / numEquations); 
    // INPUT - calculate time
    cout << endl << endl << "  "<< "What was your time?";
    crntTrial.time = getInput_timetaken();
    // PROCESSING - establish time
    crntTrial.seconds_perQuest = 1.00 * (crntTrial.time / numEquations);

    // DISPLAY - show results
    cout << endl << endl << "  " << "RESULTS"; 
    if (crntTrial.time != -2)
        cout << setprecision(2) << fixed << showpoint
             << endl << "  " << "  - Seconds per question: " << crntTrial.seconds_perQuest
             ;
    cout << endl
         << endl << "  " << " Number of Incorrect Answers: " << crntTrial.answers_incorr << " of " << numEquations
         << endl << "  " << " Percentage of Incorrect Answers % " << crntTrial.percent_incor;
    cout << endl
         << endl << "  " << " Number of Correct Answers:  " << crntTrial.answers_correct << " of " << numEquations
         << endl << "  " << " Percentage of Correct answers:  % " << crntTrial.percent_corr;

    for (int crnt = 0; crnt < numEquations; crnt++) 
    {   if (equationInfo[crnt][a.ACCURACY] == "I" || equationInfo[crnt][a.ACCURACY] == "P" )
        {   cout << endl
                 << endl << "  " << equationInfo[crnt][a.EQUATION] << equationInfo[crnt][a.SOLUTION];
            (equationInfo[crnt][a.ACCURACY] == "I") 
              ? cout << endl << "  " << "You answered:  " << equationInfo[crnt][a.STUD_ANS]
              : cout << endl << "  " << "You skipped this question.";
            cin.get();
        }
    }

    cout << endl << endl << "  Press [ENTER] to continue." << endl;
    cin.get();
}


int getInput_timetaken()
{   // DECLAR VARIABLES
    int min = 0;
    int sec = 0; 
    char *fetch = new char[100];
    bool skip = false; 
    bool inpError = false;
    
    do 
    {   // FLAG RESET
        inpError = false; 
        fetch[0] = 'x';
        fetch[1] = 'x';
        fetch[2] = 'x';
        fetch[3] = 'x';
        // DISPLAY - prompt and input
        cout << endl << "  " << "# of minutes: ";
        cin.getline(fetch, 100);
        // VALIDATION - skip option verification
        if (fetch[0] == '\n' || fetch[0] == '\0')   skip = true; 
        if (skip)                                   return -2; 
        else
        {   if (!(fetch[0] >= '0' && fetch[0] <= '9')) 
            {   inpError = true; 
                cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
            }
            else if ((fetch[2] == '\0' || fetch[2] == '\n') && !(fetch[1] >= '0' && fetch[1] <= '9')) 
            {   inpError = true; 
                cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
            }
            else if ((fetch[3] == '\0' || fetch[3] == '\n') && !(fetch[2] >= '0' && fetch[2] <= '9')) 
            {   inpError = true; 
                cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
            }
        }
    }
    while (!skip && inpError);
    // TRANSFER - after validating answers, transfer them into the variables
    min = atoi(fetch);

    do 
    {   // FLAG RESET
        inpError = false; 
        fetch[0] = 'x';
        fetch[1] = 'x';
        fetch[2] = 'x';
        fetch[3] = 'x';
        // DISPLAY - prompt and input
        cout << endl << "  " << "# of seconds: ";
        cin.getline(fetch, 100);
        // VALIDATION - skip option verification
        if (fetch[0] == '\0' || fetch[0] == '\n')
        {   inpError = true;
            cout << endl << "  " << "Input required!";
        }
        else
        {   if (!(fetch[0] >= '0' && fetch[0] <= '9')) 
            {   inpError = true; 
                cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
            }
            else if ((fetch[2] == '\0' || fetch[2] == '\n') && !(fetch[1] >= '0' && fetch[1] <= '9')) 
            {   inpError = true; 
                cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
            }
            else if ((fetch[3] == '\0' || fetch[3] == '\n') && !(fetch[2] >= '0' && fetch[2] <= '9')) 
            {   inpError = true; 
                cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
            }
        }
    }
    while (inpError);
    // TRANSFER - after validating answers, transfer them into the variables
    sec = atoi(fetch);

    return (sec + 60*min);
}

stats getInput_equations(int numEquations, string **equation)
{   stats returnInfo;
    arrElems a; 
    // input variables
    int crntAnswer; 
    int studAnswer;
    char *fetch = new char[100];
    // flags
    bool inpError = false;
    bool skip = false; 

    // PAUSE
    cout << endl << endl << "  " << "...Press [ENTER] to start...";
    cin.get();
    cout << endl << "  " << "Stopwatches start!" << endl;

    for (int crnt = 0; crnt < numEquations; crnt++)
    {   // FLAG RESET
        skip = false; 
        
        do 
        {   // FLAG RESET
            inpError = false; 
            fetch[0] = 'x';
            fetch[1] = 'x';
            fetch[2] = 'x';
            fetch[3] = 'x';
            // DISPLAY - prompt and input
            cout << endl << "  " << equation[crnt][a.EQUATION];
            cin.getline(fetch, 100);
            // VALIDATION - skip option verification
            if (fetch[0] == '\n' || fetch[0] == '\0')
            {   cout << endl << "  " << "Skip Equation? (Press enter to do so. Otherwise, input answer.)"
                     << endl;
                cin.getline(fetch, 100);
                if (fetch[0] == '\n' || fetch[0] == '\0')
                {   skip = true;
                    returnInfo.answers_unansw++;
                    equation[crnt][a.ACCURACY] = "S";
                } 
            }
            // VALIDATION - is answer an acceptable number
            if (!skip)
            {   // Length
                if (fetch[3] != '\0' && fetch[2] != '\0' && fetch[1] != '\0') 
                {   inpError = true; 
                    cout << endl << "  " << "Answer invalid. Please try again.";
                }
                // Input
                else if (!(fetch[0] >= '0' && fetch[0] <= '9')) 
                {   inpError = true; 
                    cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
                }
                else if ((fetch[2] == '\0' || fetch[2] == '\n') && !(fetch[1] >= '0' && fetch[1] <= '9')) 
                {   inpError = true; 
                    cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
                }
                else if ((fetch[3] == '\0' || fetch[3] == '\n') && !(fetch[2] >= '0' && fetch[2] <= '9')) 
                {   inpError = true; 
                    cout << endl << "  " << "Input invalid. Input must consist of numbers only.";
                }
            }
        }
        while (inpError && !skip);
        
        // RESET FLAGS
        crntAnswer = -1; 
        studAnswer = -2; 

        // TRANSFER - moving answers into the array and to the correct data types 
        crntAnswer = stoi(equation[crnt][a.SOLUTION]);
        studAnswer = atoi(fetch);
        equation[crnt][a.STUD_ANS] = to_string(studAnswer);
        
        // PROCESSING - check to see if the student's answer was correct
        if (studAnswer == crntAnswer)
        {   // Answer was correct
            returnInfo.answers_correct++;
            equation[crnt][a.ACCURACY] = "C";
        }
        else
        {   // Answer was incorrect
            returnInfo.answers_incorr++;
            equation[crnt][a.ACCURACY] = "I";
        }

        //
    }


    return returnInfo;
}



void createTrial(int selection, int crnt, string **equationInfo)
{   // ---- variable:  pre-existing array-related constants
    arrElems equ; 
    string buildEqu; 
    // ---- variables: single-use constants determining the pathway
    const int MULTIPLICATION = 1; 
    const int DIVISION = 2; 

    // BUILD - constructing the equation layout
    if (selection == MULTIPLICATION) 
    {   // ---- variables: boundaries
        int MIN = 0;
        int MAX = 10;
        // ---- variables: selection related
        int factor1 = equ.val1 = ((rand() % (MAX-MIN+1)) + MIN);
        int factor2 = equ.val2 = ((rand() % (MAX-MIN+1)) + MIN);
        int product = equ.solution = (factor1 * factor2); 
        // TRANSFER - storing parts within the array 
        equationInfo[crnt][equ.VALUE1] = to_string(factor1) + equ.closeStr;   // Part 1 
        equationInfo[crnt][equ.VALUE2] = to_string(factor2) + equ.closeStr;   // Part 2 
        equationInfo[crnt][equ.SOLUTION] = to_string(product) + equ.closeStr; // Part 3
        // TRANSFER - storing full equation  
        buildEqu = equationInfo[crnt][equ.VALUE1]; 
        buildEqu += equ.times;  
        buildEqu += equationInfo[crnt][equ.VALUE2]; 
        buildEqu += equ.equals; 
        equationInfo[crnt][equ.EQUATION] = buildEqu; 
        return; 
    }
    if (selection == DIVISION) 
    {   // ---- variables: boundaries
        int MIN = 1;
        int MAX0 = 9;
        int MAX_END = 500;
        // ---- variables: selection related
        int divisor = equ.val2 = ((rand() % (MAX0-MIN+1)) + MIN);
        int dividend = equ.val1 = ((((rand() % (MAX_END-divisor+1)) + divisor) / divisor) * divisor); 
        int quotient = equ.solution = (dividend / divisor); 
        // TRANSFER - storing parts within the array 
        equationInfo[crnt][equ.VALUE1] = to_string(dividend) + equ.closeStr;    // Part 1 
        equationInfo[crnt][equ.VALUE2] = to_string(divisor) + equ.closeStr;     // Part 2 
        equationInfo[crnt][equ.SOLUTION] = to_string(quotient) + equ.closeStr;  // Part 3
        // TRANSFER - storing full equation  // ------------------------------
        buildEqu = equationInfo[crnt][equ.VALUE1]; 
        buildEqu += equ.divided_by;  
        buildEqu += equationInfo[crnt][equ.VALUE2]; 
        buildEqu += equ.equals; 
        equationInfo[crnt][equ.EQUATION] = buildEqu; 
        return; 
    }
}



void showMenu(int *inpReturn, int *size, bool *endProg)
{
    bool inpError = false;
    char *fetch = new char[100];

    // DISPLAY MENU  << 1 >>
    cout << endl << "  " << "------------------------------"
         << endl << "  " << "1. Multiplication equations"
         << endl << "  " << "2. Division equations"
         << endl << "  " << "3. Quit this program"
         << endl << "  " << "------------------------------";

    do 
    {   // Flag reset
        *endProg = false; 
        inpError = false; 

        // INPUT
        cout << endl << "  " << "Choice:  ";
        cin.getline(fetch, 100);

        // VALIDATION
        if (fetch[0] == '\0' || fetch[0] == '\n')
        {   inpError = true;
            cout << endl << "  " << "Input required!";
        }
        else if (fetch[1] != '\0' && fetch[1] != '\n')
        {   inpError = true;
            cout << endl << "  " << "Input invalid. Input must be only 1 character long.";
        }
        else if (!(fetch[0] >= '1' && fetch[0] <= '3'))
        {   inpError = true;
            if (fetch[0] == '0' || (fetch[0] >= '4' && fetch[0] <= '9'))
                cout << endl << "  " << "Input invalid. The answer must be \'1\', \'2\', or \'3\'.";
            else
                cout << endl << "  " << "Input invalid. The answer must be an integer.";
        }
        else if (fetch[0] == '3')
        {   *endProg = true;
            cout << endl << "  " << "Program ended -- thank you for using this program!"
                 << endl;
        }
        else    *inpReturn = atoi(fetch); 
        
    }
    while (*endProg != true && inpError);

    if (*endProg == false)
    {   // clear prior entry
        fetch[0] = '0';
        fetch[1] = '0';
        fetch[2] = '0';
        fetch[3] = '0';
        fetch[4] = '0';

        // DISPLAY MENU  << 2 >>
        cout << endl << "  " << "(Press enter to skip. Enter '0' to go to the main menu.)";
        cout << endl << "  " << "Enter the number of cycles.  " << endl;

        //cout << endl << "  " << "-";
        do 
        {   // Flag reset
            *endProg = false; 
            inpError = false;

            // INPUT
            cout << endl << "  " << "Choice:  ";
            cin.getline(fetch, 100);

            // VALIDATION
            if ((fetch[2] != '\0' && fetch[2] != '\n') && (fetch[1] != '\0' && fetch[1] != '\n'))
            {   inpError = true;
                cout << endl << "  " << "Input invalid. Input can only be up to 2 character long.";
            }
            else if (fetch[0] == '0')
                // Success
                *size = 0;
            else if (!(fetch[0] >= '1' && fetch[0] <= '9'))
            {   inpError = true;
                cout << endl << "  " << "Input invalid. The answer must be an integer.";
            }
            else if (fetch[2] == '\0' && !(fetch[1] >= '0' && fetch[1] <= '9'))
            {   inpError = true;
                cout << endl << "  " << "Input invalid. The answer must be an integer.";
            }
            else    *size = atoi(fetch);
        }
        while (inpError);
    }

    delete [] fetch; 
    return; 
}


void displayQuestions(int path, int arrSize, string **equationInfo)
{   arrElems a; 
        
    if (path == 1)
    {   for (int crnt = 0; crnt < arrSize; crnt++)
        {   cout << endl
                 << endl << "  " << "Accuracy:  " << equationInfo[crnt][a.ACCURACY] 
                 << endl << "  " << "Stud_ans:  " << equationInfo[crnt][a.STUD_ANS]
                 << endl << "  " << "Value 1:   " << equationInfo[crnt][a.VALUE1]
                 << endl << "  " << "Value 2:   " << equationInfo[crnt][a.VALUE2]
                 << endl << "  " << equationInfo[crnt][a.EQUATION] << equationInfo[crnt][a.SOLUTION];
            cin.get(); 
        }
    }
}

