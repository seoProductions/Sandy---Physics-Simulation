#include "Particle.h"

//I understand that these instructions are long and tedious, I do intend on reducing ambiguity here some time in the future!

/********************************************** PARTICLE *************************************************/

Particle::Particle(int x, int y) : RigidBody(x, y) {
}

//try to move along (velocity) vector, if unable, try to move along the x component of vector, then y component
//if all fails, no movement will be done and updateToFall() will be invoked
void Particle::update() {
    if (idle) return;
    if ((int)getPosition().y > tileGrid->getHeight() - 2)        //Hit the floor TODO FIX SEGFAULT
        idle = true;

    //accelerate
    getVelocity().y += getAcceleration().y * Time::getDeltaTime();
    getVelocity().x += getAcceleration().x * Time::getDeltaTime();
    applyResistance();

    //find magnitude of the velocity vector
    float iterations = sqrtf(getVelocity().x * getVelocity().x
                             + getVelocity().y * getVelocity().y);

    //calculate offset intervals
    float x_offset = getVelocity().x / iterations;      //offset will be applied to the current Position
    float y_offset = getVelocity().y / iterations;      //inorder to test accordingly
    int test_key;

    for (int i = 0; i < iterations; i++)    //particle will test-move for this many intervals
    {
        test_key = tileGrid->getKey(getPosition().x + x_offset,
                                    getPosition().y + y_offset);

        auto test_particle = particles->list.find(test_key);

        //check if another particle is found obstructing our current particles movement along the vector
        if (test_particle            != particles->list.end()
            && test_particle->second != this)
        {
            if (i) return;         //will return if not at first iteration. ALow first iteration only

            if (x_offset != 0)
            {
                --i;               //restart first iteration TODO FIX
                x_offset = 0;
                continue;
            }
            if (y_offset != 0)
            {
                --i;               //restart first iteration
                x_offset = getVelocity().x / iterations;    //restore x_offset just incase we set it to 0
                y_offset = 0;
                continue;
            }

            //movement failed, resort to falling
            updateToFall(i, iterations);
            return;
        }


        //test successful, particle will move
        getPosition().x += x_offset * Time::getDeltaTime();
        getPosition().y += y_offset * Time::getDeltaTime();
        inBounds<float>(getPosition(), *tileGrid);           //check in bounds
    }
}

/************************************************* SAND ****************************************************/


Sand_Particle::Sand_Particle(int x, int y) : Particle(x, y) {
    idle = false;

    //set initial values
    getVelocity().y     = 5.f;
    getAcceleration().y = 1.2f;
    getVelocity().x     = 6.f;
    getAcceleration().x = rand() % 16 - 8;
}

void Sand_Particle::updateToFall(int current_i, int total_i) {

    //first test
    int test_key = tileGrid->getKey(getPosition().x - tileGrid->getPixelsPerTile(),
                                    getPosition().y + tileGrid->getPixelsPerTile());
    int this_key = tileGrid->getKey(getPosition().x,
                                    getPosition().y );

    auto test_left = particles->list.find(test_key);
    auto this_pair = particles->list.find(this_key);

    //check if able to move
    if (test_left            == particles->list.end()
        && test_left->second != this)
    {
        if (test_left->second->getType() ==
            water_t) {    //sand is allowed to move into water, it does so by swapping pointers
            std::swap(test_left, this_pair);
        }

        //test successful, particle will move
        getPosition().x -= tileGrid->getPixelsPerTile();    //TODO TRY WITH DELTA TIME
        getPosition().y += tileGrid->getPixelsPerTile();
        inBounds<float>(getPosition(), *tileGrid);           //check in bounds
        return;
    }

    //second test
    test_key = tileGrid->getKey(getPosition().x + tileGrid->getPixelsPerTile(),
                                getPosition().y + tileGrid->getPixelsPerTile());

    auto test_right = particles->list.find(test_key);

    //check if able to move
    if (test_right            == particles->list.end()
        && test_right->second != this)
    {
        if (test_right->second->getType() ==
            water_t) {    //sand is allowed to move into water, it does so by swapping pointers
            std::swap(test_right, this_pair);
        }

        //test successful, particle will move
        getPosition().x += tileGrid->getPixelsPerTile();    //TODO TRY WITH DELTA TIME
        getPosition().y += tileGrid->getPixelsPerTile();
        inBounds<float>(getPosition(), *tileGrid);           //check in bounds
        return;
    }
    //default case
    idle = true;
}

/************************************************* WATER ***************************************************/


Water_Particle::Water_Particle(int x, int y) : Particle(x, y) {
    idle = false;

    //set initial values
    getVelocity().y     = 7.f;
    getAcceleration().y = 2.f;
}

void Water_Particle::updateToFall(int current_i, int total_i) {

}

Type Sand_Particle::getType()  { return sand_t;  }
Type Water_Particle::getType() { return water_t; }
Type Solid_Particle::getType() { return solid_t; }

