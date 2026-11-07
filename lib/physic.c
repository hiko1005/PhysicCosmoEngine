#include <math.h>
#include "../include/physic/physic.h"

double getVectorModule(Vector2 vector) {
    return sqrt(vector.x*vector.x+vector.y*vector.y);
}

void initSpaceObjects(SpaceObject* spaceObject, char* name, double mass, double radius, double x, double y) {
    spaceObject->name = name;
    spaceObject->mass = mass;
    spaceObject->radius = radius;
    spaceObject->position.x = x;
    spaceObject->position.y = y;
    spaceObject->accelerate.x = 0;
    spaceObject->accelerate.y = 0;
    spaceObject->velocity.x = 0;
    spaceObject->velocity.y = 0;
}

void simulateStep(SpaceObject** spaceObjects, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) continue;

            Vector2 projections = getDistances(spaceObjects[i], spaceObjects[j]);
            double r = sqrt(projections.x*projections.x + projections.y*projections.y);
            double F = calculateGravitationalForce(spaceObjects[i], spaceObjects[j], projections);
            spaceObjects[i]->accelerate.x = F * (projections.x / r) / spaceObjects[i]->mass; // netforce / mass = F/m = a;
            spaceObjects[i]->accelerate.y = F * (projections.y / r) / spaceObjects[i]->mass; // projection / r = cos => F * cos = 
        }
    }

    for (int i = 0; i < n; i++) {
        spaceObjects[i]->velocity.x += spaceObjects[i]->accelerate.x;
        spaceObjects[i]->velocity.y += spaceObjects[i]->accelerate.y;

        spaceObjects[i]->position.x += spaceObjects[i]->velocity.x;
        spaceObjects[i]->position.y += spaceObjects[i]->velocity.y;
    }
}

Vector2 getDistances(SpaceObject* obj1, SpaceObject* obj2) {
    double dx = obj2->position.x - obj1->position.x;
    double dy = obj2->position.y - obj1->position.y;

    Vector2 projections = {dx, dy};

    return projections;
}

double calculateGravitationalForce(SpaceObject* obj1, SpaceObject* obj2, Vector2 DistaneProjection) {
    double r = DistaneProjection.x*DistaneProjection.x + DistaneProjection.y*DistaneProjection.y;

    return (G * obj1->mass * obj2->mass)/r;
}

Collided checkCollision(SpaceObject** spaceObjects, int n) {
    Collided collided;
    collided.ObjectID1 = -1;
    collided.ObjectID2 = -1;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            Vector2 projections = getDistances(spaceObjects[i], spaceObjects[j]);
            double distance = getVectorModule(projections);
            double radiusesSum = spaceObjects[i]->radius+spaceObjects[j]->radius;

            if (radiusesSum*radiusesSum >= distance) {
                collided.ObjectID1 = i;
                collided.ObjectID2 = j;
                return collided;
            }
        }
    }

    return collided;
}