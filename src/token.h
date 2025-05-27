#pragma once
#include <string>
#include <raylib.h>

class Token{
public:
   Token(const std::string& path, const Vector2 startPos);
   bool loadFromSprite(const std::string& path);
   void updatePos(Vector2 newPos);
   Vector2 getPos();
   void draw();
   bool isMouseOver(Vector2 mousePos) const;
   Rectangle getBounds() const;
   bool isSelected = false;
private:
   Vector2 pos;
   Texture2D sprite;
};

