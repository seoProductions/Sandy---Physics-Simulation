
#ifndef SANDY_TILEGRID_H
#define SANDY_TILEGRID_H
#include "SFML/Graphics.hpp"
#include "Tile.h"

#include <algorithm> //std::clamp, std::swap

class TileGrid {
    //dimensions
    unsigned int window_width ;         //window dimensions
    unsigned int window_height;
    unsigned int  window_total;
    unsigned int        width ;         //tile-grid dimensions
    unsigned int        height;
    unsigned int pixelsPerTile;         //Length and width of each Tile

    std::vector<Tile*>    tiles;

public:
    //both TileGrid() and reTile() update member variables and regenerate the vector (tiles)
       TileGrid( int pixelsPerTile, int window_width, int window_height);
    void reTile( int pixelsPerTile, int window_width, int window_height);

    //Change tile color at given position, and return drawable shape
    sf::RectangleShape& getSetSand     (const sf::Vector2f& position); //TODO GIVE ARG TYPE
    sf::RectangleShape& getSetWater    (const sf::Vector2f& position);
    sf::RectangleShape& getSetSolid    (const sf::Vector2f& position);
    sf::RectangleShape& getSetHighlight(const sf::Vector2i& position);

    //getters setters
    unsigned int getKey(int x, int y) const;        //calculate key with given x and y
    unsigned int   getPixelsPerTile() const;
    unsigned int   getHeight_pixels() const;
    unsigned int    getWidth_pixels() const;
    unsigned int    getTotal_pixels() const;        //max possible key
    unsigned int          getHeight() const;
    unsigned int           getWidth() const;

    void setPixelsPerTile(unsigned int pixelsPerTile);

};

/**************************************** HELPER FUNCTIONS ******************************************/


//global function
template<class T>
void inline inBounds(sf::Vector2<T>& vector, const TileGrid& tile_grid) {
    //restrict value
    vector.x = std::clamp<T> (vector.x, 0, (T)tile_grid.getWidth());
    vector.y = std::clamp<T> (vector.y, 0, (T)tile_grid.getHeight());
}

//global function
template<class T>
void inline inBounds_pixels(sf::Vector2<T>& vector, const TileGrid& tile_grid) {
    //restrict value
    vector.x = std::clamp<T> (vector.x, 0, (T)tile_grid.getWidth_pixels());
    vector.y = std::clamp<T> (vector.y, 0, (T)tile_grid.getHeight_pixels());
}

/**************************************** MOUSE LOCAL ********************************************/


//calculate mouse coords relative to Tile Grid, not in pixels.
class Mouse_Local : public sf::Mouse
{
    //keep in memory
    static inline sf::Vector2i local_pos;

public:
    //flash back to java
    static sf::Vector2i getLocalPosition(const sf::Window& relativeTo, const TileGrid& tile_grid)
    {
        local_pos = getPosition(relativeTo);
        inBounds_pixels<int>(local_pos, tile_grid);           //check bounds

        //calculate
        local_pos.x = local_pos.x / tile_grid.getPixelsPerTile();
        local_pos.y = local_pos.y / tile_grid.getPixelsPerTile();
        return local_pos;
    }
};

#endif //SANDY_TILEGRID_H
