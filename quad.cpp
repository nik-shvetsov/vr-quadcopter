#include "quad.h"
#include <cmath>

#include <QDebug>

  Quad::Quad()
  {
      //this->_mass = mass;
      //this->_velocity = velocity;
      //this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

      //this->toggleDefaultVisualizer();
      //this->replot(200,200,1,1);
      //this->setMaterial(GMlib::GMmaterial::Chrome);

      _mass = 1.25;
      //collision sphere (for walls)

      auto colSphere = new GMlib::PSphere<float>(0.3);
      this->_colSphere = colSphere;
      _colSphere->toggleDefaultVisualizer();
      _colSphere->replot(200,200,1,1);
      _colSphere->setMaterial(GMlib::GMmaterial::PolishedRed);
      _colSphere->setVisible(false);
      this->insert(_colSphere);

      auto frame = new Frame(0.1);
      this->_frame = frame;
      this->insert(_frame);

      _d = (frame->getStSize()) / 2.0;

      //motors
      float motorSize = 0.05; //0.5
      auto motor1 = new Motor(motorSize); //10
      _motors.push_back(motor1);
      auto motor2 = new Motor(motorSize);
      _motors.push_back(motor2);
      auto motor3 = new Motor(motorSize);
      _motors.push_back(motor3);
      auto motor4 = new Motor(motorSize);
      _motors.push_back(motor4);

      std::vector<GMlib::Vector<float,3>> translateVecSt;
      translateVecSt.push_back(GMlib::Vector<float,3>(-_d,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,-_d,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(_d,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,_d,0));

      for (int i = 0; i < (int)_motors.size(); i++)
      {
          _motors[i]->toggleDefaultVisualizer();
          _motors[i]->replot(200,200,1,1);
          _motors[i]->setMaterial(GMlib::GMmaterial::Gold);
          _motors[i]->translate(translateVecSt[i]);
          this->insert(_motors[i]);
      }

      std::vector<Rotor*> rotors;

      //initializing rotor parameters

      for (auto mot : _motors)
      {
          rotors.push_back(mot->getRotor());
      }

      for (int i = 0; i < 4; i++)
      {
          if (i%2==0) rotors[i]->setDir(-1);
          else rotors[i]->setDir(1);
          //rotors[i]->setVelocityRot(10);
      }

      //ended object manipulation--------------------------------------------------

      //preparing values

      _angVel = GMlib::Vector<double,3> (0,0,0);
      _dotAngVel = GMlib::Vector<double,3> (0,0,0);
      _torq = GMlib::Vector<double,3> (0,0,0);

      //

      _rotMatr[0][0] = 1.0;
      _rotMatr[0][1] = 0;
      _rotMatr[0][2] = 0;

      _rotMatr[1][0] = 0;
      _rotMatr[1][1] = 1.0;
      _rotMatr[1][2] = 0;

      _rotMatr[2][0] = 0;
      _rotMatr[2][1] = 0;
      _rotMatr[2][2] = 1.0;

      //

      _dotRotMatr[0][0] = 0;
      _dotRotMatr[0][1] = 0;
      _dotRotMatr[0][2] = 0;

      _dotRotMatr[1][0] = 0;
      _dotRotMatr[1][1] = 0;
      _dotRotMatr[1][2] = 0;

      _dotRotMatr[2][0] = 0;
      _dotRotMatr[2][1] = 0;
      _dotRotMatr[2][2] = 0;

      //

      _inMatr[0][0] = 0.047316;
      _inMatr[0][1] = 0;
      _inMatr[0][2] = 0;

      _inMatr[1][0] = 0;
      _inMatr[1][1] = 0.047316;
      _inMatr[1][2] = 0;

      _inMatr[2][0] = 0;
      _inMatr[2][1] = 0;
      _inMatr[2][2] = 0.539632;

      _invInMatr = _inMatr;
      _invInMatr.invert();

      //

      _angVelMatX[0][0] = 0;
      _angVelMatX[0][1] = 0;//-1.0 * _angVel[2];
      _angVelMatX[0][2] = 0;//_angVel[1];

      _angVelMatX[1][0] = 0;//_angVel[2];
      _angVelMatX[1][1] = 0;
      _angVelMatX[1][2] = 0;//_angVel[0];

      _angVelMatX[2][0] = 0;//-1.0 * _angVel[1];
      _angVelMatX[2][1] = 0;//_angVel[0];
      _angVelMatX[2][2] = 0;

      _dS = GMlib::Vector<float, 3>(0, 0, 0);
      _position = this->getPos();

  }

  Quad::~Quad() {}

//methods for setting Quad properties

  double Quad::computeForce(double dt)
  {
      double force = 0;
      for(int i = 0; i < 4; i++)
      {
          force += _Ct * pow(_motors[i]->getAngularVelocity(dt), 2);
      }
      return force;
  }

  std::vector<Motor*> Quad::getMotors()
  {
      return _motors;
  }

  GMlib::Vector<double,3> Quad::calculateTorque(double dt)
  {
      _torq[0] = _d * _Ct * (pow(_motors[1]->getAngularVelocity(dt),2) - pow(_motors[3]->getAngularVelocity(dt),2));
      _torq[1] = _d * _Ct * (pow(_motors[0]->getAngularVelocity(dt),2) - pow(_motors[2]->getAngularVelocity(dt),2));
      _torq[2] = _Cq * (-1 * pow(_motors[0]->getAngularVelocity(dt),2) + pow(_motors[1]->getAngularVelocity(dt),2) -
                        pow(_motors[2]->getAngularVelocity(dt),2) + pow(_motors[3]->getAngularVelocity(dt),2));

      return _torq;
  }

  void Quad::calculateAngVelXMatrix(double dt)
  {
      _rotMatr += _dotRotMatr * dt;

      _angVelMatX[0][0] = 0;
      _angVelMatX[0][1] = -_angVel[2];
      _angVelMatX[0][2] = _angVel[1];

      _angVelMatX[1][0] = _angVel[2];
      _angVelMatX[1][1] = 0;
      _angVelMatX[1][2] = -_angVel[0];

      _angVelMatX[2][0] = -_angVel[1];
      _angVelMatX[2][1] = _angVel[0];
      _angVelMatX[2][2] = 0;

      _dotRotMatr = _rotMatr * _angVelMatX;

      _angVel  += _dotAngVel * dt;

      GMlib::Vector<double,3> ima = _inMatr * _angVel;
      GMlib::Vector<double,3> angima = _angVel ^ ima;

      _dotAngVel = _invInMatr * (calculateTorque(dt) - angima);
  }


  //-----------------------------------------------!!!old

    void Quad::setVelocity(GMlib::Vector<float,3> velocity)
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
        std::vector<Rotor*> rotors;
        for (auto mot : _motors)
        {
            rotors.push_back(mot->getRotor());
        }

        for (auto rot : rotors) //for (auto rot : _rotors) int i = 0; i < 4; i++
        {
            //int direction = rot->getDir() * (-1); //_rotors[i]
            rot->setDir((rot->getDir() * (-1))); //direction
        }
    }

    GMlib::Vector<float,3> Quad::computeFrameDs()
    {
        GMlib::Vector<float,3> vec;

        vec = (_motors[0]->getDs() + _motors[1]->getDs() + _motors[2]->getDs() + _motors[3]->getDs())/4;

        return vec;
    }

    void Quad::computeStep(double dt)
    {
        _dS = (dt * _velocity + 0.5 * dt * dt * _g);
         _velocity = dt*_g;

        /*
        if (this->getPosition()[2] <= _frame->getRadius()) //ad hoc collision with terrain
        {
            _dS[2] = 0;
            _velocity[2] = 0;
        }

        //for skipping threshold
        if (_velocity[2] < 0.01 || _velocity[2] > -0.01)
        {
            _velocity[2] = 0;
        }

         else _velocity = (dt*_velocity + dt*_g);
         */

        //qDebug() << _velocity[0] << "  " << _velocity[1] << "  " << _velocity[2];
    }


  void Quad::localSimulate(double dt)
  {
      auto globalMatrix = getMatrixGlobal();
      globalMatrix.invert();

      double force =  computeForce(dt);
      GMlib::Vector<float,3> step = globalMatrix * _g +  (1.0 / _mass) * GMlib::Vector<float,3>(0,0,force);

      calculateAngVelXMatrix(dt);

      _position = this->getPos();
      _dir = GMlib::Vector<float, 3>(_rotMatr[0][0], _rotMatr[0][1], _rotMatr[0][2]);
      _up = GMlib::Vector<float, 3>(_rotMatr[2][0], _rotMatr[2][1], _rotMatr[2][2]);

      this->set(_position,_dir,_up);

      if ((this->getPosition() + step*dt)[2] > 0) //check for stationary position
      {
          translate(step * dt);
      }

    //-----------------------------------old
    //-----------------------------------1st method
    //computeStep(dt);
    //this->translate(_dS);

    //_frame->translate(computeFrameDs());

    //-------------------------------2nd method
//    //roll pitch yaw
//    computeFlyStep(dt);

//    _pos = this->getPosition();
//    _dir = GMlib::Vector<float, 3>(_rotMatr[0][0], _rotMatr[0][1], _rotMatr[0][2]);
//    _up = GMlib::Vector<float, 3>(_rotMatr[2][0], _rotMatr[2][1], _rotMatr[2][2]);

//    this->set(_pos,_dir,_up);

//    if ((this->getPos() + _dS)[2] > 0 || _dS[2] > 0) //check for stationary position
//    {
//        this->translate(_dS); //translate(V*dt); //for translation
//    }

    //----------------------------------------
  }
