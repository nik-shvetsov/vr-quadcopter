#include "motor.h"

#include <QDebug>

  Motor::Motor(double radius)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;
      _dS = GMlib::Vector<float,3> (0,0,0);
      _velocity = GMlib::Vector<float,3> (0,0,0);

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

    void Motor::setThrust(float thrust)
    {
        _thrust = thrust;
    }

    float Motor::getThrust()
    {
        return _thrust;
    }

    void Motor::updateThrustUp(float thrust)
    {
        _thrust += thrust;
    }

    void Motor::localSimulate(double dt)
    {
      _rotor->setVelocityRot(this->getThrust()); //velocityRot.rotor = thrust.motor

      //this->computeStep(dt);
      //this->translate(_dS);
    }

//----------------------------------------old methods

    void Motor::setVelocity(GMlib::Vector<float,3> vel)
    {
        _velocity = vel;
    }

    GMlib::Vector<float,3> Motor::getVelocity()
    {
        return _velocity;
    }

    float Motor::getTotalThrust()
    {
        //float force = std::sqrt( (1.25 * 9.81) / (4 * 86.0e-7) );
        //_thrust = force * 2 * adjDt;

        return _thrust;
    }

    void Motor::computeStep(double dt)
    {
        _dS = (dt * _velocity + 0.5 * dt * dt * _g);
        _velocity = dt*_g;
    }

    GMlib::Vector<float,3> Motor::getDs()
    {
        return this->_dS;
    }







