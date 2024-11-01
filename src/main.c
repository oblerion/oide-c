#include "raylib.h"
#include "Oide.h"
int main(int narg,char** sargs)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000; //GetMonitorWidth(0);
    const int screenHeight = 600;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight,
               TextFormat("o.ide %s by magnus oblerion",OIDE_VERSION));


    SetTargetFPS(40);   // Set our game to run at 60 frames-per-second
    Oide(16);

    if(narg==2)
    {
        Oide_Load(sargs[1]);
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(IsFileDropped())
        {
            FilePathList files = LoadDroppedFiles();
            Oide_Load(files.paths[0]);
            UnloadDroppedFiles(files);
        }
        BeginDrawing();
        Oide_Draw();
        EndDrawing();
    }
    Oide_Free();
    CloseWindow();// Close window and OpenGL

    return 0;
}

