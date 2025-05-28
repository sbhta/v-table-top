#pragma once
#include <string>
#include <raylib.h>

class Token{
public:
   Token(const std::string& path, const Vector2 startPos);
   bool loadFromSprite(const std::string& path);
   void updatePos(Vector2 newPos);
   Vector2 getPos();
   Vector2 getSize();
   void updateSize(Vector2 newSize);
   void draw();
   bool isMouseOver(Vector2 mousePos) const;
   Rectangle getBounds() const;
   bool isSelected = false;
private:
   Vector2 pos;
   Vector2 size = {180, 180};
   Texture2D sprite;
};

