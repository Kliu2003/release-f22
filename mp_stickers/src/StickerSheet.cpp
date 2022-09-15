#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
using namespace cs225;
using std::cerr;
using std::endl;
using std::min;
using std::max;
using std::string;
using std::vector;


StickerSheet::StickerSheet(const Image& picture, unsigned max){
    image = new Image(picture);
    stickers = new Image*[max];
    maxCapacity = max;
    currStickerCount = 0;
    X = new unsigned[max];
    Y = new unsigned[max];
}

StickerSheet::~StickerSheet(){
    delete image;
    delete[] stickers;
    delete[] X;
    delete[] Y;
}

StickerSheet::StickerSheet(const StickerSheet &other){
    image = new Image(*other.image);

    stickers = new Image*[other.maxCapacity];

    for(unsigned i = 0; i < other.currStickerCount; i++){
        stickers[i] = other.stickers[i];
    }

    maxCapacity = other.maxCapacity;
    currStickerCount = other.currStickerCount;

    X = new unsigned[other.maxCapacity];
    for(unsigned i = 0; i < other.currStickerCount; i++){
        X[i] = other.X[i];
    }

    Y = new unsigned[other.maxCapacity];
    for(unsigned i = 0; i < other.currStickerCount; i++){
        Y[i] = other.Y[i];
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    delete image;
    delete[] stickers;
    delete[] X;
    delete[] Y;

    image = new Image(*other.image);
    stickers = new Image*[other.maxCapacity];

    for(unsigned i = 0; i < other.currStickerCount; i++){
        stickers[i] = other.stickers[i];
    }

    maxCapacity = other.maxCapacity;
    currStickerCount = other.currStickerCount;

    X = new unsigned[other.maxCapacity];
    for(unsigned i = 0; i < other.currStickerCount; i++){
        X[i] = other.X[i];
    }

    Y = new unsigned[other.maxCapacity];
    for(unsigned i = 0; i < other.currStickerCount; i++){
        Y[i] = other.Y[i];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    Image** temp_stickers = new Image*[maxCapacity];
    unsigned* temp_X = new unsigned[maxCapacity];
    unsigned* temp_Y = new unsigned[maxCapacity];

    for(unsigned i = 0; i < maxCapacity; i++){
        temp_stickers[i] = stickers[i];
        temp_X[i] = X[i];
        temp_Y[i] = Y[i];
    }

    delete[] stickers;
    delete[] X;
    delete[] Y;

    stickers = new Image*[max];
    X = new unsigned[max];
    Y = new unsigned[max];

    unsigned numToAdd = min(max, maxCapacity);

    for(unsigned i = 0; i < numToAdd; i++){
        stickers[i] = temp_stickers[i];
        X[i] = temp_X[i];
        Y[i] = temp_Y[i];
    }
    for (unsigned i = numToAdd; i < max; i++){
		stickers[i] = NULL;
	}
   
    maxCapacity = max;
    currStickerCount = min(currStickerCount, maxCapacity);

    delete[] temp_stickers;
    delete[] temp_X;
    delete[] temp_Y;

}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if(currStickerCount < maxCapacity){
        stickers[currStickerCount] = &sticker;
        X[currStickerCount] = x;
        Y[currStickerCount] = y;
        currStickerCount++;
        return (int)currStickerCount;
    }
    return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index < currStickerCount){
        X[index] = x;
        Y[index] = y;
        return true;
    }
    return false;
}
void StickerSheet::removeSticker(unsigned index){
    for(unsigned i = index; i < currStickerCount; i++){
        stickers[i] = stickers[i+1];
        X[i] = X[i+1];
        Y[i] = Y[i+1];
    }
    stickers[currStickerCount] = NULL;
    X[currStickerCount] = 0;
    Y[currStickerCount] = 0;
    currStickerCount--;
}
Image* StickerSheet::getSticker(unsigned index)const{
    if(index < currStickerCount){
        return stickers[index];
    }
    else{
        return NULL;
    }
}
Image StickerSheet::render()const{
    Image stickeredImage = *image;
    unsigned MaxX = stickeredImage.width();
    unsigned MaxY = stickeredImage.height();
    for(unsigned i = 0; i < currStickerCount; i++){
        MaxX = max(X[i] + stickers[i]->width(), MaxX);
        MaxY = max(Y[i] + stickers[i]->height(), MaxY);
    }
    stickeredImage.resize(MaxX, MaxY);
    for(unsigned i = 0; i < currStickerCount; i++){
        for(unsigned j = X[i]; j < X[i] + stickers[i]->width(); j++){
            for(unsigned k = Y[i]; k < (Y[i] + stickers[i]->height()); k++){
                if(stickers[i]->getPixel(j-X[i], k-Y[i]).a != 0){
                    stickeredImage.getPixel(j, k) = stickers[i]->getPixel(j-X[i], k-Y[i]);
                }
            }
        }
    }
    return stickeredImage;
}