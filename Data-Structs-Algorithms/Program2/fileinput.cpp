/*
    This supplemantary function populates the input.txt file with a list of random numbers
    The user inputs how many numbers they want and the largest possible number that the random operator can generate
    The random operator also randomly assigns the number as positive or negative
    This file was not part of the original assignment, but I added it to make it easier to populate the text file
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int input = 0, length = 0, rand1 = 0, rand2 = 0;
    ofstream outputFile;

    srand(time(NULL)); // Helps randomize numbers

    cout << "How many times do you want the program to run?" << endl;
    cin >> input;
    cout << "What is the maximum number you want the function to run to?" << endl;
    cin >> length;

    outputFile.open("input.txt");

    if (!outputFile.is_open())
    {
        cerr << "Error! File cannot be read" << endl;
        return -1;
    }
    else
    {

        for (int i = 0; i < input; i++)
        {
            rand1 = rand() % length + 1; // Used to generate a random number
            rand2 = rand() % 2 + 1;      // Used to randomly assign the number as negative
            if (rand2 == 1)
            {
                rand1 *= -1;
            }
            outputFile << rand1 << endl;
        }
    }
    outputFile.close();

    return 0;
}