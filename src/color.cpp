#include "color.h"
#include "rutils.h"
#include <fstream>
#include <string>

ColorManager::ColorManager(){
}
ColorManager::~ColorManager(){
   colors.clear();
}

void ColorManager::addColor(const std::string& colorName, const std::string& hexColor){
   colors[colorName] = HexToColor(hexColor);
}
bool ColorManager::getTheme(const std::string& themePath){
   std::ifstream file(themePath);
   if (!file){throw "FILE FOR THEME NOT FOUND";return false;}
   std::string line;
   while (std::getline(file, line)){
      std::string temp = "";
      std::string colorName;
      for (const char& ch : line){
         if (ch == '.'){
            colorName = temp;
            temp.clear();
            continue;
         }
         temp += ch;
      }
      addColor(colorName, temp);
   }
   return true;
}
Color& ColorManager::getColor(const std::string& name){
   return colors[name];
}

ColorManager GCM;
