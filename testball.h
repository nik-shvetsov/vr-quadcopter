#ifndef TESTBALL_H
#define TESTBALL_H

#include <parametrics/gmpsphere>
#include <gmParametricsModule>
#include <scene/gmsceneobject>
#include <memory>

#include <QDebug>

class Ball : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Ball)

public:
    Ball(double radius, double timespawn, GMlib::Point<float,3> position);
    ~Ball();
    long getEndTime();

protected:
void localSimulate(double dt);

private:

long _timespawn;
const long _ttl = 500;
long _endtime;

}; // END class

#endif // TESTBALL_H
