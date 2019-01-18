#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	int rows, columns;
	std::cout << "Specify rows, columns:";
	std::cin >> rows >> columns;
	int wow[rows][columns];
	for (int i=0; i< rows; ++i) {
		for (int j=0; j<columns; ++j) {
			wow[i][j] = 0;
			std::cout << wow[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	return 0;
}