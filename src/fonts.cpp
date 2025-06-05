#include "fonts.h"
#include "raylib.h"
#include <stdexcept>
#include <string>
#include <vector>

FontManager::~FontManager(){
   unloadAll();
}

void FontManager::loadFont(const std::string &name, const std::string &filePath, int size){
   if (fonts[name].count(size) > 0) return; // font already loaded

   std::vector<int> codepoints = {0xf02c2};
   for (int i = 0x20; i <= 0x7E; i++) codepoints.push_back(i);
   for (int i = 0xA0; i <= 0xFF; i++) codepoints.push_back(i);
   // between 0xE000 and 0x10FFFF if you want to have access to ALL nerdfont icons and what not
   Font font = LoadFontEx(filePath.c_str(), size, codepoints.data(), codepoints.size());
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
