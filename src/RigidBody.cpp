#include "RigidBody.h"

RigidBody::RigidBody(int x, int y) {
    position.x = x;
    position.y = y;
}

sf::Vector2f &RigidBody::getPosition() {
    return position;
}

sf::Vector2f &RigidBody::getVelocity() {
    return velocity;
}

sf::Vector2f &RigidBody::getAcceleration() {
    return acceleration;
}

void RigidBody::setPosition(const sf::Vector2f &position) {
    RigidBody::position = position;
}

void RigidBody::setVelocity(const sf::Vector2f &velocity) {
     RigidBody::velocity = velocity;
}

void RigidBody::setAcceleration(const sf::Vector2f &acceleration) {
     RigidBody::acceleration = acceleration;
}

void RigidBody::applyResistance() {
    getVelocity().y += 2.f * Time::getDeltaTime();      //gravity

    //drag
    //decrease the magnitude of acceleration in the x direction. Operations will depend on the current sign of Velocity.x
    //sneaky trick found here: http://graphics.stanford.edu/~seander/bithacks.html#CopyIntegerSign
    getAcceleration().x -= ((getAcceleration().x > 0) - (getAcceleration().x < 0));
}
