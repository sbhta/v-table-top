#pragma once
#include "button.h"
#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

class Greeter{
public:
   Greeter(Vector2 screenSize);
   void update(Vector2 mousePos, bool mousePressed);
   void draw();
   bool isMapSelected() const;
   std::string getSelectedMap() const;
private:
   std::vector<std::string> mapNames;
   std::vector<Texture2D> mapTextures;
   std::vector<std::unique_ptr<Button>> mapButtons;
   std::string selectedMap;
   void loadAvailableMaps();
};
