#include <iostream>
#include <raylib.h>
#include <string>
#include "button.h"
#include "color.h"
#include "greeter.h"
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
   int monitor = GetAccurateCurrentMonitor();
   float screenWidth = GetMonitorWidth(monitor);
   float screenHeight = GetMonitorHeight(monitor);
   SetWindowSize(screenWidth, screenHeight);
   SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
   SetWindowPosition(GetMonitorPosition(monitor).x, GetMonitorPosition(monitor).y);

   GFM.loadFont("map-name", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 36);
   GFM.loadFont("sidebar-icon", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);
   GFM.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 36);
   GFM.loadFont("sidebar-text", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 42);
   GFM.loadFont("token-name", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 16);
   GFM.loadFont("token-hp", "../resources/fonts/0xProtoNerdFont-Regular.ttf", 12);

   if (!GCM.getTheme("../resources/themes/catppuccin.txt")) return 1;

   SetTargetFPS(300);
   AppState currentState = AppState::GREETING;
   // stuff for level during game
   Level level = {};
   SideBar sidebar = {{}, {}, GCM.getColor("bgSidebar"),GCM.getColor("fgSidebar"), level};
   bool loadingGame = true;
   // stuff for greeter
   Greeter greeter({screenWidth, screenHeight});
   TextButton b = {{200, 500}, {400, 100}, "CLICK ME", GFM.getFont("sidebar-text", 42), WHITE, BLACK, [&currentState](){currentState=AppState::GAME;}};
   while (!WindowShouldClose()) {
      BeginDrawing();
      switch (currentState) {
         case AppState::GREETING:
            greeter.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            if (greeter.isMapSelected()){
               std::string mapPath = greeter.getSelectedMap();
               if (!level.loadMap(mapPath)){
                  std::cout << "Could not load map from specified path" << std::endl;
                  return 1;
               }
               currentState = AppState::GAME;
            }
            ClearBackground(GCM.getColor("bgGreeter"));
            greeter.draw();
            break;
         case AppState::GAME:
            if (loadingGame){
               sidebar.updatePos({(float)GetScreenWidth()-200, 0});
               sidebar.updateSize({150, (float)GetScreenWidth()-20});
               sidebar.initButtons();
               loadingGame = false;
            }
            level.update(GetMousePosition()); 
            sidebar.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            ClearBackground(BLACK);
            level.draw();
            sidebar.draw();
            break;
      }
      EndDrawing();
      if (IsKeyPressed(KEY_Q)){
         break;
      }
   }
   CloseWindow();
   return 0;
}
