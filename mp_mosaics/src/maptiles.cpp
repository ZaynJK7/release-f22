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
    vector<Point<3>> tilesAsPoints;
    for (unsigned i = 0; i < theTiles.size(); i++) {
        tilesAsPoints.push_back(convertToXYZ(theTiles.at(i).getAverageColor()));
    }
    KDTree<3> tilesAsTree = KDTree<3>(tilesAsPoints);
    MosaicCanvas* newCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int row = 0; row < theSource.getRows(); row++) {
        for (int column = 0; column < theSource.getColumns(); column++) {
            Point<3> sourcePoint = convertToXYZ(theSource.getRegionColor(row, column));
            Point<3> tileNeeded = tilesAsTree.findNearestNeighbor(sourcePoint);
            for (unsigned i = 0; i < tilesAsPoints.size(); i++) {
                if (tileNeeded == tilesAsPoints.at(i)) {
                    newCanvas->setTile(row, column, &theTiles.at(i));
                    break;
                }
            }
        }
    }
    return newCanvas;
}

