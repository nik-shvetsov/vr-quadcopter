#ifndef ROTOR_H
#define ROTOR_H

#include <parametrics/gmpsphere>
#include <parametrics/gmpcylinder>
#include <gmParametricsModule>

#include <QDebug>

class Rotor : public GMlib::PCylinder<float> {
    GM_SCENEOBJECT(Rotor)

public:
  Rotor(float velocityRot, int direction);
  ~Rotor();

//methods for quad properties

    void setVelocity(const GMlib::Vector<float,3> velocity);
    GMlib::Vector<float,3> getVelocity();

    void setVelocityRot(float velocity);
    float getVelocityRot();

    void setDir(int direction);
    int getDir();

protected:
  void localSimulate(double dt);

private:
  GMlib::Vector<float,3> _velocity;
  float _velocityRot;
  int _direction;

}; // END class

#endif // ROTOR_H
