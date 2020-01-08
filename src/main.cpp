#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include "tetris.h"
// Override base class with your custom functionality
class TetrisGame : public olc::PixelGameEngine
{
private:
    void DrawTile(int x, int y, Tile tile)
    {
        int count = 0;
        // para cada fila
        for(int fila = 0; fila < tile.h; fila++)
        {
            // para cada columna
            for(int col = 0; col < tile.w; col++)
            {
                if(tile.shape[fila][col] == 'x')
                    Draw(x + col, y + fila);
            }
        }
    }
public:
    TetrisGame()
    {
        sAppName = "TetrisGame";
    }

public:
    bool OnUserCreate() override
    {
         
        Tile z({"0000",
                "xx00",
                "0xx0",
                "0000"});
                
        // limpiar la pantalla de color gris oscuro
        Clear(olc::Pixel(0,0,0));
        // dibujar 4 esquinas

        DrawTile(0,0,z);
        z.rotate(Dir::LEFT);
        DrawTile(0,4,z);
        
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        return true;
    }
};
int main()
{
    TetrisGame demo;
    if (demo.Construct(10, 20, 38, 38))
        demo.Start();
    return 0;
}