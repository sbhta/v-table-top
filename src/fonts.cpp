#include "fonts.h"
#include "raylib.h"
#include <stdexcept>
#include <string>

FontManager::~FontManager(){
   unloadAll();
}

void FontManager::loadFont(const std::string &name, const std::string &filePath, int size){
   if (fonts[name].count(size) > 0) return;
   Font font = LoadFontEx(filePath.c_str(), size, nullptr, 0);
   if (font.texture.id == 0) {
      throw std::runtime_error("Failed to load font: " + filePath);
   }
   fonts[name][size] = font;
}

Font& FontManager::getFont(const std::string &name, int size){
   if (fonts.count(name) == 0 || fonts[name].count(size) == 0){
      throw std::runtime_error("Font not loaded: " + name + " size " + std::to_string(size));
   }
   return fonts[name][size];
}

void FontManager::unloadAll(){
   for (auto& [name, sizeMap] : fonts){
      for (auto& [size, font] : sizeMap){
         UnloadFont(font);
      }
   }
   fonts.clear();
}

FontManager GFManager;
