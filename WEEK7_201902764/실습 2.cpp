#include <iostream>

bool funcA() {
	int c;
	std::cout << "input(number) : ";
	std::cin >> c;
	if (c < 10) {
		throw std::out_of_range("Invalid Input!!");
	}
	return true;
}

int main() {
	try {
		funcA();
	}
	catch (std::exception& e) {
		std::cout << "Exception : " << e.what() << std::endl;
	}
	return 0;
}