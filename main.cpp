/* This game was finished by Chase Brock on May 4th, 2021. This program will generate
two random numbers, and either mutliply, divide, subtract, or add them together. It will
prompt the user with the two numbers, and the user must enter the correct answer. If a correct answer
is entered, points are added to the score, and the game continues. If not, the game ends, and a function will
check to see if the current score is the highest recorded and if so, replace the current number in highscores.txt
with the new, highest score. The player can choose to play the game, view the current high score, or quit the game
from the main menu.*/

#include <iostream> 
#include <ctime>   // to make a 'seed' to make random numbers different on each execution
#include <cstdlib> // to use rand();
#include <string> // to use strings
#include <fstream> // to read/write files

using namespace std;

void mainMenu(); // the main menu the player will interact with

void playGame(); // holds the main game function, calls all functions

int numGen(int diff); // generates 2 numbers and operates them together

void addHighScore(int score); // adds a new high score, if necassary

void seeHighScore(); // allows the player to view the current highest score

void mainMenu() // main menu for game; wll present user with options for the game
{
    int choice; // holds the user's choice 
    cout << "\nPlease select an option: \n1. Play Game. \n2. View High Score. \n3. Quit Game" << endl;
    cin >> choice;
    if(choice == 1)
    {
        // play game
        cout << "\nStarting Game..." << endl;
        cin.clear(); // clears input log
        cin.ignore(); // ignores dead space in input log
        playGame(); // launch game
    } 
    else if (choice == 2)
    {
        // show high score
        cin.clear();
        cin.ignore();
        seeHighScore();
        mainMenu(); // go back to menu
    }
    else if (choice == 3)
    {
        // quit game
        cout << "Thanks for Playing!" << endl;
        cin.clear(); // these clear the choice
        cin.ignore();
    }
    else 
    {
        cout << "Invalid Option.";
        cin.clear(); // these two clear the input logs
        cin.ignore();
        mainMenu();
    }   
}

void playGame() // this is where the game is played, score is kept, and difficulty set
{
    int answer; // holds the correct answer
    int userAnswer; // holds the user's answer
    int score = 1; // initialize the player's score
    int difficulty = 10; // calculates difficluty; gets harder as game progresses
    bool isCorrect = true; // a flag to check if answer was correct

    while(isCorrect)
    {
        answer = numGen(difficulty); // get a new question
        cin >> userAnswer; // get a new answer

        if (answer == userAnswer)
        {
            score += 9 * difficulty;
            difficulty += 5;
            cout << "\nCorrect! Score = " << score << ", difficulty = " << difficulty << endl << endl;
        } else 
        {
            cout << "Incorrect! Correct answer was: " << answer << endl;
            cout << "******************************************************" << endl;
            cout << "*** Your Score: " << score << " point(s). Thanks for Playing! ***" << endl;
            cout << "******************************************************" << endl;
            seeHighScore();
            addHighScore(score);
            isCorrect = false;
        }
        
    }
    
    mainMenu(); // go back to main menu
}

int numGen(int diff)
{
    int difficulty = diff;
    srand((unsigned) time(0)); // set a 'seed' to make numbers always random    
    int randomNum1 = rand() % difficulty; // make a random number
    int randomNum2 = rand() % difficulty; // make another random number
    int finalNum; // holds the answer that the user must guess

    int choice = (rand() % 4) + 1; // choose a random num from 1-4 to decide what operator to use
    if (choice == 1) // multiply
    {
        finalNum = randomNum1 * (randomNum2 / 2);
        cout << "What is " << randomNum1 << " times " << (randomNum2 / 2) << "?" << endl;
    } else if (choice == 2) // divide
    {
        finalNum = randomNum1 / (randomNum2 / 2);
        cout << "What is " << randomNum1 << " divided by " << (randomNum2 / 2) << "?" << endl;
    } else if (choice == 3) // add
    {
        finalNum = randomNum1 + randomNum2;
        cout << "What is " << randomNum1 << " plus " << randomNum2 << "?" << endl;
    } else if (choice ==4) // subtract
    {
        finalNum = randomNum1 - randomNum2;
        cout << "What is " << randomNum1 << " minus " << randomNum2 << "?" << endl;
    }
    
    return finalNum; // return the asnwer
}

void addHighScore(int score)
{
    int line; // holds the 'current' number in the while loop
    int highScore = score; // holds the last score of the player
    
    /* Create/Read file to hold high scores */
    ifstream inFile; // create file object
    inFile.open("highscores.txt"); // open highscores.txt

    int temp = 0; // make a temporary variable to find if the current
                  // score was higher than any score in highscores.txt

    if (inFile.fail()) // if the file doesn't exist, give a proper error
    {
        inFile.close();
    } else 
    {
        while(!inFile.eof()) // while there are still things left to read in file
        {
            inFile >> line; // go to next line
            if (line > temp) // if the current line is greater than the temp variable
            {
                temp = line; // it becomes the new temp
            }
        }

    inFile.close(); // close the file object
    }
    
    if (highScore > temp) // if the highscore is greater than the biggest score in the file
    {
        cout << "New Record! High Score Saved!" << endl; 
        ofstream outFile; // create new file object
        outFile.open("highscores.txt"); // open the highscores.txt
        outFile << highScore; // write the highscore to the file
        outFile.close(); // close the file object
    }
}

void seeHighScore() // view high score from highscores.txt
{
    int line; // to hold the current number and display it.

    ifstream inFile; // create file object
    inFile.open("highscores.txt"); // open highscores.txt

    if (inFile.fail()) // if the file doesn't exist, give a proper error
    {
        cerr << "highscores.exe does not exist." << endl;
        exit(1);
    }
    
    while(!inFile.eof()) // while there are still things left to read in file
    {
        inFile >> line; // go to next line
        cout << "The current High Score is: " << line << " Points." << endl;
    }

    inFile.close(); // close the file object
}

int main()
{
    cout << "\nWelcome to the Math Game by Chase Brock! The rules are simple: " << endl;
    cout << "Enter your answer and press Enter. Helpful tip: In the division section, only enter " << endl;
    cout << "How many times the number is wholly divisible. For example, the answer to 20 / 8 is '2', and " << endl;
    cout << "10 / 15 is '0'." << endl;
    
    mainMenu();
    return 0;
}