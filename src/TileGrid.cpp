#include "TileGrid.h"

TileGrid::TileGrid( int pixelsPerTile, int window_width, int window_height)
{
    //simply re-tile
    reTile(pixelsPerTile, window_width, window_height);
}

void TileGrid::reTile(int pixelsPerTile, int window_width, int window_height) {
    this->pixelsPerTile = pixelsPerTile;

    //dimensions
    this->window_height =  window_height;
    this-> window_width =  window_width ;
    this-> window_total =  window_height *  window_width;
    this->       height =  window_height / pixelsPerTile;
    this->        width =  window_width  / pixelsPerTile;

    tiles.clear();

    //dynamically allocate Tiles into a grid-like manner
    int x, y;
    for (int i = 0; i < width * (height + 1); i++) {
        //using 1 foor loop, calculate x and y
        x = i % width;
        y = i / width;
        tiles.push_back(new Tile(x * pixelsPerTile,         //Tile's will store pixel-coords
                                 y * pixelsPerTile,
                                 pixelsPerTile));
    }
}

sf::RectangleShape& TileGrid::getSetSand(const sf::Vector2f &position) {
    int index = getKey(position.x, position.y);

    int a = tiles.size();

    //change color
    tiles.at(index)->
            Rectangle.setFillColor(Tile::sand_color);

    return tiles.at(index)->
                Rectangle;
}

sf::RectangleShape& TileGrid::getSetWater(const sf::Vector2f &position) {
    int index = getKey(position.x, position.y);

    //change color
    tiles.at(index)->
            Rectangle.setFillColor(Tile::water_color);

    return tiles.at(index)->
            Rectangle;
}

sf::RectangleShape& TileGrid::getSetSolid(const sf::Vector2f &position) {
    int index = getKey(position.x, position.y);

    //change color
    tiles.at(index)->
            Rectangle.setFillColor(Tile::solid_color);

    return tiles.at(index)->
            Rectangle;
}

sf::RectangleShape& TileGrid::getSetHighlight(const sf::Vector2i &position) {
    int index = getKey(position.x, position.y);

    tiles.at(index)->
            Rectangle.setFillColor(Tile::highlight_color);

    return tiles.at(index)->
            Rectangle;
}



/******************************************* GETTERS & SETTERS **********************************************/

unsigned
int TileGrid::getKey(int x, int y) const {
    return y * width + x;
}

unsigned
int TileGrid::getPixelsPerTile() const {
    return pixelsPerTile;
}

unsigned
int TileGrid::getHeight() const {
    return height;
}

unsigned
int TileGrid::getWidth() const {
    return width;
}

unsigned
int TileGrid::getHeight_pixels() const {
    return window_height;
}

unsigned
int TileGrid::getWidth_pixels() const {
    return window_width;
}

unsigned int TileGrid::getTotal_pixels() const {
    return window_total;
}

void TileGrid::setPixelsPerTile(unsigned int pixelsPerTile) {
     TileGrid::pixelsPerTile = pixelsPerTile;
}

