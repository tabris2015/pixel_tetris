#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "tetris.h"
// Override base class with your custom functionality
class TetrisGame : public olc::PixelGameEngine
{
private:
    bool pixel = false;
    Tile f;

    void DrawTile(int x, int y, Tile tile)
    {
        for(int fila = 0; fila < tile.h; fila++)
        {
            for(int col = 0; col < tile.w; col++)
            {
                if(tile.shape[fila][col] == 'x')
                    Draw(col + x, fila + y, tile.color);
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
        f.init({"0000",
                "0x00",
                "0x00",
                "0xx0"}, olc::YELLOW);   

        Tile g({"0000",
                "0x00",
                "0x00",
                "0xx0"}, olc::BLUE);  
        // limpiar la pantalla de color gris oscuro
        Clear(olc::Pixel(0,0,0));
        // dibujar 4 esquinas
        DrawTile(0,0,f);

        DrawTile(4,0,g);

        return true;
    }
    // game loop
    bool OnUserUpdate(float fElapsedTime) override
    {

        // temporizacion
        // actualizar el estado
        // -- atender eventos (teclado, mouse, otros)
        if(GetKey(olc::Key::UP).bPressed)
            f.rotate(Dir::RIGHT);

        // dibujar el estado
        // Clear(olc::BLACK);
        DrawTile(4, 9, f);
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