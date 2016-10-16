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


      _rotor = std::make_shared<Rotor>(1);

      _rotor->toggleDefaultVisualizer();
      _rotor->replot(200,200,1,1);
      _rotor->setMaterial(GMlib::GMmaterial::BlackRubber);
      _rotor->translateGlobal(GMlib::Vector<float,3>(0,0,radius+upZ));
      _rotor->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));

      this->insert(_rotor.get());
  }

  Motor::~Motor() {}

//methods for setting Motor properties

    std::shared_ptr<Rotor> Motor::getRotor()
    {
      return _rotor;
    }

    float Motor::getAngularVelocity()
    {
        return (_thrust + _velPitch + _velRoll + _velYaw) / dt_stable;
        //return getTotalThrust() / (2.0 * dt_stable);
    }

    void Motor::updateThrust(float thrust)
    {
        if (thrust > 0)
        {
            _thrust += thrust;
        }

        else
        {
            if (_thrust >= thrust) _thrust += thrust;
            else _thrust = min_thrust;
        }

        if (_thrust < min_thrust) _thrust = min_thrust;
        if (_thrust > max_thrust) _thrust = max_thrust;
    }

    void Motor::setPitch(float pitchVal) // 0 0.1 -0.1
    {
        _velPitch = pitchVal;
    }
    void Motor::setRoll(float rollVal) // 0 0.1 -0.1
    {
        _velRoll = rollVal;
    }
    void Motor::setYaw(float yawVal) // 0 0.1 -0.1
    {
        _velYaw = yawVal;
    }

    float Motor::getThrust()
    {
        return _thrust;
    }

    void Motor::setThrust(float thrust) //nnu
    {
        _thrust = thrust;
    }

    void Motor::localSimulate(double dt)
    {
        _rotor->setVelocityRot(this->getThrust()); //velocityRot.rotor = thrust.motor
    }

    //-------------------------------
    float Motor::getTotalThrust()
    {
        float check = (1.25f * g) / (4.0 * 8.6e-6);
        float sq = std::sqrt(check);
        float total = (sq * 2.0 * dt_stable);
        return total;
    }
