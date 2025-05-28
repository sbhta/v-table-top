#include "rutils.h"

Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight) {
   // Create a render texture to draw into
   RenderTexture2D render = LoadRenderTexture(newWidth, newHeight);

   // Draw the original texture to the new size into the render texture
   BeginTextureMode(render);
   ClearBackground(BLANK); // Optional
   DrawTexturePro(
      texture,
      (Rectangle){ 0, 0, (float)texture.width, (float)-texture.height }, // Flip vertically
      (Rectangle){ 0, 0, (float)newWidth, (float)newHeight },
      (Vector2){ 0, 0 },
      0.0f,
      WHITE
   );
   EndTextureMode();

   // Extract the texture from the render texture
   Image image = LoadImageFromTexture(render.texture); // Copy it as an image
   Texture2D resized = LoadTextureFromImage(image);    // Convert back to texture

   // Clean up
   UnloadImage(image);
   UnloadRenderTexture(render);

   return resized;
}
