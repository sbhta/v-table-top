#include <iostream>
#include <raylib.h>
#include <string>
#include "sidebar.h"
#include "fonts.h"
#include "rutils.h"
#include "level.h"

enum class AppState {
   GREETING,
   GAME,
};

int main() {
   InitWindow(1000, 1000, "Virtual Tabletop");
   AppState currentState = AppState::GAME;
   int monitor = GetAccurateCurrentMonitor();
   int screenWidth = GetMonitorWidth(monitor);
   int screenHeight = GetMonitorHeight(monitor);
   SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
   SetWindowPosition(GetMonitorPosition(monitor).x, GetMonitorPosition(monitor).y);
   SetWindowSize(screenWidth, screenHeight);

   GFManager.loadFont("sidebar-icon", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);
   GFManager.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 36);
   GFManager.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);

   Level level = {false}; if (!level.loadFromFile("../maps/TestMap/")) { TraceLog(LOG_ERROR, "Failed to load level"); }
   SideBar sidebar = {{(float)GetScreenWidth()-200, 0}, {150, (float)GetScreenHeight()-20}, WHITE, level};
   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      BeginDrawing();
      level.update(); 
      sidebar.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
      ClearBackground(BLACK);
      level.draw();
      sidebar.draw();
      EndDrawing();
   }
   CloseWindow();
   return 0;
}
