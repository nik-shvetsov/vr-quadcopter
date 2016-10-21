#include "testball.h"
#include "controller.h"

#include <QDebug>

  Ball::Ball(float radius, double timespawn, GMlib::Point<float,3> position, Controller* controller)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;
      _timespawn = timespawn;
      _endtime = _timespawn + _ttl;

      this->toggleDefaultVisualizer();
      this->setMaterial(GMlib::GMmaterial::Ruby);
      this->replot(50,50,1,1);

      this->translate(position);
  }

  Ball::~Ball() {}

  long Ball::getEndTime()
  {
      return _endtime;
  }

  void Ball::localSimulate(double dt)
  {

  }
