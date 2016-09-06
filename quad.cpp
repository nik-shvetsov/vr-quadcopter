#include "quad.h"

#include <QDebug>

  Quad::Quad(double radius, double mass, GMlib::Vector<float,3> velocity)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;
      this->_mass = mass;
      this->_velocity = velocity;
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



        double checkV1 = _velocity*_velocity + 2.0*(g*_dS); //

        _velocity+=dt*g;


        double checkV2 = _velocity*_velocity; //

        if(checkV2 > 0.0001) //
        { //
            if(checkV1 > 0.0001) //
            {
                _velocity *= std::sqrt(checkV1/checkV2); // vector correction 1
            }
        } //
    }

    void Quad::moveUp()
    {
        GMlib::Vector<float,3> newVelVect = this->getVelocity();
        if (newVelVect[1] < 8.0 && newVelVect[1] > -8.0)
        {
            if (newVelVect[1] < 0.0)
            {
                newVelVect[1] = 0.0;
            }

            newVelVect[1] += 1.0;
            newVelVect[0] *= 0.5;
            //newVelVect[2] *= 0.5;

            this->setVelocity(newVelVect);

//        qDebug() << newVelVect[0];
//        qDebug() << "";
//        qDebug() << newVelVect[1];
//        qDebug() << "";
//        qDebug() << newVelVect[2];
//        qDebug() << "--------------";
        }
        else
        {
            while (newVelVect[1] >= 8.0 || newVelVect[1] <= -8.0)
            {
                newVelVect[1] *= 0.9;
                this->setVelocity(newVelVect);
            }
        }
    }
    void Quad::moveDown()
    {
        GMlib::Vector<float,3> newVelVect = this->getVelocity();
        if (newVelVect[1] < 8.0 && newVelVect[1] > -8.0)
        {
            if (newVelVect[1] > 0.0)
            {
                newVelVect[1] = 0.0;
            }

            newVelVect[1] -= 1.0;
            newVelVect[0] *= 0.5;
            //newVelVect[2] *= 0.5;

            this->setVelocity(newVelVect);
        }
        else
        {
            while (newVelVect[1] >= 8.0 || newVelVect[1] <= -8.0)
            {
                newVelVect[1] *= 0.9;
                this->setVelocity(newVelVect);
            }
        }
    }
    void Quad::moveRight()
    {
        GMlib::Vector<float,3> newVelVect = this->getVelocity();
        if (newVelVect[0] < 8.0 && newVelVect[0] > -8.0)
        {
            if (newVelVect[0] < 0.0)
            {
                newVelVect[0] = 0.0;
            }

            newVelVect[0] += 1.0;
            newVelVect[1] *= 0.5;
            //newVelVect[2] *= 0.5;

            this->setVelocity(newVelVect);
        }
        else
        {
            while (newVelVect[0] >= 8.0 || newVelVect[0] <= -8.0)
            {
                newVelVect[0] *= 0.9;
                this->setVelocity(newVelVect);
            }
        }
    }
    void Quad::moveLeft()
    {
        GMlib::Vector<float,3> newVelVect = this->getVelocity();
        if (newVelVect[0] < 8.0 && newVelVect[0] > -8.0)
        {
            if (newVelVect[0] > 0.0)
            {
                newVelVect[0] = 0.0;
            }

            newVelVect[0] -= 1.0;
            newVelVect[1] *= 0.5;
            //newVelVect[2] *= 0.5;

            this->setVelocity(newVelVect);
        }
        else
        {
            while (newVelVect[0] >= 8.0 || newVelVect[0] <= -8.0)
            {
                newVelVect[0] *= 0.9;
                this->setVelocity(newVelVect);
            }
        }
    }

  void Quad::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);
    this->translateParent(_dS);

    //computeStep(dt);
  }
