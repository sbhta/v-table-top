#include "color.h"
#include "rutils.h"

ColorManager::ColorManager(){
   // TODO:Add a directory called themes with different themes 
}
ColorManager::~ColorManager(){
   colors.clear();
}

void ColorManager::addColor(const std::string& colorName, const std::string& hexColor){
   colors[colorName] = HexToColor(hexColor);
}
Color& ColorManager::getColor(const std::string& name){
   return colors[name];
}

ColorManager GCManager;
