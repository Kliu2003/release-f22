#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base, sticker;
  base.readFromFile("../alma.png");
  sticker.readFromFile("../i.png");
  StickerSheet imageWithSticker(base, 3);
  imageWithSticker.addSticker(sticker, 1, 1);
  imageWithSticker.addSticker(sticker, 200, 200);
  imageWithSticker.addSticker(sticker, 500, 500);
  Image output = imageWithSticker.render();
  output.writeToFile("../myImage.png");

  return 0;
}
