#include "rotor.h"

#include <QDebug>

  Rotor::Rotor(int direction)
      :GMlib::PCylinder<float>(0.04*0.1,0.09*0.1,1.5*0.1) //rx,ry,length
  {
      this->_direction = direction; //-1 or 1
      _velocityRot = 0;

  }

  Rotor::~Rotor() {}

//methods for setting Rotor properties

    void Rotor::setVelocityRot(float velocityRot) //velocityRot = motor._thrust
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
      double angle = _velocityRot * _direction * dt;
      rotateGlobal(GMlib::Angle(angle), GMlib::Vector<float,3> (0,0,1));

    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //this->translateParent(_dS);
    //computeStep(dt);
  }
