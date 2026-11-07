#ifndef PHYSICS_H
#define PHYSICS_H

#define G 100

typedef struct {
    double x;
    double y;
} Vector2;

typedef struct {
    char* name;

    double mass;
    double radius;
    Vector2 position;
    Vector2 accelerate;
    Vector2 velocity;
} SpaceObject;

typedef struct {
    unsigned int ObjectID1;
    unsigned int ObjectID2;
} Collided;

double getVectorModule(Vector2 vector);

void simulateStep(SpaceObject** spaceObjects, int n);

void initSpaceObjects(SpaceObject* spaceObject, char* name, double mass, double radius, double x, double y);

Vector2 getDistances(SpaceObject* obj1, SpaceObject* obj2);

double calculateGravitationalForce(SpaceObject* obj1, SpaceObject* obj2, Vector2 DistaneProjection);

Collided checkCollision(SpaceObject** spaceObjects, int n);


#endif
