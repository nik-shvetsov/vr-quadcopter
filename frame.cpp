#include "frame.h"

#include <QDebug>

  Frame::Frame(double radius)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;










  }

  Frame::~Frame() {}

  void Frame::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //this->translateParent(_dS);
    //computeStep(dt);
  }
