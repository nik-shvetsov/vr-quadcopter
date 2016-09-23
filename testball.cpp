#include "testball.h"

#include <QDebug>

  Ball::Ball(double radius)
      :GMlib::PSphere<float>(radius)
  {

  }

  Ball::~Ball() {}

  void Ball::localSimulate(double dt)
  {
      translate(GMlib::Vector<float,3> (0,0,0.01));
  }
