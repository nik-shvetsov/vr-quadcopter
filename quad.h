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

    void computeStep(double dt);

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBackward();

protected:
  void localSimulate(double dt);

private:
  GMlib::Vector<float,3> _velocity;
  double _mass;
  GMlib::Vector<float,3> _dS;

  std::vector<Motor*> _motors {};
  std::vector<Rotor*> _rotors {};


}; // END class

#endif // QUAD_H
