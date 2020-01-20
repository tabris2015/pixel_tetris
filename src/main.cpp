#define OLC_PGE_APPLICATION
#include <chrono>
#include <stdlib.h>     // rand()
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
    int score = 0;
    int interval = 20;
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

    void DrawBoard(Board board)
    {
        for(int fila = 0; fila < board.h; fila++)
        {
            for(int col = 0; col < board.w; col++)
            {
                if(board.state[fila][col] == 't')
                    Draw(col, fila, olc::DARK_GREY);
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
        // inicializar ficha aleatoria 
        f.init(TILES[rand() % (N_TILES - 1)], olc::Pixel(rand() % 255, rand() % 255, rand() % 255));   

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

        if(!(time % interval))
        {
            std::cout << "score: " << score << std::endl;
            if(board.isTileBottom(f)) 
            {
                // insertar ficha en el estado del tablero
                board.insertTile(f);
                score++;
                // debug print
                // board.printState();
                f.init(TILES[rand() % (N_TILES - 1)], olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
                f.x = rand() % (ScreenWidth() - 4);
                f.y = 0;
            }
            if(board.doesTileFit(f.x, f.y + 1, f))
            {
                f.y++;
            }
        }

        if(score > 30) interval = 18;
        if(score > 50) interval = 15;
        if(score > 80) interval = 10;
        if(score > 100) interval = 5;
        
        score += board.updateTetris() * 10;
        // dibujar el estado
        Clear(olc::BLACK);
        DrawBoard(board);
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