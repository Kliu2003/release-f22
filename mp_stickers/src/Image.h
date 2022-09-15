/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
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

class Image: public cs225::PNG{
    public:
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);
};