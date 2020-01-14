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
    int time;
    void DrawTile(Tile tile)
    {
        for(int fila = 0; fila < tile.h; fila++)
        {
            for(int col = 0; col < tile.w; col++)
            {
                if(tile.shape[fila][col] == 'x')
                    Draw(col + tile.x, fila + tile.y, tile.color);
            }
        }
    }

public:
    TetrisGame()
    {
        sAppName = "TetrisGame";
    }
    bool OnUserCreate() override
    {
        //        3210  
        f.init({"0000",
                "0x00",
                "0x00",
                "0xx0"}, olc::RED);   

        board.init(ScreenWidth(), ScreenHeight());

        // limpiar la pantalla de color gris oscuro
        Clear(olc::Pixel(0,0,0));
        time = 0;
        return true;
    }
    // game loop
    bool OnUserUpdate(float fElapsedTime) override
    {

        // temporizacion
        std::this_thread::sleep_for(50ms);
        // actualizar el estado
        // -- atender eventos (teclado, mouse, otros)
        if(GetKey(olc::Key::UP).bPressed)
            f.rotate(Dir::RIGHT);

        if(GetKey(olc::Key::RIGHT).bPressed)
        {
            if(board.doesTileFit(f.x + 1, f.y, f))
            {
                f.x++;
            }
        }
        else if(GetKey(olc::Key::LEFT).bPressed)
        {
            if(board.doesTileFit(f.x - 1, f.y, f))
            {
                f.x--;
            }
        }
        else if(GetKey(olc::Key::DOWN).bPressed)
        {
            if(board.doesTileFit(f.x, f.y + 1, f))
            {
                f.y++;
            }
        }

        if(!(time % 20))
        {
            if(board.doesTileFit(f.x, f.y + 1, f))
            {
                f.y++;
            }
        }
        // dibujar el estado
        Clear(olc::BLACK);
        DrawTile(f);
        time++;
        // std::cout << time << std::endl;
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