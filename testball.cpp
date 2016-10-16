#include "testball.h"


#include <QDebug>

  Ball::Ball(double radius, double timespawn, GMlib::Point<float,3> position)
      :GMlib::PSphere<float>(radius)
  {
      _timespawn = timespawn;
      _endtime = _timespawn + _ttl;

      this->_radius = radius;
      this->toggleDefaultVisualizer();
      this->replot(50,50,1,1);
      this->setMaterial(GMlib::GMmaterial::Ruby);
      //this->translate(position);
  }

  Ball::~Ball() {}

  long Ball::getEndTime()
  {
      return _endtime;
  }

  void Ball::localSimulate(double dt)
  {

  }
