#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::ofstream output(argv[1]);

    char c;
    while (std::cin >> c) {
        std::cout << c;
        output << c;
    }
}