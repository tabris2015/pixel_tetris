#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include "tetris.h"
// Override base class with your custom functionality
class TetrisGame : public olc::PixelGameEngine
{
public:
    TetrisGame()
    {
        sAppName = "TetrisGame";
    }

private:
    Tile z;
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
    bool OnUserCreate() override
    {
        z.init({"0x00",
                "0xx0",
                "00x0",
                "0000"});
        // limpiar la pantalla de color gris oscuro
        Clear(olc::Pixel(0,0,0));
        // dibujar 4 esquinas

        DrawTile(3,8,z);
        
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        if(GetKey(olc::Key::UP).bPressed)
        {
           z.rotate(Dir::LEFT);
           Clear(olc::BLACK);
           DrawTile(3,8,z);
        }

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