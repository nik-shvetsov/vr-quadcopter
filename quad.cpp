#include "quad.h"
#include <cmath>

#include <QDebug>

  Quad::Quad(Scenario* scenario)
  {
      this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));
      _mass = 1.25;
      _sc = scenario;

      //collision sphere (for walls)

      _colSphere = std::make_shared<GMlib::PSphere<float>>(0.3);
      _colSphere->toggleDefaultVisualizer();
      _colSphere->replot(200,200,1,1);
      _colSphere->setMaterial(GMlib::GMmaterial::PolishedRed);
      _colSphere->setVisible(false);
      this->insert(_colSphere.get());

      _frame = std::make_shared<Frame>(0.1);
      this->insert(_frame.get());

      _d = (_frame->getStSize()) / 2.0;

      //motors
      float motorSize = 0.05; //0.5
      auto motor1 = std::make_shared<Motor>(motorSize); //10
      _motors.emplace_back(motor1); //better than push_back due to r-value ref
      auto motor2 = std::make_shared<Motor>(motorSize);
      _motors.emplace_back(motor2);
      auto motor3 = std::make_shared<Motor>(motorSize);
      _motors.emplace_back(motor3);
      auto motor4 = std::make_shared<Motor>(motorSize);
      _motors.emplace_back(motor4);

      std::vector<GMlib::Vector<float,3>> translateVecSt;
      translateVecSt.push_back(GMlib::Vector<float,3>(-_d,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,-_d,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(_d,0,0));
      translateVecSt.push_back(GMlib::Vector<float,3>(0,_d,0));

      for (int i = 0; i < 4; i++)
      {
          _motors[i]->translate(translateVecSt[i]);
          this->insert(_motors[i].get());
      }

      std::vector<std::shared_ptr<Rotor>> rotors;

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
      _angVelMatX[0][1] = 0;
      _angVelMatX[0][2] = 0;

      _angVelMatX[1][0] = 0;
      _angVelMatX[1][1] = 0;
      _angVelMatX[1][2] = 0;

      _angVelMatX[2][0] = 0;
      _angVelMatX[2][1] = 0;
      _angVelMatX[2][2] = 0;

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

  std::vector<std::shared_ptr<Motor>> Quad::getMotors()
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

      _dotAngVel = _invInMatr * (calculateTorque(dt) - (_angVel ^ (_inMatr * _angVel)));

//      _torq = calculateTorque(dt);
//      _dotAngVel = _invInMatr * (_torq - (_angVel ^ (_inMatr * _angVel)));
//      _angVel += _dotAngVel * dt;

//      _angVelMatX[0][0] = 0;
//      _angVelMatX[0][1] = -_angVel[2];
//      _angVelMatX[0][2] = _angVel[1];

//      _angVelMatX[1][0] = _angVel[2];
//      _angVelMatX[1][1] = 0;
//      _angVelMatX[1][2] = -_angVel[0];

//      _angVelMatX[2][0] = -_angVel[1];
//      _angVelMatX[2][1] = _angVel[0];
//      _angVelMatX[2][2] = 0;

//      _dotRotMatr = _rotMatr * _angVelMatX;
//      _rotMatr += _dotRotMatr * dt;

  }

    double Quad::getMass()
    {
        return _mass;
    }

    GMlib::Point<float,3> Quad::getPosition()
    {
        _position = this->getPos();
        return _position;
    }

    void Quad::switchDirRotors()
    {
        std::vector<std::shared_ptr<Rotor>> rotors;
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

  void Quad::localSimulate(double dt)
  {
      auto globalMatrix = getMatrixGlobal();
      globalMatrix.invert();

      double force =  computeForce(dt);
      GMlib::Vector<float,3> step = globalMatrix * _g +  (1.0f / _mass) * GMlib::Vector<float,3>(0,0,force);

      calculateAngVelXMatrix(dt);

      //_position = this->getPos();
      _dir = GMlib::Vector<float, 3>(_rotMatr[0][0], _rotMatr[0][1], _rotMatr[0][2]);
      _up = GMlib::Vector<float, 3>(_rotMatr[2][0], _rotMatr[2][1], _rotMatr[2][2]);

      this->set(this->getPos(),_dir,_up);

      //if ((this->getPos() + step*dt)[2] > 0) //check for stationary position
      if ((this->getPosition() + step * dt)[2] > 0.099)
      {
        translate(step * dt);

      //qDebug() << this->getPosition()[0] << " " << this->getPosition()[1] << " " << this->getPosition()[2];
      }
      //qDebug() << step[0] << " " << step[1] << " " << step[2];



  }
