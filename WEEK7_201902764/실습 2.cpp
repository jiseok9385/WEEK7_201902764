#include <iostream>

bool funcA() {
	int c;
	std::cout << "input(number) : ";
	std::cin >> c;
	if (c < 10) {
		return false;
	}
	return true;
}

int main() {
	if(funcA()) {}
	else {
		std::cout << "Exception : Invalid Input!!" << std::endl;
	}
	return 0;
}