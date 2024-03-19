#ifndef SANDY_RIGIDBODY_H
#define SANDY_RIGIDBODY_H
#include <SFML/Graphics.hpp>
#include "Time.h"

class RigidBody {

    //default float values are 0, according to c++
    sf::Vector2f position;      //x, y
    sf::Vector2f velocity;      //pixels per second
    sf::Vector2f acceleration;  //for forces applied, mass of 1 will be assumed

public:
    RigidBody(int x, int y);

    void applyResistance();     //invoked to apply gravity and drag forces

    //getters setters
    sf::Vector2f &getPosition();
    sf::Vector2f &getVelocity();
    sf::Vector2f &getAcceleration();

    void setPosition    (const sf::Vector2f &position);
    void setVelocity    (const sf::Vector2f &velocity);
    void setAcceleration(const sf::Vector2f &acceleration);

};


#endif //SANDY_RIGIDBODY_H
