#ifndef TESTBALL_H
#define TESTBALL_H

#include <parametrics/gmpsphere>
#include <gmParametricsModule>
#include <scene/gmsceneobject>
#include <memory>

#include <QDebug>

class Controller;

class Ball : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Ball)

public:
    Ball(float radius, double timespawn, GMlib::Point<float,3> position, Controller* controller);
    ~Ball();
    long getEndTime();

protected:
void localSimulate(double dt) override;

private:

long _timespawn;
const long _ttl = 3000;
long _endtime;

}; // END class

#endif // TESTBALL_H
