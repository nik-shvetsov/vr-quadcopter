#include "rotor.h"

#include <QDebug>

  Rotor::Rotor(float velocityRot, int direction)
      :GMlib::PCylinder<float>(0.04,0.09,1.5) //rx,ry,length
  {
      this->_velocity = GMlib::Vector<float,3> (0,0,0);
      this->_velocityRot = velocityRot; //0-90
      this->_direction = direction; //-1 or 1
  }

  Rotor::~Rotor() {}

//methods for setting Rotor properties

    void Rotor::setVelocity(const GMlib::Vector<float,3> velocity)
    {
        _velocity = velocity;
    }

    GMlib::Vector<float,3> Rotor::getVelocity()
    {
        return _velocity;
    }

    void Rotor::setVelocityRot(float velocityRot)
    {
        _velocityRot = velocityRot;
    }

    float Rotor::getVelocityRot()
    {
        return _velocityRot;
    }

    void Rotor::setDir(int direction)
    {
        _direction = direction;
    }

    int Rotor::getDir()
    {
        return _direction;
    }


  void Rotor::localSimulate(double dt)
  {
      int angle = _velocityRot * _direction;

      rotateGlobal(GMlib::Angle(angle), GMlib::Vector<float,3> (0,0,1));


    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //this->translateParent(_dS);
    //computeStep(dt);
  }
