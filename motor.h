#ifndef MOTOR_H
#define MOTOR_H
#include <parametrics/gmpsphere>
#include <gmParametricsModule>
#include "rotor.h"

#include <QDebug>

class Motor : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Motor)

public:
  Motor(double radius);
  ~Motor();

//methods for quad properties

    void setThrust(float thrust);
    float getThrust();
    Rotor* getRotor();
    void computeStep(double dt);

    void setVelocity(GMlib::Vector<float,3> vel);
    GMlib::Vector<float,3> getVelocity();

protected:
  void localSimulate(double dt);

private:
  const GMlib::Vector<float,3> _g = GMlib::Vector<float,3> (0,0,-9.81);
  float _thrust;
  Rotor* _rotor;

  GMlib::Vector<float,3> _velocity;
  GMlib::Vector<float,3> _dS;

}; // END class
#endif // MOTOR_H
