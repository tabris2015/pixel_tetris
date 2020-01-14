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
    // dimensiones
    int w;      //ancho
    int h;      //alto
    // posicion
    int x;
    int y;

    std::vector<std::string> shape;
    olc::Pixel color;
    Tile()
    :w(4), 
    h(4), 
    x(0), 
    y(0), 
    color(olc::RED)
    {};
    Tile(std::vector<std::string> shape, olc::Pixel c) 
    :w(4), 
    h(4), 
    x(0),
    y(0),
    shape(shape), 
    color(c) 
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

private:
    void swap(int sx, int sy, int dx, int dy)
    {
        char aux = shape[sy][sx];
        shape[sy][sx] = shape[dy][dx];
        shape[dy][dx] = aux;
    };
};

class Board
{
private:
    int w;
    int h;
    // estado del tablero
    std::vector<std::vector<char>> state;
public:
    Board(){};
    Board(int width, int height): w(width), h(height)
    {
        // inicializar el estado 
        std::vector<char> row(w,'0');
        for(int i = 0; i < h; i++)
            state.push_back(row);
    };

    void init(int width, int height, char c='0')
    {
        w = width;
        h = height;

        state.clear();
        std::vector<char> row(w,c);
        for(int i = 0; i < h; i++)
            state.push_back(row);
    };

    bool doesTileFit(int x, int y, Tile& tile)
    {
        for(int fila = 0; fila < tile.h; fila++)
        {
            for(int col = 0; col < tile.w; col++)
            {
                if(tile.shape[fila][col] == 'x' && (y + fila) > (h - 1))
                {
                    return false;
                }
                if(tile.shape[fila][col] == 'x' && (state[y + fila][x + col] != '0'))
                {
                    return false;
                }
                
            }
        }
        return true;
    };
};

#endif