using namespace std;
using namespace cs225;
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cassert>
#include <algorithm>
#include <functional>

Image::lighten(){
    for(int i = 0; i < width(); i++){
        for(int j = 0; j < height(); j++){
            getPixel(i,j).l = min(getPixel(i,j).l+0.1, 1);
        }
    }
}
Image::lighten(double amount){
    for(int i = 0; i < width(); i++){
        for(int j = 0; j < height(); j++){
            getPixel(i,j).l = min(getPixel(i,j).l+amount, 1);
        }
    }
}
Image::darken(){
    
}
Image::darken(double amount){
    
}
Image::saturate(){
    
}