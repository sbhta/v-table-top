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

   bool loadFromFile(const std::string& path);
   void update();
   void draw();
   void drawGrid();
private:
   Texture2D background;
   int gridSize = 64;
   bool gridVisible = true;

   std::vector<Token> tokens;
   Token* selectedToken = nullptr;
   Vector2 dragOffset = {0, 0};

   void handleTokenSelectionAndDrag();
};
