#include "heap.h"
#include "bmp_writer.h"

int main(int argc, char* argv[]) {
    Program program;
    std::string input_file;
    std::string output_file;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-i" || arg == "--input") && i + 1 < argc) {
            program.input_file = argv[++i];
        }
        else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
            program.output_file = argv[++i];
        }
        else if ((arg == "-m" || arg == "--max-iter") && i + 1 < argc) {
            program.max_iter = std::stoi(argv[++i]);
        }
        else if ((arg == "-f" || arg == "--freq") && i + 1 < argc) {
            program.freq = std::stoi(argv[++i]);
        }
    }
    create_program(program);
    int iter = 0;
    while (iter < program.max_iter) {
        program.matr.collapse();
        if (program.freq != 0) {
            if (iter % program.freq == 0) {
                write_bmp(program.output_file, program.matr, iter+1);
            }
        }
        iter++;
    }
    write_bmp(program.output_file, program.matr, 0);
}