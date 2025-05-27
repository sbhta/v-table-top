#include "token.h"
#include <iostream>
#include <raylib.h>

Token::Token(const std::string& path, const Vector2 startPos){
   sprite = {};
   isSelected = false;
   loadFromSprite(path);
   pos = startPos;
}

bool Token::loadFromSprite(const std::string& path){
   sprite = LoadTexture((path+"sprite.png").c_str());
   if (sprite.id == 0) return false;
   std::cout << "LOADED SPRITE WITH ID " + std::to_string(sprite.id) << std::endl;
   return true;
}

void Token::draw(){
   DrawTexture(sprite, pos.x, pos.y,  WHITE);
   for (float i = 0; i < 7; i+=0.5){
      if (isSelected) DrawCircleLines(pos.x+((float)sprite.width/2), pos.y+((float)sprite.height/2), 50+i, PINK);
      else DrawCircleLines(pos.x+((float)sprite.width/2), pos.y+((float)sprite.height/2), 50+i, BLACK);
   }
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
    return Rectangle{ pos.x, pos.y, (float)sprite.width, (float)sprite.height };
}
