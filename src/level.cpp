#include "level.h"
#include "raymath.h"
#include "rutils.h"
#include "token.h"
#include <raylib.h>

Level::Level() {
   background = {};
   tokens.push_back({"../tokens/TestToken/", {500, 500}, {50, 50}, "Sbhta The Great", {43, 75}});
   tokens.push_back({"../tokens/TestToken/", {500, 500}, {50, 50}, "Sbhta The Greatest", {47, 75}});
}
Level::~Level(){
   if (background.id > 0){
      UnloadTexture(background);
   }
}
bool Level::loadMap(const std::string& path) {
   // loading the map image itself
   UnloadTexture(background); background = LoadTexture((path+"map.png").c_str());
   if (background.id == 0) return false;
   // scale the image according to screen
   float scale = std::min( static_cast<float>(GetScreenWidth()) / background.width, static_cast<float>(GetScreenHeight()) / background.height);
   Image image = LoadImageFromTexture(background); ImageResize(&image, image.width*scale, image.height*scale);
   UnloadTexture(background); background = LoadTextureFromImage(image);
   UnloadImage(image);

   // TODO: load map info like tokens and obstecales


   return true;
}
void Level::draw(){
   DrawTextureEx(background, {0, 0}, 0.0f, 1, WHITE);
   
   if(gridVisible) drawGrid();

   for (auto& token : tokens){
      token.draw();
   }
}
void Level::drawGrid() {
   float mapWidth = background.width;
   float mapHeight = background.height;
   Color gridColor = Fade(LIGHTGRAY, 0.4f);
   for (int x = 0; x < mapWidth;x += gridSize){
      DrawLine(x, 0, x, mapHeight, gridColor);
   }
   for (int y = 0; y < mapHeight;y += gridSize){
      DrawLine(0, y, mapWidth, y, gridColor);
   }
}
void Level::update() {
   handleTokenSelectionAndDrag();
}
void Level::handleTokenSelectionAndDrag(){
   Vector2 mouse = GetMousePosition();
   // Testing to see if better to first check if button over the token before seeing if button pressed
   for (auto& token : tokens){
      if (token.isMouseOver(mouse)){
         token.isHovered = true;
         break;
      }
      else token.isHovered = false;
   }
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
void Level::switchGrid(){
   gridVisible = !gridVisible;
}
