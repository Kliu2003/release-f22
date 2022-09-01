/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
using namespace std;
using namespace cs225;
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cassert>
#include <algorithm>
#include <functional>

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