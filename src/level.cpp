#include "level.h"
#include "raymath.h"
#include "token.h"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

Level::Level() {
   background = {};
   tokens.push_back({"../tokens/TestToken/", {600, 500}, {50, 50}, "Sbhta", {50, 100}});
}
Level::~Level(){
   if (background.id > 0){
      UnloadTexture(background);
   }
}
bool Level::loadMap(const std::string& pathDir) {
   path = pathDir;
   // loading the map image itself
   UnloadTexture(background); background = LoadTexture((pathDir+"map.png").c_str());
   if (background.id == 0) return false;
   // scale the image according to screen
   float scale = std::min( static_cast<float>(GetScreenWidth()) / background.width, static_cast<float>(GetScreenHeight()) / background.height);
   Image image = LoadImageFromTexture(background); ImageResize(&image, image.width*scale, image.height*scale);
   UnloadTexture(background); background = LoadTextureFromImage(image);
   UnloadImage(image);

   // TODO: load map info like tokens and obstecales
   std::vector<std::vector<std::string>> data;
   std::ifstream infile(pathDir+"data.txt");
   if (infile){
      std::string line;
      while (std::getline(infile, line)){
         // comments
         if (line[0] == '#') continue;
         // handling a token
         std::vector<std::string> parts;
         std::string tempPart = "";
         for (char ch : line){
            if (ch == '.') {
               parts.push_back(tempPart);
               tempPart = "";
               continue;
            }
            tempPart += ch;
         }
         parts.push_back(tempPart);
         data.push_back(parts);
      }
      infile.close();
   }
   
   for (const auto& v : data){
      // type token
      if (v[0] == "t"){
         tokens.push_back({"../tokens/TestToken/", {std::stof(v[4]), std::stof(v[5])}, {std::stof(v[6]), std::stof(v[7])}, v[1], {std::stoi(v[2]), std::stoi(v[3])}});
      }
   }

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
void Level::update(Vector2 mousePos) {
   handleTokenSelectionAndDrag(mousePos);
}
void Level::handleTokenSelectionAndDrag(Vector2 mousePos){
   for (auto& token : tokens){
      if (token.isMouseOver(mousePos)){
         token.isHovered = true;
         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            selectedToken = &token;
            dragOffset = Vector2Subtract(token.getPos(), mousePos);
            break;
         }
      }
      else {
         token.isHovered = false;
      }
   }
   if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedToken) {
      if (selectedToken->isMouseOver(mousePos)) selectedToken->updatePos(Vector2Add(mousePos, dragOffset)); 
      else selectedToken = nullptr; 
   }

}
void Level::switchGrid(){
   gridVisible = !gridVisible;
}
