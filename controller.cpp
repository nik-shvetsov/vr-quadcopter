#include "controller.h"
#include "scenario.h"

  Controller::Controller(Scenario *scenario)
    {
      this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

      //terrain
      _terrain = std::make_shared<Terrain>(GMlib::Point<float,3>(-3,-2,0), GMlib::Vector<float,3>(0,10,0), GMlib::Vector<float,3>(6,0,0));
      this->insert(_terrain.get());

      //skybox
      _skybox = std::make_shared<Skybox>(1000.0f);
      this->insert(_skybox.get());

      //walls
      //

      //quadcopter
      _qd = std::make_shared<Quad>(scenario);
      _qd->translateGlobal(GMlib::Vector<float,3>(0,0,1));
      this->insert(_qd.get());

    }

  Controller::~Controller() {}

  void Controller::moveUp()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(0.2);
      }
  }
  void Controller::moveDown()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(-0.2);
      }
  }

  void Controller::localSimulate(double dt)
  {

  }
