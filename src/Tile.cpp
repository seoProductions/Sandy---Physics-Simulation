
#include "Tile.h"

Tile::Tile(int x, int y, int pixelsPerTile) {
    this->x_pixels = x;
    this->y_pixels = y;

    //setting sf::Shape values
    Rectangle.setSize(sf::Vector2f(pixelsPerTile, pixelsPerTile));
    Rectangle.setPosition(x_pixels, y_pixels);
    Rectangle.setFillColor(background_color);

}
