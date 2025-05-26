#include <iostream>
#include "level.h"
#include "token.h"
#include <raylib.h>

int main() {
   int monitor = 1;
   int screenWidth = GetMonitorWidth(monitor);
   int screenHeight = GetMonitorHeight(monitor);

   SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
   InitWindow(screenWidth, screenHeight, "Virtual Tabletop");
   SetWindowPosition(GetMonitorPosition(monitor).x, GetMonitorPosition(monitor).y);

   Level level;
   if (!level.loadFromFile("../maps/TestMap/")) { TraceLog(LOG_ERROR, "Failed to load level"); }

   Token token;
   if (!token.loadFromFile("../tokens/TestToken/")) { TraceLog(LOG_ERROR, "Failed to load token"); }
   token.updatePos({200, 200});
   SetTargetFPS(10);

   while (!WindowShouldClose()) {
      level.update(); 

      BeginDrawing();
      ClearBackground(BLACK);
      level.draw();
      token.draw();
      EndDrawing();
   }

   CloseWindow();
   return 0;
}
