#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<std::string> items{"apple", "banana", "cherry"};

	do {
		/* print the permutation */
		for(unsigned int ii=0; ii < items.size(); ii++) {
			std::cout << items[ii] << " ";
		}
		std::cout << std::endl;
	} while(std::next_permutation(items.begin(), items.end()));

	return 0;
}
