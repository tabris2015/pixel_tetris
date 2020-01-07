#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>
#include <vector>
struct Tile 
{
    int w;
    int h;
    std::vector<uint8_t> shape;
    Tile(std::vector<uint8_t> shape):w(4), h(4), shape(shape){};
};
#endif