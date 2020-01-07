#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "tetris.h"
// Override base class with your custom functionality
class TetrisGame : public olc::PixelGameEngine
{
private:
    void DrawTile(int x, int y, Tile tile)
    {
        // para cada fila
        for(int j = 0; j < tile.h; j++)
        {
            for(int i = 0; i < tile.w; i++)
            {
            // para cada fila
                uint8_t fila = tile.shape[j];
                // fila = 0b1000
                // p1 = 0b1000 >> 3 = 1  si
                // m  = 0b0001
                // p2 = 0b1000 >> 2 = 1  si
                if((fila >> (tile.w - i - 1)) & 0b0001)
                {
                    Draw(x + i, y + j);
                }
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
        //        3210  
        Tile l({0b1000, 
                0b1000, 
                0b1000, 
                0b1000});
        Tile z({0b0000, 
                0b0000, 
                0b1100, 
                0b0110});
                
        // limpiar la pantalla de color gris oscuro
        Clear(olc::Pixel(0,0,0));
        // dibujar 4 esquinas
        DrawTile(0,0,l);
        DrawTile(3,0,z);
        
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