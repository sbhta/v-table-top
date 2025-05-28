#include "token.h"
#include <raylib.h>
#include "rutils.h"
   

Token::Token(const std::string& path, const Vector2 startPos, const Vector2 startSize){
   sprite = {};
   isSelected = false;
   updateSize(startSize);
   loadFromSprite(path);
   pos = startPos;
}

bool Token::loadFromSprite(const std::string& path){
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

bool Token::isMouseOver(Vector2 mousePos) const{
   return CheckCollisionPointRec(mousePos, getBounds());
}
Rectangle Token::getBounds() const{
    return Rectangle{ pos.x, pos.y, size.x, size.y };
}
