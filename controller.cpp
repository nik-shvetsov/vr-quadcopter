#include "controller.h"
#include "scenario.h"

  Controller::Controller(Scenario *scenario, std::shared_ptr<GMlib::Camera> cam)
    {
      this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));
      _followCam = cam;

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

      _qd->insert(_followCam.get());

    }

  Controller::~Controller() {}

  //ON PRESS CONTROLS----------------------------------------------------------------------

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
          motors[i]->updateThrust(-0.1);
      }
  }

  void Controller::pitchForward()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(-0.1);
      motors[1]->setPitch(0.1);
  }
  void Controller::pitchBackward()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(0.1);
      motors[1]->setPitch(-0.1);
  }
  void Controller::rollRight()
  {
      auto motors = _qd->getMotors();
      motors[0]->setRoll(-0.1);
      motors[2]->setRoll(0.1);
  }
  void Controller::rollLeft()
  {
     auto motors = _qd->getMotors();
     motors[0]->setRoll(0.1);
     motors[2]->setRoll(-0.1);
  }

  void Controller::yawRight()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(-0.1);
      motors[1]->setYaw(0.1);
      motors[2]->setYaw(-0.1);
      motors[3]->setYaw(0.1);
  }

  void Controller::yawLeft()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(0.1);
      motors[1]->setYaw(-0.1);
      motors[2]->setYaw(0.1);
      motors[3]->setYaw(-0.1);
  }


  //ON RELEASE CONTROLS--------------------------------------------
  void Controller::moveUpReleased()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(0);
      }
  }
  void Controller::moveDownReleased()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(0);
      }
  }

  void Controller::pitchForwardReleased()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(0);
      motors[1]->setPitch(0);
  }
  void Controller::pitchBackwardReleased()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(0);
      motors[1]->setPitch(0);

  }
  void Controller::rollRightReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setRoll(0);
      motors[2]->setRoll(0);
  }
  void Controller::rollLeftReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setRoll(0);
      motors[2]->setRoll(0);
  }
  void Controller::yawLeftReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(0);
      motors[1]->setYaw(0);
      motors[2]->setYaw(0);
      motors[3]->setYaw(0);
  }
  void Controller::yawRightReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(0);
      motors[1]->setYaw(0);
      motors[2]->setYaw(0);
      motors[3]->setYaw(0);
  }


  void Controller::localSimulate(double dt)
  {

//      auto motors = _qd->getMotors();
//      GMlib::Vector<float,4> tr;
//      for(int i = 0; i < 4; i++)
//      {
//          tr[i] = motors[i]->getThrust();
//      }
//      qDebug() << tr[0] << " " << tr[1] << " " << tr[2] << " " << tr[3];

  }
