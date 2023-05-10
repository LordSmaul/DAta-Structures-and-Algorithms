/*
	Author: Lord Smaul
	File Name: solution.cpp
	Date: 01/28/2023
	Purpose: Recursive solution to the Greatest Common Denominator of two input variables
*/

#include <iostream>
#include <sstream>
#include <math.h>

void calculate_gcd(int m, int n) {
	// Declaring statics for printing later in the function
	static int M = m;
	static int N = n;

	// Using absolute value function to account for any negative numbers
	m = fabs(m);
	n = fabs(n);

	if (n != 0) // a greatest common divisor has yet to be reached
	{
		calculate_gcd(n, m % n);
	}
	else if (n == 0 && m != 0) // a greatest common divisor has been reached
	{
		std::cout << "gcd(" << M << "," << N << ") = " << m << std::endl;
	}
	else // if both n and m are zero, gcd(m, n) is undefined
	{
		std::cout << "gcd(" << M << "," << N << ") is undefined" << std::endl;
	}
}

void usage(char *name) {
	std::cerr << "Calculates the greatest common divisor of two numbers." << std::endl;
	std::cerr << "usage:" << name << " [m] [n]" << std::endl;
	std::cerr << "m,n integers, not both " << std::endl;
}

int main(int argc, char *argv[]) {
	int m = 0;
	int n = 0;

	if(argc != 3) {
		std::cerr << "Invalid number of arguments." << std::endl << std::endl;
		usage(argv[0]);

		return 0;
	}

	std::istringstream iss(argv[1]);
	if((iss>>m).fail() || !iss.eof()) {
		std::cerr << argv[1] << " is not a valid integer." << std::endl << std::endl;
		usage(argv[0]);

		return 0;
	}

	iss.str(argv[2]);
	iss.clear();
	if((iss>>n).fail() || !iss.eof()) {
		std::cerr << argv[2] << " is not a valid integer." << std::endl << std::endl;
		usage(argv[0]);

		return 0;
	}

	calculate_gcd(m, n);

	return 0;
}
