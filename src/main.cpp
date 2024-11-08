#include "raylib.h"
#include "Oide.hpp"
#include <string>

int main(int narg,char** sargs)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight,
               TextFormat("o.ide %s by magnus oblerion",OIDE_VERSION));


    SetTargetFPS(40);   // Set our game to run at 60 frames-per-second
    Oide oide(16);
    if(narg==2)
    {
        oide.Load(sargs[1]);
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(IsFileDropped())
        {
            FilePathList files = LoadDroppedFiles();
            oide.Load(files.paths[0]);
            UnloadDroppedFiles(files);
        }
        BeginDrawing();
        oide.Draw();
        EndDrawing();
    }
    oide.Free();
    CloseWindow();// Close window and OpenGL

    return 0;
}

