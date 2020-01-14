#define OLC_PGE_APPLICATION
#include <chrono>
#include "olcPixelGameEngine.h"
#include "tetris.h"

using namespace std::chrono_literals;
// Override base class with your custom functionality
class TetrisGame : public olc::PixelGameEngine
{
private:
    bool pixel = false;
    Tile f;
    Board board;
    int time = 0;

    void DrawTile(Tile tile)
    {
        for(int fila = 0; fila < tile.h; fila++)
        {
            for(int col = 0; col < tile.w; col++)
            {
                if((tile.shape[fila][col] == 'x') && validPixelPos(col + tile.x, fila + tile.y))
                    Draw(col + tile.x, fila + tile.y, tile.color);
            }
        }
    }
    bool validPixelPos(int x, int y)
    {
        // std::cout << x << "," << y << std::endl;
        if(x >= ScreenWidth() || x < 0 || y >= ScreenHeight() || y < 0)
            return false;

        return true;
    };

public:
    TetrisGame()
    {
        sAppName = "TetrisGame";
    }
    bool OnUserCreate() override
    {
         
        board.init(10, 20);
        f.init({"0x00",
                "0x00",
                "0xx0",
                "0000"}, olc::YELLOW);   
 
        // limpiar la pantalla de color gris oscuro
        Clear(olc::Pixel(0,0,0));
        return true;
    }
    // game loop
    bool OnUserUpdate(float fElapsedTime) override
    {
        // temporizacion
        std::this_thread::sleep_for(100ms);
        // actualizar el estado
        // -- atender eventos (teclado, mouse, otros)
        if(GetKey(olc::Key::UP).bPressed)
        {
            f.rotate(Dir::RIGHT);
        }
        if(GetKey(olc::Key::LEFT).bHeld)
        {
            // mover a la izquierda
            if(board.doesTileFit(f.x - 1, f.y, f))
            {
                f.x--;
            }
        }
        if(GetKey(olc::Key::RIGHT).bHeld)
        {
            // mover a la derecha
            if(board.doesTileFit(f.x + 1, f.y, f))
            {
                f.x++;
            }
        }
        if ((time % 10 == 0) || (GetKey(olc::Key::DOWN).bHeld))
        {
            // mover abajo
            auto fits = board.doesTileFit(f.x, f.y + 1, f);
            if (fits)
            {
                f.y++;
            }
        }

        // dibujar el estado
        Clear(olc::BLACK);
        // std::cout << "step" << std::endl;
        DrawTile(f);
        // std::cout << "step fin" << std::endl;
        time++;
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