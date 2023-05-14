/*
    Author: Lord Smaul
    File Name: solution.cpp
    Date: 03/25/2023
    Purpose: Recursive decrease-and-conquer approach to finding 
    the maximum element in a vector with items read from a file.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>

int maxNum(std::vector<int> arr, int len)
{
    if (len == 1) // Base Case: if only one element remains in the list
    {
        return arr[0];
    }
    // Recursively shortens the scope of the max check, 
    return std::max(arr[len - 1], maxNum(arr, len - 1));
}


int main(int argc, char *argv[])
{
    std::vector<int> numbers;                       // vector for reading integers
    std::ifstream inputFile(argv[1], std::ios::in); // ifstream used for reading file input
    std::string line;                               // for reading integers into the vector from the file

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
            inputFile >> line;
            int num = stoi(line);
            numbers.push_back(num);
        }
    }
    else // Error message if file is not found
    {
        std::cerr << "Unable to open the file." << std::endl;
        return 0;
    }

    // Prints max element
    std::cout << maxNum(numbers, numbers.size()) << std::endl;

    return 0;
}
