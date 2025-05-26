#include "level.h"
#include <raylib.h>

Level::Level() {
   background = {0};
}

Level::~Level(){
   if (background.id > 0){
      UnloadTexture(background);
   }
}

bool Level::loadFromFile(const std::string& path) {
   background = LoadTexture((path+"map.png").c_str());
   if (background.id == 0) return false;
   obstacles.push_back({{100, 100, 200, 100}, RED});
   obstacles.push_back({{400, 200, 150, 200}, DARKGRAY});
   return true;
}

void Level::update() {
    // Add level-specific logic later if needed
}

void Level::draw(){
   float scale = std::min(
    static_cast<float>(GetScreenWidth()) / background.width,
    static_cast<float>(GetScreenHeight()) / background.height
   );
   DrawTextureEx(background, {0, 0}, 0.0f, scale, WHITE);
   for (Obstacle obs : obstacles){
      DrawRectangleRec(obs.bounds, obs.color);
   }
   if(gridVisible) drawGrid();
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

const std::vector<Obstacle>& Level::getObstacles() const {
    return obstacles;
}
