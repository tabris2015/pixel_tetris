#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#define N_TILES 7

enum Dir
{
    RIGHT,
    LEFT,
    N_DIRS
};

// fichas del juego
std::vector<std::string> TILES[N_TILES] = {
                {"0000",
                 "0x00",
                 "0x00",
                 "0xx0"},
                {"0000",
                 "0x00",
                 "0x00",
                 "xx00"},
                {"0000",
                 "0000",
                 "xx00",
                 "0xx0"},
                {"0000",
                 "0000",
                 "00xx",
                 "0xx0"},
                {"0000",
                 "0000",
                 "0x00",
                 "xxx0"},
                {"0x00",
                 "0x00",
                 "0x00",
                 "0x00"},
                {"0000",
                 "0000",
                 "0xx0",
                 "0xx0"}
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
public:
    int w;
    int h;
    // estado del tablero
    std::vector<std::vector<char>> state;
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

    bool isTileBottom(Tile& tile)
    {
        for(int fila = 0; fila < tile.h; fila++)
        {
            for(int col = 0; col < tile.w; col++)
            {
                if((tile.y + fila) >= h) return true;
                if(tile.shape[fila][col] == 'x' && (tile.y + fila) == (h - 1)) return true;
                if(tile.shape[fila][col] == 'x' && state[tile.y + fila + 1][tile.x + col] != '0') return true;
            }
        }
        return false;
    };

    void insertTile(Tile& tile)
    {
        for(int fila = 0; fila < tile.h; fila++)
        {
            for(int col = 0; col < tile.w; col++)
            {
                if(tile.shape[fila][col] == 'x' && (tile.y + fila) > (h - 1)) continue;
                if(tile.shape[fila][col] == 'x' && (state[tile.y +fila][tile.x + col] == '0'))
                {
                    state[tile.y +fila][tile.x + col] = 't';
                }

            }
        }
    };

    void printState()
    {
        std::cout << "------------" << std::endl;
        for(auto& fila: state)
        {
            std::cout << '|';
            for(auto& c: fila)
                std::cout << c;
            std::cout << '|' << std::endl;
        }
        std::cout << "------------" << std::endl;
    };

    int updateTetris()
    {
        int rows = 0;
        // TODO: convertir el tablero a un std::vector<std::string>>
        for(int fila = (h - 1); fila >= 0; fila--)
        {
            std::string s(state[fila].begin(), state[fila].end());

            if(s == "tttttttttt")
            {
                // quito la fila completa
                state.erase(state.begin() + fila);
                std::vector<char> r(w, '0');
                state.insert(state.begin(), r);
                rows++;
            }
        }

        return rows;
    };

    bool isGameOver()
    {
        // verifico la primera fila
        for(auto& c: state[0])
        {
            if(c != '0')
                return true;
        }
        return false;
    };
};

#endif