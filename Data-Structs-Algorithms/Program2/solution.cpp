/*
    Author: Lord Smaul
    File Name: solution.cpp
    Date: 02/25/2023
    Purpose: Brute-force approach to finding the maximum element in a vector with items from a file.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>

int main(int argc, char *argv[])
{
    std::vector<int> numbers;                       // vector for reading integers
    std::ifstream inputFile(argv[1], std::ios::in); // ifstream used for reading file input
    int max = 0;                                    // Usd to find the max number
    std::string line;                               // for reading integers into the vector from the file
    bool check = true;

    // If incorrect number of arguments is passed
    if (argc != 2)
    {
        std::cerr << "Error! Too few or too many arguments." << std::endl;
        return 0;
    }

    // Checks if file is open, prints error message if file is not found
    if (inputFile.is_open())
    {
        // Reads in input while end of file has not been reached
        while (!inputFile.eof())
        {
            check = true;
            inputFile >> line;
            for (int i = 0; i < int(line.length()); i++)
            {
                if (!isdigit(line[i]))
                {
                    check = false;
                    break;
                }
            }

            if (!check)
            {
                continue;
            }
            else
            {
                int num = stoi(line);
                numbers.push_back(num);
            }
        }
    }
    else // Error message if file is not found
    {
        std::cerr << "Unable to open the file." << std::endl;
        return 0;
    }

    // Implements brute force search of every element in the array to find max element in the array
    for (int i = 0; i < int(numbers.size()); i++)
    {
        if (numbers[i] >= max)
        {
            max = numbers[i];
        }
    }

    // Prints max element
    std::cout << max << std::endl;

    return 0;
}