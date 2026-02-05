#ifndef BMP_H
#define BMP_H

#include <fstream>
#include <cstdint>
#include "heap.h"
#include "bmp_writer.h"
#include <filesystem>

unsigned char get_pixel_color(int value) {
    if (value == 0) return 0;
    if (value == 1) return 1;
    if (value == 2) return 2;
    if (value == 3) return 3;
    return 4;
}

void write_bmp(const std::string& direct, Heap& heap, int index) {
    int width = heap.N;
    int height = heap.M;

    std::filesystem::create_directory(direct);

    std::filesystem::path fullPath = std::filesystem::path(direct) / ("output" + std::to_string(index) + ".bmp");

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    infoHeader.width = width;
    infoHeader.height = height;

    int padding = (4 - (((width + 1) / 2) % 4)) % 4;
    infoHeader.sizeImage = ((width + 1) / 2 + padding) * height;
    fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + 5 * sizeof(uint32_t) + infoHeader.sizeImage;
    fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + 5 * sizeof(uint32_t);

    uint32_t palette[] = {0x00FFFFFF, 0x0000FF00, 0x00FF00FF, 0x00FFFF00, 0x00000000};

    std::ofstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("couldn`t open output file: " + fullPath.string());
    }

    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    for (int j = 0; j < 5; ++j) {
        file.write(reinterpret_cast<char*>(&palette[j]), sizeof(palette[j]));
    }

    uint8_t byte = 0;
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; x += 2) {
            uint8_t pixel1 = get_pixel_color(heap.heap[y][x]);
            uint8_t pixel2 = 0;

            if (x + 1 < width) {
                pixel2 = get_pixel_color(heap.heap[y][x + 1]);
            }

            byte = (pixel1 << 4) | pixel2;
            file.write(reinterpret_cast<char*>(&byte), sizeof(byte));
        }

        for (int p = 0; p < padding; ++p) {
            file.put(0);
        }
    }
    file.close();
}

#endif
