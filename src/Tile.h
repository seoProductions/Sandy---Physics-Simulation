
#ifndef SANDY_TILE_H
#define SANDY_TILE_H
#include "SFML/Graphics.hpp"


class Tile {
public:
    //color
    static const inline sf::Color sand_color  = sf::Color::Yellow;
    static const inline sf::Color water_color = sf::Color::Blue;
    static const inline sf::Color solid_color = sf::Color::White;
    static const inline sf::Color highlight_color  = sf::Color(70, 70, 70);
    static const inline sf::Color background_color = sf::Color(40, 40, 40);


    int x_pixels;                       //position in pixels
    int y_pixels;
    sf::RectangleShape Rectangle;       //will initialize to a square

    Tile(int x, int y, int pixelsPerTile);
};


#endif //SANDY_TILE_H
