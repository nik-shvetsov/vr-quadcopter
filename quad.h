#ifndef QUAD_H
#define QUAD_H

#include "rotor.h"
#include "motor.h"
#include "frame.h"

#include <parametrics/gmpsphere>
#include <gmParametricsModule>

#include <QDebug>

class Scenario;


class Quad : public GMlib::SceneObject {
    GM_SCENEOBJECT(Quad)

public:
  Quad(Scenario* scenario);
  ~Quad();

//methods for quad properties

    double getMass();
    std::vector<Motor*> getMotors();

    double computeForce(double dt);

    GMlib::Vector<double,3> calculateTorque(double dt);
    void calculateAngVelXMatrix(double dt);

    //-------------------------------------------------
    GMlib::Point<float,3> getPosition();

    void switchDirRotors();
    //-------------------------------------------

protected:
  void localSimulate(double dt);

private:
  double _mass;
  float _d;

  Scenario* _sc;

  std::vector<Motor*> _motors {}; //in every motor there is a rotor
  Frame* _frame;
  GMlib::PSphere<float>* _colSphere; //collision sphere

  //values for movment
  const double _Ct = (86.0e-7); //thrust coef
  const double _Cq = (18.0e-8); //thrust coef
  const GMlib::Vector<float,3> _g = GMlib::Vector<float,3> (0.0, 0.0, -9.81); //-9.81

  GMlib::SqMatrix<double,3> _inMatr; //inertia matrix
  GMlib::SqMatrix<double,3> _invInMatr; //inverted inertia matrix
  GMlib::SqMatrix<double,3> _rotMatr; //rotation matrix
  GMlib::SqMatrix<double,3> _dotRotMatr; //dot rotation matrix
  GMlib::SqMatrix<double,3> _angVelMatX;//omegaX



  GMlib::Vector<double,3> _angVel; //omega
  GMlib::Vector<double,3> _dotAngVel; //omegaDot
  GMlib::Vector<double,3> _torq; //torque

  //for set
  GMlib::Point<float,3> _prevposition;
  GMlib::Point<float,3> _position;
  GMlib::Vector<float,3> _dir;
  GMlib::Vector<float,3> _up;


}; // END class

#endif // QUAD_H
