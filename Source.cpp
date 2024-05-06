#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include "block.h"
#include <string>
using namespace std;
enum gameState {
   menu, 
   instruct,
   gameplay,
   Hard,
   Audio
};
double lastUpdateTime = 0;
double zz;
double z = 0.4;
double k = 0.4;
double noise = 0.2f;
bool startGame = false;
bool Pause = false;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
int main()
{   
    InitWindow(1000, 1100, "Tetris");
    SetTargetFPS(60);
    InitAudioDevice();
    gameState GameState = menu;
    Music music = LoadMusicStream("D:/C++/newtetris/Tetris.mp3");
    SetMusicVolume(music, noise);
    Sound gameover = LoadSound("D:/C++/newtetris/gameover.mp3");
    Font font = LoadFontEx("D:/C++/newtetris/monogram.ttf", 64, 0, 0);
    Game game = Game();
    Image back = LoadImage("D:/C++/newtetris/back3.png");
    Texture2D backtext = LoadTextureFromImage(back);
    UnloadImage(back);
    Image back2 = LoadImage("D:/C++/newtetris/back6.png");
    Texture2D backtext2 = LoadTextureFromImage(back2);
    UnloadImage(back2);
    Image back3 = LoadImage("D:/C++/newtetris/back4.png");
    Texture2D backtext3 = LoadTextureFromImage(back3);
    UnloadImage(back3);
    Image back4 = LoadImage("D:/C++/newtetris/back5.png");
    Texture2D backtext4 = LoadTextureFromImage(back4);
    UnloadImage(back4);
    Color lightgrey = { 64,64,64, 255 };
    Color lightred = { 255,102,102,255 };
    while (WindowShouldClose() == false)
    {
        int keypress = GetKeyPressed();
        switch (keypress) {
        case KEY_SPACE :
            Pause = !Pause;
            break;
        case KEY_ENTER:
            GameState = menu;
            game.Reset();
            break;
        }
        BeginDrawing();
        ClearBackground(lightgrey);
        PlayMusicStream(music);
        UpdateMusicStream(music);
        if (GameState == menu) {
            DrawTexture(backtext, 0, 0, WHITE);
            DrawText("TETRIS", 670 / 2 - MeasureText("TETRIS", 40) / 2, 40, 120, WHITE);
            Rectangle startButton = { 350, 350, 300, 100 };
            DrawRectangleRounded(startButton, 0.5, 30, GRAY);
            DrawText("Start Game", startButton.x + 40, startButton.y + 25, 40, DARKBLUE);
            Rectangle instruction = { 350, 500, 300, 100 };
            DrawRectangleRounded(instruction, 0.5, 30, cyan);
            DrawText("Instruction", instruction.x + 40, instruction.y + 25, 40, DARKBLUE);
            Rectangle Score = { 350, 650, 300, 100 };
            DrawRectangleRounded(Score, 0.5, 30, orange);
            DrawText("Game mode", Score.x + 40, Score.y + 25, 40, DARKBLUE);
            Rectangle audio = { 350, 800, 300, 100 };
            DrawRectangleRounded(audio, 0.5, 30, green);
            DrawText("Game audio", audio.x + 40, audio.y + 25, 40, DARKBLUE);
            if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                GameState = gameplay;
            }
            if (CheckCollisionPointRec(GetMousePosition(), instruction) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                GameState = instruct;
            }
            if (CheckCollisionPointRec(GetMousePosition(), Score) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                GameState = Hard;
            }
            if (CheckCollisionPointRec(GetMousePosition(), audio) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                GameState = Audio;
            }

        }
        else if (GameState == gameplay) {
            
            DrawTexture(backtext2, 0, 0, WHITE);
            DrawFPS(900, 70);
            DrawTextEx(font, "Score", { 710, 30 }, 45, 2, WHITE);
            DrawTextEx(font, "Next", { 720, 450 }, 45, 2, WHITE);
            DrawTextEx(font, "Highscore: ", { 670, 250 }, 45, 2, WHITE);
           
                if (game.gameOver)
                {
                    PlaySound(gameover);
                    SetSoundVolume(gameover, 0.5);
                    DrawTextEx(font, "GAME OVER", { 670, 850 }, 40, 2, WHITE);
                    Rectangle restart = { 650, 900, 230, 100 };
                    DrawRectangleRec(restart, GRAY);
                    DrawText("Return", restart.x + 40, restart.y + 15, 40, DARKBLUE);
                    if (CheckCollisionPointRec(GetMousePosition(), restart) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        GameState = menu;
                    }
                }
                DrawRectangleRounded({ 600, 110, 340, 120 }, 0.3, 6, lightBlue);

                char scoreText[10];
                sprintf_s(scoreText, "%d", game.score);
                Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
                DrawTextEx(font, scoreText, { 600 + (340 - textSize.x) / 2, 140 }, 45, 2, WHITE);
                DrawRectangleRounded({ 600, 500, 340, 200 }, 0.3, 6, lightBlue);
                string high = to_string(game.high_score);
                DrawTextEx(font, high.c_str(), { 740, 300 }, 40, 3, WHITE);
                game.Draw();
            if (!Pause) {
                if (EventTriggered(z))
                {
                    game.MoveBlockDown();
                }
                game.Input();
                bool x = IsKeyDown(KEY_DOWN);
                if (x) {
                    z = z - 0.003;
                }
                else {
                    z = k;
                }
            }
            if (Pause == true) {
                Rectangle pause = { 135,500,300,100 };
                DrawRectangleRounded(pause, 0.3,6 ,lightBlue);
                DrawText("PAUSED", pause.x + 70, pause.y + 25, 40, WHITE);
            }
           
        }
        else if (GameState == instruct) {
            DrawTexture(backtext3, 0, 0, WHITE);
            DrawText("       Instructions", 570 / 2 - MeasureText("Instructions", 40) / 2, 20, 60, WHITE);
            DrawText("Press Enter to return to the Main Menu ", 50, 100, 30, WHITE);
            DrawText("Press arrow up key to rotate the blocks ", 50, 150, 30, WHITE);
            DrawText("Press arrow left key to move the blocks ", 50, 200, 30, WHITE);
            DrawText("Press arrow right key to move the blocks ", 50, 250, 30, WHITE);
            DrawText("Press arrow down key to move the blocks ", 50, 300, 30, WHITE);
            DrawText("Hold arrow down key to accelerate the game ", 50, 350, 30, WHITE);
            DrawText("Press ESC to escape the programme ", 50, 400, 30, WHITE);
            DrawText("Use gamemode function to define game ", 50, 450, 30, WHITE);
            DrawText("Use audio function to adjust volumn ", 50, 500, 30, WHITE);
            DrawText("When game is over, click on any arrow key to continue  ", 50, 550, 30, WHITE);
            DrawText("Click space bar to stop the game  ", 50, 600, 30, WHITE);
            DrawText("Click space bar again to continue the game  ", 50, 650, 30, WHITE);
           
        }
        else if (GameState == Hard)
        {
            DrawTexture(backtext4, 0, 0, WHITE);
            Rectangle easy = { 350, 200, 300, 100 };
            DrawRectangleRounded(easy, 0.5, 30, lightred);
            DrawText("easy", easy.x + 100, easy.y + 15, 40, DARKBLUE);
            if (CheckCollisionPointRec(GetMousePosition(), easy) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                zz = 0.7;
                k = zz;

                GameState = menu;
            }
            Rectangle medium = { 350, 400, 300, 100 };
            DrawRectangleRounded(medium, 0.5, 30, lightred);
            DrawText("medium", medium.x + 80, medium.y + 15, 40, DARKBLUE);
            if (CheckCollisionPointRec(GetMousePosition(), medium) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                zz = 0.5;
                k = zz;

                GameState = menu;
            }
            Rectangle hard = { 350, 600, 300, 100 };
            DrawRectangleRounded(hard, 0.5, 30, lightred);
            DrawText("hard", hard.x + 100, hard.y + 15, 40, DARKBLUE);
            if (CheckCollisionPointRec(GetMousePosition(), hard) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                zz = 0.2;
                k = zz;

                GameState = menu;
            }
            
        }
        else if (GameState == Audio) {
            DrawTexture(backtext3, 0, 0, WHITE);
            Rectangle audio1 = { 150, 400, 300, 100 };
            DrawRectangleRounded(audio1, 0.5, 30, GRAY);
            DrawText("volume -", audio1.x + 60, audio1.y + 20, 40, DARKBLUE);
            Rectangle audio2 = { 550, 400, 300, 100 };
            DrawRectangleRounded(audio2, 0.5, 30, GRAY);
            DrawText("volumn +", audio2.x + 60, audio2.y + 20, 40, DARKBLUE);
            Rectangle audio3 = { 350, 600, 300, 100 };
            DrawRectangleRounded(audio3, 0.5, 30, GRAY);
            DrawText("volumn off", audio3.x + 55, audio3.y + 20, 40, DARKBLUE);
            if (CheckCollisionPointRec(GetMousePosition(), audio2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                noise += 0.1f;
                if (noise > 1.0f) noise = 1.0f;
                SetMusicVolume(music, noise);
            }
            if (CheckCollisionPointRec(GetMousePosition(), audio1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                noise -= 0.1f;
                if (noise < 0.0f) noise = 0.0f;
                SetMusicVolume(music, noise);
            }
            if (CheckCollisionPointRec(GetMousePosition(), audio3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                noise = 0.0f;
                SetMusicVolume(music, noise);
            }
         
        }
        EndDrawing();

    }
    UnloadSound(gameover);
    CloseAudioDevice();
    UnloadMusicStream(music);
    CloseWindow();
    UnloadTexture(backtext);
    UnloadTexture(backtext2);
    UnloadTexture(backtext3);
    UnloadTexture(backtext4);

    return 0;
}
