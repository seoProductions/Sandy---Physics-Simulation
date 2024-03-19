#ifndef SANDY_PARTICLE_H
#define SANDY_PARTICLE_H

class Particle;                                 //forward declaration

#include "RigidBody.h"
#include "TileGrid.h"

//enumeration to hold particle info
enum Type {                                     //large scope. Used by main.cpp
    sand_t,
    water_t,
    solid_t
};

//Structure holds a collection of Particles
struct Particles
{
    std::unordered_map                          //map brings performance benefits.
    <int, Particle*> list;                      //note: pointer activates polymorphism


    void new_Grid() {
        for (auto & particle: list)   //generate iterator
            //free memory
            delete particle.second;

        list.clear();
    }
};

class Particle: public RigidBody {
public:
    Particle(int x, int y);
    bool idle;

    static inline                                //TODO MANAGE MEMORY
    Particles* particles;                        //used to test for collision

    static inline
    TileGrid*   tileGrid;                        //used to retrieve dimension info

    //move along the velocity vector and it's components
    //if movement fails, will invoke virtual method updateToFall()
    void update()                         ;
    virtual void updateToFall(int,int) = 0;      //particle specific falling-like movement
    virtual Type getType()             = 0;      //return info of particle
};

class Sand_Particle : public Particle {
public:

    Sand_Particle(int x, int y);

    void updateToFall(int current_i,             //particle specific falling-like movement
                      int total_i)  override;
    Type getType()                  override;    //return sand Type
};

class Water_Particle : public Particle {
public:

    Water_Particle(int x, int y);

    void updateToFall(int current_i,             //particle specific falling-like movement
                      int total_i)  override;
    Type getType()                  override;    //return water Type
};

class Solid_Particle : public Particle {
public:

    Solid_Particle(int x, int y) : Particle(x, y) { idle = true; };

    void updateToFall(int current_i,             //particle specific falling-like movement
                      int total_i)   override { };
    Type getType()                   override;   //return sand Type
};

#ifdef TESTING
/*  For fun, and testing during development :)  */
class Sand_Particle_test : public Sand_Particle {
public:
    Sand_Particle_test(int x, int y) : Sand_Particle(x, y)
    {

        //set initial values
        getAcceleration().y = rand() % 2 - 1;
        getAcceleration().x = rand() % 4 - 2;
        getVelocity().y     = rand() % 4 - 1;
        getVelocity().x     = rand() % 20 - 10;

        if (getAcceleration().x == 0) ++getAcceleration().x;
        if (getAcceleration().y == 0) ++getAcceleration().y;
        if (getVelocity().x == 0) ++getVelocity().x;
        if (getVelocity().y == 0) ++getVelocity().y;
    }
};
#endif //TESTING

#endif //SANDY_PARTICLE_H
