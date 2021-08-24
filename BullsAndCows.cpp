#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

bool validInput(string userInput)
{
    int inputLength = userInput.length();
    bool isNumber;

    for(int i = 0;i < inputLength; i++)
    {
        if(isdigit(userInput[i]) && userInput[i] != '0')
            isNumber = true;
        else
        {
            isNumber = false;
            break;
        }
    }

    if(userInput == "i")
    {
        return true;
    }
    else if(isNumber && (userInput.length() == 4))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool repeatCheck(string userInput)
{
    int inputLength = userInput.length();

    for(int i = 0; i < inputLength; i++)
    {
        for(int e = 0; e < inputLength; e++)
        {
            if(userInput.at(i) == userInput.at(e) && i != e)
                return true;
        }
    }

    return false;
}

string answerGen()
{
    int digits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int randomNum = 0;
    vector<int> toShuffle(digits, digits + 9);
    string answer = "";
    stringstream convert;

    srand(time(0));
    random_shuffle(toShuffle.begin(), toShuffle.end());

    for(int i = 0; i < 4; i++)
    {
        randomNum *= 10;
        randomNum += toShuffle[i];
    }

    convert << randomNum;
    answer = convert.str();

    return answer;
}

int bullsCheck(string userInput, string answer)
{
    int inputLength = userInput.length();
    int bulls = 0;

    for(int i = 0; i < inputLength; i++)
    {
        if(userInput[i] == answer[i])
            bulls++;
    }

    return bulls;
}

int cowsCheck(string userInput, string answer)
{
    int inputLength = userInput.length();
    int cows = 0;
    int bulls = bullsCheck(userInput, answer);

    for(int i = 0; i < inputLength; i++)
    {
        for(int e = 0; e < inputLength; e++)
        {
            if(userInput.at(i) == answer.at(e))
                cows++;
        }
    }

    cows -= bulls;

    return cows;
}

int main()
{
    string userInput;
    string answer = answerGen();
    int bulls = 0;
    int cows = 0;

    cout << "Welcome to Bulls and Cows. Enter 'i' for instructions or begin "
            "guessing now." << endl;

    for(int i = 1; i <= 10; i++)
    {
        cout << "Guess: ";
        cin >> userInput;
        if(!(validInput(userInput)) && userInput != "i")
        {
            cout << "Try again. Your input must be a four digit number "
                    "with no zeros." << endl;
            i--;
        }
        else if(validInput(userInput) && userInput == "i")
        {
            cout << "Bulls and Cows is a logic game. The goal is to find the "
                    "randomly generated order of four unique non-zero numbers in "
                    "ten guesses. Based on your input, you will be given Bulls or "
                    "Cows. A Bull means you have the correct number in the "
                    "correct order. A Cow means you have the correct number in "
                    "the wrong place. Four bulls is a win. Good luck!" << endl;
            i--;
        }
        else if(validInput(userInput) && repeatCheck(userInput))
        {
            cout << "Try again. Your input should not have repeats." << endl;
            i--;
        }
        else
        {
            bulls = bullsCheck(userInput, answer);
            cows = cowsCheck(userInput, answer);
            cout << "You have " << bulls << " bulls and " << cows << " cows." << endl;
            if(bulls == 4)
                break;
            else
            {
                switch(i)
                {
                case 10:
                    cout << "Game Over. The answer was " << answer << ". ";
                default:
                    cout << "You have used " << i << " attempts." << endl;
                    break;
                }
            }

        }

    }
    if(bulls == 4)
        cout << "Congratulations! You have guessed the number.";

    return 0;
}

