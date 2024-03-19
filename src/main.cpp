#include <SFML/Graphics.hpp>

//#define TESTING
#ifdef TESTING
  #include <iostream>
  #include "Time.h"
#endif

#include <iterator>
#include "Particle.h"
#include "TileGrid.h"

const int PIXELS_PER_TILE = 10;

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1400, 800), "Sandy 1.0");
    window.setMouseCursorVisible(false);

    enum selected_particle_type {                        //track which particle to instantiate
        sand,
        water,
        solid,
        eraser
    };
    int selected_particle = sand;                        //will change with keyboard events

    //   collection of particles used by main window
    Particles particles;
    //   will also be used by Particle class
    Particle::particles = &particles;
              particles.new_Grid();

    //   tile grid used by the game loop
    TileGrid tileGrid
              ( PIXELS_PER_TILE, window.getSize().x, window.getSize().y);
    //   will also be used by Particle class
    Particle::tileGrid  =  &tileGrid;

    srand(time(NULL));

    while (window.isOpen()) {

        //poll events
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        //keyboard events
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) //1
            selected_particle = sand;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) //2
            selected_particle = water;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) //3
            selected_particle = solid;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) //4
            selected_particle = eraser;

        window.clear(Tile::background_color);

        //Create a tile-highlight effect when the mouse hover over any tile
        sf::Vector2i   hover_pos = Mouse_Local::getLocalPosition(window, tileGrid);
        inBounds<int> (hover_pos, tileGrid);    //avoid out of range TODO FIX

#ifdef TESTING
        //insert particles at mouse pos
        particles.list.insert({tileGrid.getKey(
                                    hover_pos.x,
                                    hover_pos.y),
                               new Sand_Particle(
                                    hover_pos.x,
                                    hover_pos.y)});

        std::cout << Time::getDeltaTime() << "\n";
#endif
        window.draw(tileGrid.getSetHighlight(hover_pos));


        //mouse
        if (sf::Mouse::isButtonPressed(             //click
                sf::Mouse::Button::Left)) {

            //retrieve mouse info
            int x = Mouse_Local::getLocalPosition(window, tileGrid).x ;
            int y = Mouse_Local::getLocalPosition(window, tileGrid).y ;

            int key = tileGrid.getKey(x, y);

            //If the user clicks on an existing particle (in the window), ignore
            //Otherwise, spawn in the particle
            if (particles.list.find(key) == particles.list.end()
                || selected_particle == eraser) {
                switch (selected_particle) {
                    case sand:
                        particles.list.insert({key, new Sand_Particle(x, y)});
                        break;
                    case water:
                        particles.list.insert({key, new Water_Particle(x, y)});
                        break;
                    case solid:
                        particles.list.insert({key, new Solid_Particle(x, y)});
                        break;
                    case eraser:
                        if (key < tileGrid.getTotal_pixels()) //TODO FIX OUT OF RANGE
                            particles.list.erase(key);
                }
            }
        }

        //generate iterator
        std::unordered_map
        <int, Particle*>::iterator
                          particle = particles.list.begin();

        //Draw

        for (; particle != particles.list.end(); ) {
            // Test each particle type
            switch (particle->second->getType()) {
                case sand_t:
                    window.draw(tileGrid.getSetSand(
                                particle->second->getPosition()));  //update specific Tile and return the drawable tile
                    break;
                case water_t:
                    window.draw(tileGrid.getSetWater(
                            particle->second->getPosition()));      //update specific Tile and return the drawable tile
                    break;
                case solid_t:
                    window.draw(tileGrid.getSetSolid(
                            particle->second->getPosition()));      //update specific Tile and return the drawable tile
                    break;
            }

            //Actions to perform if particle is in motion.
            //Create new keys-value pairs, delete the old one
            //same pointer, different key
            if (!particle->second->idle) {

                //use particle data to calculate old and new key
                unsigned
                int key_old = particle->first;

                particle->second->update();

                unsigned
                int key_new = tileGrid.getKey(particle->second->getPosition().x,
                                              particle->second->getPosition().y);

                if (key_new == key_old)         //different key only
                    ++particle;
                else {
                    //insert new key with the same particle pointer. Erase the old one
                    particles.list.insert({key_new, particle->second});
                    particle = particles.list.erase (particle);
                }
            } else
                ++particle;         //idle, move on to the next particle
        }

        window.display();
    }
}

