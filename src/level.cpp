#include "level.h"
#include "raymath.h"
#include "token.h"
#include <raylib.h>

Level::Level(const bool grid) {
   background = {};
   tokens.push_back({"../tokens/TestToken/", {500, 500}, {50, 50}});
   tokens.push_back({"../tokens/TestToken/", {1000, 500}, {50, 50}});
   if (grid) gridVisible = true;
}
Level::~Level(){
   if (background.id > 0){
      UnloadTexture(background);
   }
}

bool Level::loadFromFile(const std::string& path) {
   background = LoadTexture((path+"map.png").c_str());
   if (background.id == 0) return false;
   return true;
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
    int mapWidth = background.width;
    int mapHeight = background.height;
    Color gridColor = Fade(LIGHTGRAY, 0.4f);
    for (int x = 0; x < mapWidth; x += gridSize) DrawLine(x, 0, x, mapHeight, gridColor);
    for (int y = 0; y < mapHeight; y += gridSize) DrawLine(0, y, mapWidth, y, gridColor);
    
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
            selectedToken->isSelected = true;
            dragOffset = Vector2Subtract(mouse, token.getPos());
            break;
         }
      }
   }
   if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectedToken) selectedToken->updatePos(Vector2Subtract(mouse, dragOffset));
   if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      if (selectedToken) selectedToken->isSelected = false;
      selectedToken = nullptr;
   }
}


