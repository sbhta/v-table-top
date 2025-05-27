#pragma once
#include <string>
#include <raylib.h>

class Token{
public:
   Token();
   ~Token();
   bool isSelected = false;
   bool loadFromFile(const std::string& path);
   void draw();
   void updatePos(Vector2 newPos);
   Vector2 getPos();
   bool isMouseOver(Vector2 mousePos) const;
   Rectangle getBounds() const;
private:
   Vector2 pos;
   Texture2D sprite;
};

