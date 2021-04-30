#include "particle.h"


void Particle::move(float dx, float dy){

    set_x(position().x + dx);

    set_y(position().y + dy);

}
