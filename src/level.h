#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include "token.h"

struct Obstacle {
   Rectangle bounds;
   Color color;
};

class Level {
public:
   Level();
   ~Level();

   bool loadMap(const std::string& path);
   void update(Vector2 mousePos);
   void draw();
   void drawGrid(); 
   void switchGrid();
   int gridSize = 36;
   Token* selectedToken = nullptr;
private:
   Texture2D background;
   bool gridVisible = false;
   std::vector<Token> tokens;
   Vector2 dragOffset = {0, 0};
   std::string path;

   void handleTokenSelectionAndDrag(Vector2 mousePos);
};
