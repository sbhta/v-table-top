#include "greeter.h"
#include "button.h"
#include "color.h"
#include "fonts.h"
#include "raylib.h"
#include "rutils.h"
#include <memory>
#include <filesystem>

Greeter::Greeter(Vector2 screenSize){
   loadAvailableMaps();
   float y = 200;
   for (const auto& map : mapNames){
      mapButtons.push_back(std::make_unique<TextButton>(
         Vector2{screenSize.x/2-100, y},
         Vector2{200, 240},
         map,
         GFM.getFont("map-name", 36),
         GCM.getColor("bgGreeter"),
         GCM.getColor("fgGreeter"),
         [this, map](){
            selectedMap = "../maps/" + map + "/";
         }
      ));
      y += 250;
   }
}
void Greeter::loadAvailableMaps(){
   namespace fs = std::filesystem;
   for (const auto& entry : fs::directory_iterator("../maps/")){
      if (entry.is_directory()){
         mapNames.push_back(entry.path().filename().string());
         Texture2D t = LoadTexture((entry.path().string() + "/map.png").c_str());
         mapTextures.push_back(ResizeTexture(t, 200, 200));
      }
   }
}
void Greeter::update(Vector2 mousePos, bool mousePressed){
   for (auto& button : mapButtons){
      button->update(mousePos, mousePressed);
   }
}
void Greeter::draw(){
   for (size_t i = 0; i < mapButtons.size(); ++i){
      mapButtons[i]->draw();
      DrawTexture(mapTextures[i], mapButtons[i]->getPos().x, mapButtons[i]->getPos().y+30, WHITE);
   }
}
bool Greeter::isMapSelected() const {
   return !selectedMap.empty();
}
std::string Greeter::getSelectedMap() const{
   return selectedMap;
}
