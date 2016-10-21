#ifndef ROTOR_H
#define ROTOR_H

#include <parametrics/gmpsphere>
#include <parametrics/gmpcylinder>
#include <gmParametricsModule>

#include <QDebug>

class Rotor : public GMlib::PCylinder<float> {
    GM_SCENEOBJECT(Rotor)

public:
  Rotor(int direction);
  ~Rotor();

//methods for quad properties

    void setVelocityRot(float velocity);
    float getVelocityRot();

    void setDir(int direction);
    int getDir();

protected:
  void localSimulate(double dt) override;

private:

  float _velocityRot; //angular velocity value
  int _direction;// -1 or 1: counter-clockwise and clockwise

}; // END class

#endif // ROTOR_H
