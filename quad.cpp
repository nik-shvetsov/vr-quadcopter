#include "quad.h"

#include <QDebug>

  Quad::Quad(double radius, double mass, GMlib::Vector<float,3> velocity)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;
      this->_mass = mass;
      this->_velocity = velocity;

      this->toggleDefaultVisualizer();
      this->replot(200,200,1,1);
      this->setMaterial(GMlib::GMmaterial::Chrome);

      float stSize = 5;

      auto stSN = new GMlib::PCylinder<float>(0.1,0.1,stSize);
      stSN->toggleDefaultVisualizer();
      stSN->replot(200,200,1,1);
      stSN->setMaterial(GMlib::GMmaterial::Plastic);
      this->insert(stSN);
      stSN->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));

      auto stEW = new GMlib::PCylinder<float>(0.1,0.1,stSize);
      stEW->toggleDefaultVisualizer();
      stEW->replot(200,200,1,1);
      stEW->setMaterial(GMlib::GMmaterial::Plastic);
      this->insert(stEW);
      stEW->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(1,0,0));


      float motorSize = 0.5;
      auto motor1 = new Motor(motorSize, 0);
      _motors.push_back(motor1);
      auto motor2 = new Motor(motorSize, 0);
      _motors.push_back(motor2);
      auto motor3 = new Motor(motorSize, 0);
      _motors.push_back(motor3);
      auto motor4 = new Motor(motorSize, 0);
      _motors.push_back(motor4);

      std::vector<GMlib::Vector<float,3>> translateVecSt;
      translateVecSt.push_back(GMlib::Vector<float,3>(-stSize/2,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,-stSize/2,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(stSize/2,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,stSize/2,0));

      for (int i = 0; i < (int)_motors.size(); i++)
      {
          _motors[i]->toggleDefaultVisualizer();
          _motors[i]->replot(200,200,1,1);
          _motors[i]->setMaterial(GMlib::GMmaterial::Gold);
          _motors[i]->translate(translateVecSt[i]);
          this->insert(_motors[i]);
      }


      //rotors
      std::vector<GMlib::Vector<float,3>> translateVecRt;
      translateVecRt.push_back(GMlib::Vector<float,3>(-stSize/2,0,motorSize+0.04));
      translateVecRt.push_back(GMlib::Vector<float,3>(0,-stSize/2,motorSize+0.04));
      translateVecRt.push_back(GMlib::Vector<float,3>(stSize/2,0, motorSize+0.04));
      translateVecRt.push_back(GMlib::Vector<float,3>(0,stSize/2,motorSize+0.04));

      auto rotor1 = new Rotor(1, 1);
      _rotors.push_back(rotor1);
      auto rotor2 = new Rotor(1, 1);
      _rotors.push_back(rotor2);
      auto rotor3 = new Rotor(1, -1);
      _rotors.push_back(rotor3);
      auto rotor4 = new Rotor(1, 1);
      _rotors.push_back(rotor4);


      for (int i = 0; i < (int)_rotors.size(); i++)
      {
          _rotors[i]->toggleDefaultVisualizer();
          _rotors[i]->replot(200,200,1,1);
          _rotors[i]->setMaterial(GMlib::GMmaterial::BlackRubber);
          _rotors[i]->translate(translateVecRt[i]);
          _rotors[i]->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));
          this->insert(_rotors[i]);
      }

      qDebug() << _rotors[0]->getVelocityRot() * _rotors[0]->getDir();

  }

  Quad::~Quad() {}

//methods for setting Quad properties

    void Quad::setVelocity(const GMlib::Vector<float,3> velocity)
    {
        _velocity = velocity;
    }

    GMlib::Vector<float,3> Quad::getVelocity()
    {
        return _velocity;
    }

    double Quad::getMass()
    {
        return _mass;
    }

    GMlib::Vector<float,3> Quad::getDs()
    {
        return _dS;
    }

    void Quad::computeStep(double dt)
    {
        static auto g = GMlib::Vector<float,3>(0,0,-9.8);
        _dS = dt * _velocity + 0.5 * dt * dt * g;
        _velocity+=dt*g;
    }



  void Quad::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //rotate(GMlib::Angle(2), GMlib::Vector<float,3>(0,0,1));

    qDebug() << _dS[0] << " " << _dS[1] << " " << _dS[2];
    computeStep(dt);
    this->translate(_dS);
  }
