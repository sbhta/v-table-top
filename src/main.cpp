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
   try{GFManager.loadFont("sidebar-icon", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);}
   catch (const std::exception& e){
      TraceLog(LOG_ERROR, e.what());
      return 1;
   }
   Level level = {false}; if (!level.loadFromFile("../maps/TestMap/")) { TraceLog(LOG_ERROR, "Failed to load level"); }
   SideBar sidebar = {{(float)GetScreenWidth()-50, 0}, {50, (float)GetScreenHeight()-20}, WHITE};
   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      level.update(); 
      sidebar.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
      BeginDrawing();
      ClearBackground(BLACK);
      level.draw();
      sidebar.draw();
      DrawTextEx(GFManager.getFont("sidebar-icon", 42), "<HELLO world󰋂 ", {100, 100}, GFManager.getFont("sidebar-icon", 42).baseSize, 3.0f, WHITE);
      EndDrawing();
   }
   CloseWindow();
   return 0;
}
