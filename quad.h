#ifndef QUAD_H
#define QUAD_H

#include "rotor.h"
#include "motor.h"

#include <parametrics/gmpsphere>
#include <gmParametricsModule>

#include <QDebug>

class Quad : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Quad)

public:
  Quad(double radius, double mass, GMlib::Vector<float,3> velocity);
  ~Quad();

//methods for quad properties

    void setVelocity(const GMlib::Vector<float,3> velocity);
    GMlib::Vector<float,3> getVelocity();
    double getMass();
    GMlib::Vector<float,3> getDs();
    GMlib::Point<float,3> getPosition();

    //trust
    void setMotorThrust(GMlib::Vector<float,4> thrustvec); //&
    GMlib::Vector<float,4> getMotorThrust();

    void switchDirRotors();

    void computeStep(double dt);
    void computeFly(double dt);

protected:
  void localSimulate(double dt);

private:
  GMlib::Vector<float,3> _velocity;
  double _mass;
  GMlib::Vector<float,3> _dS;

  GMlib::Point<float,3> _position;

  std::vector<Motor*> _motors {};
  std::vector<Rotor*> _rotors {};

  //values for movment
  const double _Ct = (86.0e-7);
  const double _Cq = (18.0e-8);
  const GMlib::Vector<float,3> _g = GMlib::Vector<float,3> (0.0, 0.0, -9.81);

  GMlib::SqMatrix<double,3> _inMatr;

}; // END class

#endif // QUAD_H
