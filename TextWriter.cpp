// Copyright 2023 (Clyde Shtino)
#include <fstream>
#include <sstream>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    // argc check
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " order_k length_L < input_file" << std::endl;
        return 1;
    }
    // for user input
    int k = std::stoi(argv[1]);
    int L = std::stoi(argv[2]);
    std::string input(std::istreambuf_iterator<char>(std::cin), {});

    // creating object
    RandWriter writer(input, k);

    // generating new string
    string temp;
    for (int i = 0; i < k; i++) {
        temp.push_back(input[i]);
    }
    // in case of exception issue
    try {
        std::cout << writer.generate(temp, L) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
