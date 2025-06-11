#include <iostream>
#include <raylib.h>
#include <string>
#include "button.h"
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
   AppState currentState = AppState::GREETING;
   int monitor = GetAccurateCurrentMonitor();
   int screenWidth = GetMonitorWidth(monitor);
   int screenHeight = GetMonitorHeight(monitor);

   GFManager.loadFont("sidebar-icon", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);
   GFManager.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 36);
   GFManager.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);

   Level level = {};
   SideBar sidebar = {{}, {}, WHITE, level};
   bool loadingGame = true;
   SetTargetFPS(60);
   TextButton b = {{500, 500}, {100, 100}, "CLICK ME", GFManager.getFont("sidebar-text", 42), WHITE, BLACK, [&currentState](){currentState=AppState::GAME;}};
   while (!WindowShouldClose()) {
      BeginDrawing();
      switch (currentState) {
         case AppState::GREETING:
            b.draw();
            b.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            break;
         case AppState::GAME:
            if (loadingGame){
               SetWindowSize(screenWidth, screenHeight);
               SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
               SetWindowPosition(GetMonitorPosition(monitor).x, GetMonitorPosition(monitor).y);
               level = {};
               level.loadMap("../maps/TestMap/");
               sidebar.updatePos({(float)GetScreenWidth()-200, 0});
               sidebar.updateSize({150, (float)GetScreenWidth()-20});
               sidebar.initButtons();
               loadingGame = false;
            }
            level.update(); 
            sidebar.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            ClearBackground(BLACK);
            level.draw();
            sidebar.draw();
            break;
      }
      EndDrawing();
   }
   CloseWindow();
   return 0;
}
