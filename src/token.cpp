#include "token.h"
#include <raylib.h>
#include <string>
#include "fonts.h"
#include "rutils.h"
   

Token::Token(const std::string& path, const Vector2 startPos, const Vector2 startSize, const std::string& startName, std::pair<int, int> startHp){
   sprite = {};
   isSelected = false;
   updateSize(startSize);
   loadSprite(path);
   pos = startPos;
   name = startName;
   hp = startHp;
}
bool Token::loadSprite(const std::string& path){
   sprite = LoadTexture((path+"sprite.png").c_str());
   if (sprite.id == 0) return false;
   sprite = ResizeTexture(sprite, size.x, size.y);
   updateSize({(float)sprite.width, (float)sprite.width});
   return true;
}
void Token::draw(){
   DrawTexture(sprite, pos.x, pos.y,  WHITE);
   for (float i = 0; i < 5; i+=0.5){
      if (isSelected) DrawCircleLines(pos.x+(size.x/2), pos.y+(size.y/2), (size.x/2)+i, PINK);
      else DrawCircleLines(pos.x+(size.x/2), pos.y+(size.y/2), (size.x/2)+i, BLACK);
   }
   if (isHovered) {
      DrawTextEx(nameFont,name.c_str(),{(pos.x+size.x/2)-(MeasureTextEx(nameFont,name.c_str(),nameFont.baseSize,0).x/2), pos.y-20 },nameFont.baseSize,0,PINK);
   }
   // TODO: draw health beneath the token
}
Vector2 Token::getSize(){
   return size;
}
void Token::updateSize(Vector2 newSize){
   size = newSize;
}
Vector2 Token::getPos(){
   return pos;
}
void Token::updatePos(Vector2 newPos){
   pos = newPos;
}
bool Token::isMouseOver(Vector2 mousePos){
   return CheckCollisionPointRec(mousePos, getBounds());
}
Rectangle Token::getBounds() const{
    return Rectangle{ pos.x, pos.y, size.x, size.y };
}
