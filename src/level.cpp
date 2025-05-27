#include "level.h"
#include "raymath.h"
#include "token.h"
#include <raylib.h>

Level::Level() {
   background = {};
   tokens.push_back({});
   tokens.push_back({});
   tokens[0].updatePos({300, 300});
   tokens[1].updatePos({800, 800});
   tokens[0].loadFromFile("../tokens/TestToken/");
   tokens[1].loadFromFile("../tokens/TestToken/");
}

Level::~Level(){
   if (background.id > 0){
      UnloadTexture(background);
   }
   for (auto& token : tokens){
      token.~Token();
   }
}

bool Level::loadFromFile(const std::string& path) {
   background = LoadTexture((path+"map.png").c_str());
   if (background.id == 0) return false;
   return true;
}

void Level::update() {
   handleTokenSelectionAndDrag();
}

void Level::handleTokenSelectionAndDrag(){
   Vector2 mouse = GetMousePosition();
   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      selectedToken = nullptr;
      for (auto& token : tokens){
         token.isSelected = false;
         if (token.isMouseOver(mouse)){
            selectedToken = &token;
            token.isSelected = true;
            dragOffset = Vector2Subtract(mouse, token.getPos());
            break;
         }
      }
   }
   if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectedToken) selectedToken->updatePos(Vector2Subtract(mouse, dragOffset));
   if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) selectedToken = nullptr;
}

void Level::draw(){
   float scale = std::min(
    static_cast<float>(GetScreenWidth()) / background.width,
    static_cast<float>(GetScreenHeight()) / background.height
   );
   DrawTextureEx(background, {0, 0}, 0.0f, scale, WHITE);
   if(gridVisible) drawGrid();
   for (auto& token : tokens){
      token.draw();
   }
}
void Level::drawGrid() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Color gridColor = Fade(LIGHTGRAY, 0.4f);
    for (int x = 0; x < screenWidth; x += gridSize) {
        DrawLine(x, 0, x, screenHeight, gridColor);
    }
    for (int y = 0; y < screenHeight; y += gridSize) {
        DrawLine(0, y, screenWidth, y, gridColor);
    }
}

