#include "quad.h"
#include <cmath>

#include <QDebug>

  Quad::Quad(double mass, GMlib::Vector<float,3> velocity)

  {
      this->_mass = mass;
      this->_velocity = velocity;
      //this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

//      this->toggleDefaultVisualizer();
//      this->replot(200,200,1,1);
//      this->setMaterial(GMlib::GMmaterial::Chrome);

      auto frame = new Frame(0.1);
      this->_frame = frame;
      this->insert(_frame);

      _stSize = _frame->getStSize();
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
      translateVecSt.push_back(GMlib::Vector<float,3>(-_stSize/2,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,-_stSize/2,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(_stSize/2,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,_stSize/2,0));

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

      _dS = GMlib::Vector<float, 3>(0, 0, 0);
      _d = _stSize / 2.0;


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

      //

      _invInMatr = _inMatr;
      _invInMatr.invert();

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

      _angVel = GMlib::Vector<double,3> (0,0,0);
      _dotAngVel = GMlib::Vector<double,3> (0,0,0);
      _torq = GMlib::Vector<double,3> (0,0,0);

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

  }

  Quad::~Quad() {}

//methods for setting Quad properties

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

    std::vector<Motor*> Quad::getMotors()
    {
        return _motors;
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

//    void Quad::setMotorThrust(GMlib::Vector<float,4> thrustvec) //&
//    {
//        for (int i = 0; i < 4; i++)
//        {
//            _motors[i]->setThrust(thrustvec[i]);
//        }
//    }

//    GMlib::Vector<float,4> Quad::getMotorThrust()
//    {
//        GMlib::Vector<float,4> thrustvec;

//        for (int i = 0; i < 4; i++)
//        {
//            thrustvec[i] = _motors[i]->getThrust();
//        }

//        return thrustvec;
//    }

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

        qDebug() << _velocity[0] << "  " << _velocity[1] << "  " << _velocity[2];
    }

    void Quad::computeFlyStep(double dt)
    {
        /*//------------------------------------
        float thrustSum = 0;
        GMlib::Vector<float,4> w;
        GMlib::Vector<float,4> w_pow;
        for (int i = 0; i < 4; i++)
        {
            w[i] = _rotors[i]->getVelocityRot();
            w_pow[i] = pow(_rotors[i]->getVelocityRot(),2);
            thrustSum += w_pow[i];
        }
        //qDebug() << w_pow[0] << " " << w_pow[1] << " " << w_pow[2] << " " << w_pow[3] << " ";
        thrustSum *= _Ct;
        //qDebug() << thrustSum;
        //------------------------------------

       auto globalMatrix = this->getMatrixGlobal();
       globalMatrix.invert();

       auto gravLVec = globalMatrix *_g;
       auto localF = GMlib::Vector<float,3>(0,0,thrustSum);

       _dS = gravLVec + (1.0/this->getMass()) * localF;

       _rotMatr += _dotRotMatr*dt;

       _angVelMatX[0][0] = 0;
       _angVelMatX[0][1] = -1*_angVel[2];
       _angVelMatX[0][2] = _angVel[1];

       _angVelMatX[1][0] = _angVel[2];
       _angVelMatX[1][1] = 0;
       _angVelMatX[1][2] = -1*_angVel[0];

       _angVelMatX[2][0] = -1*_angVel[1];
       _angVelMatX[2][1] = _angVel[0];
       _angVelMatX[2][2] = 0;

       _dotRotMatr = _rotMatr * _angVelMatX;

       _angVel += _dotAngVel*dt;

       _dotAngVel = _invInMatr * (_torq - (_angVel ^ (_inMatr*_angVel)));

       _torq[0] = _d * _Ct * (pow(_rotors[1]->getVelocityRot(),2)-(_rotors[3]->getVelocityRot(),2));
       _torq[1] = _d * _Ct * (pow(_rotors[0]->getVelocityRot(),2)-pow(_rotors[2]->getVelocityRot(),2));
       _torq[2] = _Cq * (-1 * pow(_rotors[0]->getVelocityRot(),2) + pow(_rotors[1]->getVelocityRot(),2) -
               pow(_rotors[2]->getVelocityRot(),2) + pow(_rotors[3]->getVelocityRot(),2));j*/
    }


  void Quad::localSimulate(double dt)
  {
    computeStep(dt);
    this->translate(_dS);

    //-------------------------------2nd method
//    //roll pitch yaw
//    computeFlyStep(dt);

//    _pos = this->getPosition();
//    _dir = GMlib::Vector<float, 3>(_rotMatr[0][0], _rotMatr[0][1], _rotMatr[0][2]);
//    _up = GMlib::Vector<float, 3>(_rotMatr[2][0], _rotMatr[2][1], _rotMatr[2][2]);

//    this->set(_pos,_dir,_up);

//    if ((this->getPos() + _dS*dt)[2] > 0 || _dS[2] > 0) //check for stationary position
//    {
//        this->translate(_dS*dt); //translate(V*dt); //for translation
//    }

    //----------------------------------------
  }
