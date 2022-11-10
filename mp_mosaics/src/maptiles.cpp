/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* res = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    vector<Point<3>>averagePoints;
    map<Point<3>, int> tilemap;
    for(unsigned i = 0; i < theTiles.size(); i++){
        averagePoints.push_back(convertToXYZ(theTiles[i].getAverageColor()));
        tilemap.insert(pair<Point<3>, int>(convertToXYZ(theTiles[i].getAverageColor()), i));
    }

    KDTree<3> tree = KDTree<3>(averagePoints);
    for(int i = 0; i < theSource.getRows(); i++){
        for(int j = 0; j < theSource.getColumns(); j++){
            res->setTile(i, j, &theTiles[tilemap[tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i,j)))]]);
        }
    }
    return res;
}

