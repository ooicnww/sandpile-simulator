#include <string>
#include <sstream>
#include "heap.h"
#include <fstream>
#include <algorithm>

void create_program(Program &program) {
    std::ifstream file(program.input_file);
    if (!file.is_open()) {
        std::cerr << "Error with opening file: " << program.input_file << std::endl;
        return;
    }

    std::string line;
    int height = 0, width = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string x, y, value;
        if (iss >> x >> y >> value) {
            height = std::max(std::stoi(y) + 1, height);
            width = std::max(std::stoi(x) + 1, width);
        }
    }

    program.matr.N = width + (4 - (width % 4));
    program.matr.M = height + (4 - (height % 4));

    file.clear();
    file.seekg(0);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string x, y, value;
        if (iss >> x >> y >> value) {
            int xi = std::stoi(x);
            int yi = std::stoi(y);
            int val = std::stoi(value);
            program.matr.heap[xi][yi] = val;
        }
    }
    file.close();
}