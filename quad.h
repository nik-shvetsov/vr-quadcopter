#ifndef QUAD_H
#define QUAD_H

#include "rotor.h"
#include "motor.h"
#include "frame.h"

#include <parametrics/gmpsphere>
#include <gmParametricsModule>
#include <scene/gmsceneobject>

#include <QDebug>

class Scenario;


class Quad : public GMlib::SceneObject {
    GM_SCENEOBJECT(Quad)

public:
  Quad(Scenario* scenario);
  ~Quad();

//methods for quad properties

    double getMass();
    std::vector<std::shared_ptr<Motor>> getMotors();

    float computeForce();

    GMlib::Vector<double,3> calculateTorque();
    void calculateAngVelXMatrix(double dt);
    GMlib::Matrix<float,3,3> reintFloatMat();
    void initializeMat();
    void reinitializeMat();

    GMlib::Point<float,3> getPosition();
    void switchDirRotors();
    double getHeight();
    std::shared_ptr<GMlib::PSphere<float>> getColSphere();

protected:
  void localSimulate(double dt) override;

private:
  const double _mass = 1.25;
  float _d;
  double _height;

  Scenario* _sc;

  std::vector<std::shared_ptr<Motor>> _motors;
  std::vector<std::shared_ptr<Rotor>> _rotors;
  //std::vector<Motor*> _motors {}; //in every motor there is a rotor
  std::shared_ptr<Frame> _frame;
  //Frame* _frame;
  std::shared_ptr<GMlib::PSphere<float>> _colSphere;
  //GMlib::PSphere<float>* _colSphere; //collision sphere

  //values for movment
  const double _Ct = (86.0e-7); //thrust coef
  const double _Cq = (18.0e-8); //thrust coef
  const GMlib::Vector<float,3> _g = GMlib::Vector<float,3> (0.0, 0.0, -9.81); //-9.81
  const double dt_stable = 0.016;

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

  //QString label;


}; // END class

#endif // QUAD_H
