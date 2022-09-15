#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cassert>
#include <algorithm>
#include <functional>
#include <cmath>

void Image::lighten(){
    /*Iterate through each pixel and increase luminance by 0.1 when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).l = min(getPixel(i,j).l+0.1, 1.0);
        }
    }
}
void Image::lighten(double amount){
    /*Iterate through each pixel and increase luminance by the wanted amount when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).l = min(getPixel(i,j).l+amount, 1.0);
        }
    }
}
void Image::darken(){
    /*Iterate through each pixel and decrease luminance by 0.1 when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).l = max(getPixel(i,j).l-0.1, 0.0);
        }
    }
}
void Image::darken(double amount){
    /*Iterate through each pixel and decrease luminance by the wanted amount when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).l = max(getPixel(i,j).l-amount, 0.0);
        }
    }
}
void Image::saturate(){
    /*Iterate through each pixel and increase saturation by the wanted amount when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).s = min(getPixel(i,j).s+0.1, 1.0);
        }
    }
}
void Image::saturate(double amount){
    /*Iterate through each pixel and increase saturation by 0.1 when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).s = min(getPixel(i,j).s+amount, 1.0);
        }
    }
}
void Image::desaturate(){
    /*Iterate through each pixel and decrease saturation by 0.1 when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).s = max(getPixel(i,j).s-0.1, 0.0);
        }
    }
}
void Image::desaturate(double amount){
    /*Iterate through each pixel and decrease saturation by the wanted amount when possible*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).s = max(getPixel(i,j).s-amount, 0.0);
        }
    }
}
void Image::grayscale(){
    /*Grayscales each pixel in the image*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j).s = 0;
        }
    }
}
void Image::rotateColor(double degrees){
    /*Rotate the color of each pixel by the wanted degrees*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            if(fmod((getPixel(i,j).h+degrees), 360.0) >= 0){
                getPixel(i,j).h = fmod((getPixel(i,j).h+degrees), 360.0);
            }
            else{
                getPixel(i,j).h = fmod((getPixel(i,j).h+degrees), 360.0)+360;
            }
        }
    }
}
void Image::illinify(){
    /*Iterate through each pixel and see if its closer to the orange color or blue color. Then, adjust the color accordingly*/
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            this->rotateColor(0.0);
            int orangeDist = min(getPixel(i,j).h-11, 360+11-getPixel(i,j).h);
            int blueDist = min(getPixel(i,j).h-216, 360+216-getPixel(i,j).h);
            if(blueDist >= orangeDist){
                getPixel(i,j).h = 11;
            }
            else{
                getPixel(i,j).h = 216;
            }
        }
    }
}
void Image::scale(double factor){
    /*Scale the image by a given factor and adjust each pixel as well as possible.*/
    Image temp = *this;
    resize(width()*factor, height()*factor);
    for(unsigned i = 0; i < width(); i++){
        for(unsigned j = 0; j < height(); j++){
            getPixel(i,j) = temp.getPixel(i/factor, j/factor);
        }
    }
}
void Image::scale(unsigned w, unsigned h){
    /*Scale the image to a given width and height. The image will be scaled depending on the lower bound of the width and height ratios.*/
    double factor = min((1.0*w)/width(), (1.0*h)/height());
    scale(factor);
}