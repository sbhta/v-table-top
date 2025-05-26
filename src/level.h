#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>

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
   const std::vector<Obstacle>& getObstacles() const;
private:
   Texture2D background;
   std::vector<Obstacle> obstacles;
   int gridSize = 64;
   bool gridVisible = true;
};
