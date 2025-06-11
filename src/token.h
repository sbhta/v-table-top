#pragma once
#include "fonts.h"
#include <string>
#include <raylib.h>
#include <utility>

class Token{
public:
   Token(const std::string& path, const Vector2 startPos, const Vector2 startSize, const std::string& startName, std::pair<int, int> startHp);
   bool loadSprite(const std::string& path);
   Vector2 getPos();
   Vector2 getSize();
   std::string getName();
   std::pair<int, int> gethp();
   void updatePos(Vector2 newPos);
   void updateSize(Vector2 newSize);
   void updateName(const std::string& name);
   void updateHp(int damage);
   void updateMaxHp(int damage);
   void draw();
   bool isMouseOver(Vector2 mousePos);
   Rectangle getBounds() const;
   bool isSelected = false;
   bool isHovered = false;
   Font nameFont = GFManager.getFont("token-name", 16);
private:
   Vector2 pos;
   Vector2 size = {180, 180};
   Texture2D sprite;
   std::string name;
   std::pair<int, int> hp;
};

