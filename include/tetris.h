#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>

enum Dir
{
    RIGHT,
    LEFT,
    N_DIRS
};

struct Tile 
{
    int w;
    int h;
    std::vector<std::string> shape;
    olc::Pixel color;
    Tile():w(4), h(4), color(olc::RED){};
    Tile(std::vector<std::string> shape, olc::Pixel c) : w(4), h(4), shape(shape), color(c) 
    {};
    void init(std::vector<std::string> n_shape, olc::Pixel c)
    {
        shape = n_shape;
        color = c;
    }
    // rotar la ficha 90 grados a la izq o a la derecha
    void rotate(Dir dir)
    {
        switch (dir)
        {
        case Dir::RIGHT:
            // traspuesta
            for (int i = 0; i < w; i += 1) {
                for (int j = i+1; j < h; j += 1) {
                    swap(i,j,j,i);
                }
            }
            // reversa horizontal (columnas)
            for(int fila = 0; fila < h; fila++)
                std::reverse(shape[fila].begin(), shape[fila].end());
            break;
        case Dir::LEFT:
            // traspuesta
            for (int i = 0; i < w; i += 1) {
                for (int j = i+1; j < h; j += 1) {
                    swap(i,j,j,i);
                }
            }
            // reversa vertical (filas)
            std::reverse(shape.begin(), shape.end());
            break;
        default:
            break;
        }
    }
    // verificar si la ficha encaja en la posicion dada
    bool doesFit(){};
private:
    void swap(int sx, int sy, int dx, int dy)
    {
        char aux = shape[sy][sx];
        shape[sy][sx] = shape[dy][dx];
        shape[dy][dx] = aux;
    };
};
#endif