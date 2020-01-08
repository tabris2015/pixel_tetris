#ifndef TETRIS_H
#define TETRIS_H
#include <assert.h>
#include <stdint.h>

#include <vector>

enum Dir{
    LEFT,
    RIGHT
};

class Board
{
private:
    /* data */
public:
    Board(/* args */);
    ~Board();
};

struct Tile 
{
    int w;
    int h;
    std::vector<std::string> shape;
    Tile(std::vector<std::string> shape):w(4), h(4), shape(shape)
    {
        assert(shape.size() == 4);
        assert(shape[0].size() == 4);
    };
    // funcion que rota la ficha 90 grados en una direccion
    void rotate(Dir dir)
    {
        // left: transpose and mirror
        for (int n = 0; n < w - 2; n++)
            for (int m = n + 1; m < h - 1; m++)
                swap(n,m,m,n);
        // right: mirror and transpose
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