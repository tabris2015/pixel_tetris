#ifndef TETRIS_H
#define TETRIS_H
#include <assert.h>
#include <stdint.h>
#include <bits/stdc++.h>
#include <vector>

enum Dir
{
    RIGHT,
    LEFT,
    N_DIRS
};


enum Cell
{
    FREE,
    TILE,
    WALL,
    N_CELLS
};


class Board
{
private:
    int w;
    int h;
    std::vector<std::vector<Cell>> state;
public:
    Board(int w, int h):w(w), h(h){};
    
};

struct Tile 
{
    int w;
    int h;
    std::vector<std::string> shape;
    Tile():w(4), h(4){};
    Tile(std::vector<std::string> shape):w(4), h(4), shape(shape)
    {
        assert(shape.size() == 4);
        assert(shape[0].size() == 4);
    };
    void init(std::vector<std::string> n_shape)
    {
        shape = n_shape;
    }
    // funcion que rota la ficha 90 grados en una direccion
    void rotate(Dir dir)
    {
        switch (dir)
        {
        case Dir::RIGHT:
            for (int i = 0; i < w; i += 1) {
                for (int j = i+1; j < w; j += 1) {
                    swap(i,j,j,i);
                }
            }
            // h mirror:
            for (int i = 0; i < w; i++)
            {
                std::reverse(shape[i].begin(), shape[i].end());
            }
            break;
        case Dir::LEFT:
            // left: transpose and vertical mirror
            // mirror:
            for (int i = 0; i < w; i += 1) {
                for (int j = i+1; j < w; j += 1) {
                    swap(i,j,j,i);
                }
            }
            //v mirror
            std::reverse(shape.begin(), shape.end());
            break;
        default:
            break;
        }
    };
    // funcion que verifica si la ficha encaja en la posicion en el tablero
    bool fits(int x, int y, const Board& board)
    {
        return true;
    };
private:
    void swap(int sx, int sy, int dx, int dy)
    {
        char aux = shape[sy][sx];
        shape[sy][sx] = shape[dy][dx];
        shape[dy][dx] = aux;
    };
};



#endif