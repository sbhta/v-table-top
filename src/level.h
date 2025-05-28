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
   Level(const bool grid);
   ~Level();

   bool loadFromFile(const std::string& path);
   void update();
   void draw();
   void drawGrid(); //TODO: make grid appear only on the map, not whole window
private:
   Texture2D background;
   int gridSize = 64;
   bool gridVisible = false;

   std::vector<Token> tokens;
   Token* selectedToken = nullptr;
   Vector2 dragOffset = {0, 0};

   void handleTokenSelectionAndDrag();
};
