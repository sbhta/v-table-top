#include <iostream>
#include "level.h"
#include "button.h"
#include <raylib.h>

int main() {
   int monitor = 1;
   int screenWidth = GetMonitorWidth(monitor);
   int screenHeight = GetMonitorHeight(monitor);

   SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
   InitWindow(screenWidth, screenHeight, "Virtual Tabletop");
   SetWindowPosition(GetMonitorPosition(monitor).x, GetMonitorPosition(monitor).y);

   Level level = {false};
   if (!level.loadFromFile("../maps/TestMap/")) { TraceLog(LOG_ERROR, "Failed to load level"); }

   SetTargetFPS(60);

   //TESTING
   Button button = {{50, 50}, {50, 50}};
   //END TESTING
   while (!WindowShouldClose()) {
      level.update(); 
      button.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));

      BeginDrawing();
      ClearBackground(BLACK);
      level.draw();
      button.draw();
      EndDrawing();
   }

   CloseWindow();
   return 0;
}
