#include "motor.h"

#include <QDebug>

  Motor::Motor(double radius, float thrust)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;
      this->_thrust = thrust;
  }

  Motor::~Motor() {}

//methods for setting Rotor properties

    void Motor::setThrust(float thrust)
    {
        _thrust = thrust;
    }

    float Motor::getThrust()
    {
        return _thrust;
    }

  void Motor::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //this->translateParent(_dS);
    //computeStep(dt);
  }
