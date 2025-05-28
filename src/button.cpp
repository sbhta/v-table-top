#include "button.h"
#include "raylib.h"
#include <iostream>

Button::Button(Vector2 startPos, Vector2 startSize){
   updatePos(startPos);
   updateSize(startSize);
   bounds = {pos.x, pos.y, size.x, size.y};
}
void Button::update(Vector2 mousePos, bool mousePressed){
   hovered = CheckCollisionPointRec(mousePos, bounds);
   pressed = hovered && mousePressed;
   if (pressed) {
      onClick();
   }
}

void Button::draw() const {
   if (pressed) {
      DrawRectangleRec(bounds, PINK);
   }
   else {
      DrawRectangleRec(bounds, WHITE);
   }
}

void Button::onClick(){
   std::cout << "Clicked button" << std::endl;
}

Vector2 Button::getPos(){ return pos; }
Vector2 Button::getSize(){ return size; }
void Button::updatePos(Vector2 newPos){pos = newPos;}
void Button::updateSize(Vector2 newSize){size = newSize;}
