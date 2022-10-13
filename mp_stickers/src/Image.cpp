#include "image.h"
using namespace cs225;

void Image::illinify() {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
        if (pixel.h >= 114 && pixel.h <= 243) {
          pixel.h = 216; 
        } else {
          pixel.h = 11;
        }
    }
  }
}

void Image::lighten() {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
      if (pixel.l < 1 && pixel.l >= 0) {
        pixel.l += 0.1;
      }
    }
  }
}
 
void Image::darken() {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
      if (pixel.l < 1 && pixel.l >= 0) {
        pixel.l -= 0.1;
      }
    }
  }
}

void Image::saturate() {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
      if (pixel.s < 1 && pixel.s >= 0) {
        pixel.s += 0.1;
      } 
    }
  }
}

void Image::desaturate() {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
      if (pixel.s < 1 && pixel.s >= 0) {
        pixel.s -= 0.1;
      } 
    }
  }
}


void Image::grayscale() {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  for (int row = 0; row < this -> width(); row++) {
    for (int col = 0; col < this -> height(); col++){
      HSLAPixel pixel = this -> getPixel(row, col);
      if (pixel.h + degrees <= 360) {
        pixel.h += degrees;
      }
      pixel.h = (pixel.h + degrees) - 360
    }
  }
}