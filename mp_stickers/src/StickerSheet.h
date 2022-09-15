/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <vector>
using namespace cs225;
using std::cerr;
using std::endl;
using std::min;
using std::max;
using std::string;
using std::vector;

class StickerSheet{
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image *getSticker(unsigned index) const;
        Image render() const;
    private:
        Image* image;
        Image** stickers;
        unsigned maxCapacity;
        unsigned currStickerCount;
        unsigned* X;
        unsigned* Y;
};