#include <exception>
#include <iostream>
#include "level.h"
#include <raylib.h>
#include <string>
#include "sidebar.h"
#include "fonts.h"

void hello(){
   std::cout << "HELLO FROM BUTTON" << std::endl;
}

int main() {
   int monitor = 1;
   int screenWidth = GetMonitorWidth(monitor);
   int screenHeight = GetMonitorHeight(monitor);

   SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
   InitWindow(screenWidth, screenHeight, "Virtual Tabletop");
   SetWindowPosition(GetMonitorPosition(monitor).x, GetMonitorPosition(monitor).y);

   GFManager.loadFont("sidebar-icon", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);
   GFManager.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 36);
   GFManager.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);

   Level level = {false}; if (!level.loadFromFile("../maps/TestMap/")) { TraceLog(LOG_ERROR, "Failed to load level"); }
   SideBar sidebar = {{(float)GetScreenWidth()-200, 0}, {150, (float)GetScreenHeight()-20}, WHITE, level};
   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      level.update(); 
      sidebar.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
      BeginDrawing();
      ClearBackground(BLACK);
      level.draw();
      sidebar.draw();
      EndDrawing();
   }
   CloseWindow();
   return 0;
}
