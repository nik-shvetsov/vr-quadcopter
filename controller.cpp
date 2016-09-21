#include "controller.h"

//  Controller::Controller(GMlib::PBezierSurf<float>* surf)
//    {
//        this->toggleDefaultVisualizer();
//        this->replot(30,30,1,1);
//        this->setVisible(false); //hiding controller sphere

//        this->_surf = surf;
//        this->insert(_surf);

//    }

  Controller::Controller()
    {
        this->toggleDefaultVisualizer();
        this->replot(30,30,1,1);
        this->setVisible(false); //hiding controller sphere
    }

  Controller::~Controller() {}

  void Controller::localSimulate (double dt)
  {

  }
