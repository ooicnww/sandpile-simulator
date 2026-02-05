#ifndef HEAP_H
#define HEAP_H

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

struct Heap {
    int N;
    int M;
    int** heap;

    Heap(int width=10, int height=10) : N(width), M(height) {
        heap = new int*[N];
        for (int i = 0; i < N; ++i) {
            heap[i] = new int[M]{0};
        }
    }


    void resize(int new_N, int new_M) {
        new_N = new_N + (4 - (new_N% 4));
        new_M = new_M + (4 - (new_M % 4));
        int** new_heap = new int*[new_N];
        for (int i = 0; i < new_N; ++i) {
            new_heap[i] = new int[new_M]{0};
        }

        int delta_N = (new_N - N) / 2;
        int delta_M = (new_M - M) / 2;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                new_heap[i + delta_N][j + delta_M] = heap[i][j];
            }
        }
        for (int i = 0; i < N; ++i) {
            delete[] heap[i];
        }
        delete[] heap;
        heap = new_heap;
        N = new_N;
        M = new_M;
    }
    void collapse() {
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < M; ++y) {
                if (heap[x][y] >= 4) {
                    if (x == N-1 || y == M-1) {
                        resize((int)N*1.2, (int)M*1.2);
                    }
                    int ost = heap[x][y] / 4;
                    heap[x][y] -= 4 * ost;
                    if (x + 1 < N) {
                        heap[x + 1][y] += ost;
                    }
                    if (x - 1 >= 0) heap[x - 1][y] += ost;
                    if (y + 1 < M) heap[x][y + 1] += ost;
                    if (y - 1 >= 0) heap[x][y - 1] += ost;
                }
            }
        }
    }

    void print_heap() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                std::cout << heap[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

struct Program {
    std::string input_file;
    std::string output_file = "output";
    int max_iter;
    int freq;
    Heap matr;
    Program() : input_file(""), output_file(""), max_iter(100), freq(0), matr() {}
};


void create_program(Program& program);

#endif

//N - width, x
//M - height, y