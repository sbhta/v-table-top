#include "token.h"
#include <raylib.h>

Token::Token(){
   sprite = {};
   isSelected = false;
}

Token::~Token(){
   if (sprite.id > 0){
      UnloadTexture(sprite);
   }
}

bool Token::loadFromFile(const std::string& path){
   sprite = LoadTexture((path+"sprite.png").c_str());
   if (sprite.id == 0) return false;
   return true;
}

void Token::draw(){
   DrawTexture(sprite, pos.x, pos.y,  WHITE);
   for (float i = 0; i < 10; i+=0.5){
      DrawCircleLines(pos.x+(sprite.width/2), pos.y+(sprite.height/2), 50+i, BLACK);
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

