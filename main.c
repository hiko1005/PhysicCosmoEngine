#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void initSpaceObjects(SpaceObject* spaceObject, char* name, double mass, double radius, double x, double y) {
    spaceObject->name = name;
    spaceObject->mass = mass;
    spaceObject->radius = radius;
    spaceObject->position.x = x;
    spaceObject->position.y = y;
    spaceObject->accelerate.x = (rand()%10 + 1);
    spaceObject->accelerate.y = (rand()%10 + 1);
    spaceObject->velocity.x = (rand()%10 + 1);
    spaceObject->velocity.y = (rand()%10 + 1);
}

void createSpaceObjectsList(SpaceObject** SpaceObjects, int n, char** nameList) {
    for (int i = 0; i < n; i++) {
        nameList[i] = SpaceObjects[i]->name;
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

void simulateStep(SpaceObject** spaceObjects, int n) {
    for (int i = 0; i < n; i++) {
        Vector2 netForce = {0, 0};
        for (int j = 0; j < n; j++) {
            if (j == i) continue;

            Vector2 projections = getDistances(spaceObjects[i], spaceObjects[j]);
            double r = sqrt(projections.x*projections.x + projections.y*projections.y);
            double F = calculateGravitationalForce(spaceObjects[i], spaceObjects[j], projections);
            netForce.x += F * (projections.x / r);
            netForce.y += F * (projections.y / r);
        }
        spaceObjects[i]->accelerate.x = netForce.x / spaceObjects[i]->mass;
        spaceObjects[i]->accelerate.y = netForce.y / spaceObjects[i]->mass;
    }

    for (int i = 0; i < n; i++) {
        spaceObjects[i]->velocity.x += spaceObjects[i]->accelerate.x;
        spaceObjects[i]->velocity.y += spaceObjects[i]->accelerate.y;

        spaceObjects[i]->position.x += spaceObjects[i]->velocity.x;
        spaceObjects[i]->position.y += spaceObjects[i]->velocity.y;
    }
}

void checkCollision(SpaceObject** spaceObjects, int n, bool turn_on, bool should_exit) {
    if (!turn_on) return;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            Vector2 r = getDistances(spaceObjects[i], spaceObjects[j]);
            double r_pos = r.x*r.x + r.y*r.y;
            double r_rad = spaceObjects[i]->radius+spaceObjects[j]->radius;
            if (r_rad*r_rad >= r_pos) {
                printf("!!! %s and %s collided!", spaceObjects[i]->name, spaceObjects[j]->name);
                if (should_exit) exit(0);
            }
        }
    }
}

double getScalar(Vector2 vector) {
    return sqrt(vector.x*vector.x+vector.y*vector.y);
}

int main() {
    srand(time(NULL));

    int n = 2;
    SpaceObject Earth;
    initSpaceObjects(&Earth, "Earth", 50, 100, 600, 600);
    SpaceObject Sun;
    initSpaceObjects(&Sun, "Sun", 1000, 20, -500, -600);

    SpaceObject* systemElements[] = {&Earth, &Sun};
    char* nameList[n];
    createSpaceObjectsList(systemElements, n, nameList);

    long long N;
    printf("N = "); scanf("%lld", &N);

    char answ;
    bool turn_on = false, should_exit = false;
    printf("Check collision?(+/-)"); scanf(" %c", &answ);
    if (answ == '+') turn_on = true;
    printf("Should exit on collision?(+/-)"); scanf(" %c", &answ);
    if (answ == '+') should_exit = true;

    for (int i = 0; i < N; i++) {
        simulateStep(systemElements, n);
        checkCollision(systemElements, n, turn_on, should_exit);
        printf("[---------[%-5d]---------]\n", i+1);
        for (int i = 0; i < n; i++) {
            printf("-----\n");
            printf("[%s]:\n", nameList[i]);
            printf("[x, y] : (%-2.5f,%-2.5f)\n", systemElements[i]->position.x, systemElements[i]->position.y);
            printf("[speed] : %.3f\n", getScalar(systemElements[i]->velocity));
            printf("[accelerate] : %.3f\n", getScalar(systemElements[i]->accelerate));
        }
    }
}