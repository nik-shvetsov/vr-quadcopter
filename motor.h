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

    Rotor* getRotor();

    //--------------

    void setThrust(float thrust);
    float getThrust();

    void updateThrustUp(float thrust);
    float getAngularVelocity(double dt);



//-----------------------------
    void computeStep(double dt);
    void setVelocity(GMlib::Vector<float,3> vel);
    GMlib::Vector<float,3> getVelocity();

    float getTotalThrust();
    GMlib::Vector<float,3> getDs();

protected:
  void localSimulate(double dt);

private:
  const GMlib::Vector<float,3> _g = GMlib::Vector<float,3> (0.0, 0.0, -9.81); //-9.81
  Rotor* _rotor;

  float _thrust;
  float _velRoll;
  float _velYaw;
  float _velPitch;



  //--------------

  GMlib::Vector<float,3> _velocity;
  GMlib::Vector<float,3> _dS;

}; // END class
#endif // MOTOR_H
