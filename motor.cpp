#include "motor.h"

#include <QDebug>

  Motor::Motor(double radius)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;

      this->toggleDefaultVisualizer();
      this->replot(200,200,1,1);
      this->setMaterial(GMlib::GMmaterial::Gold);

      _thrust = 0;
      _velRoll = 0;
      _velYaw = 0;
      _velPitch = 0;

      float upZ = 0.04 * 0.1;

      auto rotor = new Rotor(1);
      _rotor = rotor;

      _rotor->toggleDefaultVisualizer();
      _rotor->replot(200,200,1,1);
      _rotor->setMaterial(GMlib::GMmaterial::BlackRubber);
      _rotor->translateGlobal(GMlib::Vector<float,3>(0,0,radius+upZ));
      _rotor->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));

      this->insert(_rotor);
  }

  Motor::~Motor() {}

//methods for setting Motor properties

    Rotor* Motor::getRotor()
    {
      return _rotor;
    }

    float Motor::getAngularVelocity(double dt)
    {
        return (_thrust + _velPitch + _velRoll + _velYaw) / dt;
    }

    float Motor::getThrust()
    {
        return _thrust;
    }

    void Motor::setThrust(float thrust)
    {
        _thrust = thrust;
    }

    void Motor::updateThrust(float thrust)
    {
        _thrust += thrust;
        if (_thrust < 0.0) _thrust = 0.0;
    }

    void Motor::speedPitch(float pitchVal) // 0 0.1 -0.1
    {
        _velPitch = pitchVal;
    }
    void Motor::speedRoll(float rollVal) // 0 0.1 -0.1
    {
        _velRoll = rollVal;
    }
    void Motor::speedYaw(float yawVal) // 0 0.1 -0.1
    {
        _velYaw = yawVal;
    }

    float Motor::getTotalThrust()
    {
        float force = std::sqrt( (1.25 * 9.81) / (4 * 86.0e-7) );
        _thrust = force*2*0.2;

        return _thrust;
    }


    void Motor::localSimulate(double dt)
    {
      _rotor->setVelocityRot(this->getThrust()); //velocityRot.rotor = thrust.motor

      //this->computeStep(dt);
      //this->translate(_dS);
    }

//----------------------------------------old methods



