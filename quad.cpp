#include "quad.h"

#include <QDebug>

  Quad::Quad(double radius, double mass, GMlib::Vector<float,3> velocity)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;
      this->_mass = mass;
      this->_velocity = velocity;

      //this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

      this->toggleDefaultVisualizer();
      this->replot(200,200,1,1);
      this->setMaterial(GMlib::GMmaterial::Chrome);

      float stSize = 0.5; //0.3-0.5 //5

      auto stSN = new GMlib::PCylinder<float>(0.01,0.01,stSize); //0.1
      stSN->toggleDefaultVisualizer();
      stSN->replot(200,200,1,1);
      stSN->setMaterial(GMlib::GMmaterial::Plastic);
      this->insert(stSN);
      stSN->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));

      auto stEW = new GMlib::PCylinder<float>(0.01,0.01,stSize); //0.1
      stEW->toggleDefaultVisualizer();
      stEW->replot(200,200,1,1);
      stEW->setMaterial(GMlib::GMmaterial::Plastic);
      this->insert(stEW);
      stEW->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(1,0,0));


      float motorSize = 0.05; //0.5
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
      float upZ = 0.04 * 0.1;
      std::vector<GMlib::Vector<float,3>> translateVecRt;
      translateVecRt.push_back(GMlib::Vector<float,3>(-stSize/2,0,motorSize+upZ));
      translateVecRt.push_back(GMlib::Vector<float,3>(0,-stSize/2,motorSize+upZ));
      translateVecRt.push_back(GMlib::Vector<float,3>(stSize/2,0, motorSize+upZ));
      translateVecRt.push_back(GMlib::Vector<float,3>(0,stSize/2,motorSize+upZ));

      auto rotor1 = new Rotor(30, -1);
      _rotors.push_back(rotor1);
      auto rotor2 = new Rotor(30, 1);
      _rotors.push_back(rotor2);
      auto rotor3 = new Rotor(30, -1);
      _rotors.push_back(rotor3);
      auto rotor4 = new Rotor(30, 1);
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


      //preparing values
      _inMatr[0][0] = 0.047316;
      _inMatr[0][1] = 0;
      _inMatr[0][2] = 0;

      _inMatr[1][0] = 0;
      _inMatr[1][1] = 0.047316;
      _inMatr[1][2] = 0;

      _inMatr[2][0] = 0;
      _inMatr[2][1] = 0;
      _inMatr[2][2] = 0.539632;

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

    GMlib::Point<float,3> Quad::getPosition()
    {
        _position = this->getPos();
        return _position;
    }

    void Quad::setMotorThrust(GMlib::Vector<float,4> thrustvec) //&
    {
        for (int i = 0; i < 4; i++)
        {
            _motors[i]->setThrust(thrustvec[i]);
        }
    }

    GMlib::Vector<float,4> Quad::getMotorThrust()
    {
        GMlib::Vector<float,4> thrustvec;

        for (int i = 0; i < 4; i++)
        {
            thrustvec[i] = _motors[i]->getThrust();
        }

        return thrustvec;
    }

    void Quad::switchDirRotors()
    {
        for (auto rot : _rotors) //for (auto rot : _rotors) int i = 0; i < 4; i++
        {
            //int direction = rot->getDir() * (-1); //_rotors[i]
            rot->setDir((rot->getDir() * (-1))); //direction
        }
    }

    void Quad::computeStep(double dt)
    {
        static auto g = GMlib::Vector<float,3>(0,0,-1); //-9.8
        _dS = dt * _velocity + 0.5 * dt * dt * g;
        _velocity+=dt*g;
    }

    void Quad::computeFly(double dt)
    {

    }


  void Quad::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //rotate(GMlib::Angle(2), GMlib::Vector<float,3>(0,0,1));

    //qDebug() << _dS[0] << " " << _dS[1] << " " << _dS[2];
    //getPosition();
    //qDebug() << _position[0] << " " << _position[1] << " " << _position[2];

    computeStep(dt);
    this->translate(_dS);

     //set(); //for rotation
    //translate(V*dt); //for translation

  }
