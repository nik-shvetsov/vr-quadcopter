#ifndef TESTBALL_H
#define TESTBALL_H

#include <parametrics/gmpsphere>
#include <gmParametricsModule>

#include <QDebug>

class Ball : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Ball)

public:
  Ball(double radius);
  ~Ball();

protected:
void localSimulate(double dt);

private:

}; // END class

#endif // TESTBALL_H
