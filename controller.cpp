#include "controller.h"
#include "scenario.h"
#include "testball.h"

  Controller::Controller(Scenario *scenario, std::shared_ptr<GMlib::Camera> cam)
    {
      this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));
      _followCam = cam;

      //terrain
      _terrain = std::make_shared<Terrain>(GMlib::Point<float,3>(-30,-20,0), GMlib::Vector<float,3>(0,140,0), GMlib::Vector<float,3>(60,0,0));
      //_terrain = std::make_shared<Terrain>(GMlib::Point<float,3>(-7,-5,0), GMlib::Vector<float,3>(0,70,0), GMlib::Vector<float,3>(14,0,0));
      this->insert(_terrain.get());

      //skybox
      _skybox = std::make_shared<Skybox>(1000.0f);
      this->insert(_skybox.get());

      //walls
      auto wall1s = std::make_shared<Wall>(GMlib::Point<float,3>(-7,35,0), GMlib::Vector<float,3>(4,0,0), GMlib::Vector<float,3>(0,0,3));
      auto wall1n = std::make_shared<Wall>(GMlib::Point<float,3>(-7,36,0), GMlib::Vector<float,3>(4,0,0), GMlib::Vector<float,3>(0,0,3));
      auto wall1e = std::make_shared<Wall>(GMlib::Point<float,3>(-7,35,0), GMlib::Vector<float,3>(0,1,0), GMlib::Vector<float,3>(0,0,3));
      auto wall1w = std::make_shared<Wall>(GMlib::Point<float,3>(-3,35,0), GMlib::Vector<float,3>(0,1,0), GMlib::Vector<float,3>(0,0,3));
      auto wall1top = std::make_shared<Wall>(GMlib::Point<float,3>(-7,35,3), GMlib::Vector<float,3>(4,0,0), GMlib::Vector<float,3>(0,1,0));

      auto wall2s = std::make_shared<Wall>(GMlib::Point<float,3>(7,35,0), GMlib::Vector<float,3>(-4,0,0), GMlib::Vector<float,3>(0,0,3));
      auto wall2n = std::make_shared<Wall>(GMlib::Point<float,3>(7,36,0), GMlib::Vector<float,3>(-4,0,0), GMlib::Vector<float,3>(0,0,3));
      auto wall2e = std::make_shared<Wall>(GMlib::Point<float,3>(7,35,0), GMlib::Vector<float,3>(0,1,0), GMlib::Vector<float,3>(0,0,3));
      auto wall2w = std::make_shared<Wall>(GMlib::Point<float,3>(3,35,0), GMlib::Vector<float,3>(0,1,0), GMlib::Vector<float,3>(0,0,3));
      auto wall2top = std::make_shared<Wall>(GMlib::Point<float,3>(7,35,3), GMlib::Vector<float,3>(-4,0,0), GMlib::Vector<float,3>(0,1,0));

      //borders (counts as walls)
      auto wallS = std::make_shared<Wall>(GMlib::Point<float,3>(-30,-20,0), GMlib::Vector<float,3>(0,0,7), GMlib::Vector<float,3>(60,0,0));
      auto wallW = std::make_shared<Wall>(GMlib::Point<float,3>(-30,-20,0), GMlib::Vector<float,3>(0,0,7), GMlib::Vector<float,3>(0,140,0));
      auto wallN = std::make_shared<Wall>(GMlib::Point<float,3>(30,120,0), GMlib::Vector<float,3>(0,0,7), GMlib::Vector<float,3>(-60,0,0));
      auto wallE = std::make_shared<Wall>(GMlib::Point<float,3>(30,120,0), GMlib::Vector<float,3>(0,0,7), GMlib::Vector<float,3>(0,-140,0));


      _walls.emplace_back(wall1s);
      _walls.emplace_back(wall1n);
      _walls.emplace_back(wall1e);
      _walls.emplace_back(wall1w);
      _walls.emplace_back(wall1top);

      _walls.emplace_back(wall2s);
      _walls.emplace_back(wall2n);
      _walls.emplace_back(wall2e);
      _walls.emplace_back(wall2w);
      _walls.emplace_back(wall2top);

      _walls.emplace_back(wallS);
      _walls.emplace_back(wallN);
      _walls.emplace_back(wallE);
      _walls.emplace_back(wallW);

      this->insert(wall1s.get());
      this->insert(wall1n.get());
      this->insert(wall1e.get());
      this->insert(wall1w.get());
      this->insert(wall1top.get());


      this->insert(wall2s.get());
      this->insert(wall2n.get());
      this->insert(wall2e.get());
      this->insert(wall2w.get());
      this->insert(wall2top.get());

      this->insert(wallS.get());
      this->insert(wallN.get());
      this->insert(wallE.get());
      this->insert(wallW.get());


      //quadcopter
      _qd = std::make_shared<Quad>(scenario);
      _qd->translateGlobal(GMlib::Vector<float,3>(0,0,0.5));
      this->insert(_qd.get());

      _qd->insert(_followCam.get());
    }

  Controller::~Controller()
  {
      _followCam.reset();
      _terrain.reset();
      _skybox.reset();
      _qd.reset();
      _walls.clear();
  }

  //ON PRESS CONTROLS----------------------------------------------------------------------

  void Controller::moveUp()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(0.05);
      }
  }
  void Controller::moveDown()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(-0.05);
      }
  }

  void Controller::pitchForward()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(-0.05);
      motors[1]->setPitch(0.05);
  }
  void Controller::pitchBackward()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(0.05);
      motors[1]->setPitch(-0.05);
  }
  void Controller::rollRight()
  {
      auto motors = _qd->getMotors();
      motors[0]->setRoll(-0.05);
      motors[2]->setRoll(0.05);
  }
  void Controller::rollLeft()
  {
     auto motors = _qd->getMotors();
     motors[0]->setRoll(0.05);
     motors[2]->setRoll(-0.05);
  }

  void Controller::yawRight()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(-0.7);
      motors[1]->setYaw(0.7);
      motors[2]->setYaw(-0.7);
      motors[3]->setYaw(0.7);
  }

  void Controller::yawLeft()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(0.7);
      motors[1]->setYaw(-0.7);
      motors[2]->setYaw(0.7);
      motors[3]->setYaw(-0.7);
  }


  //ON RELEASE CONTROLS--------------------------------------------
  void Controller::moveUpReleased()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(0.0);
      }
  }
  void Controller::moveDownReleased()
  {
      auto motors = _qd->getMotors();
      for(int i = 0; i < 4; i++)
      {
          motors[i]->updateThrust(0.0);
      }
  }

  void Controller::pitchForwardReleased()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(0.0);
      motors[1]->setPitch(0.0);
  }
  void Controller::pitchBackwardReleased()
  {
      auto motors = _qd->getMotors();
      motors[3]->setPitch(0.0);
      motors[1]->setPitch(0.0);

  }
  void Controller::rollRightReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setRoll(0.0);
      motors[2]->setRoll(0.0);
  }
  void Controller::rollLeftReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setRoll(0.0);
      motors[2]->setRoll(0.0);
  }
  void Controller::yawLeftReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(0.0);
      motors[1]->setYaw(0.0);
      motors[2]->setYaw(0.0);
      motors[3]->setYaw(0.0);
  }
  void Controller::yawRightReleased()
  {
      auto motors = _qd->getMotors();
      motors[0]->setYaw(0.0);
      motors[1]->setYaw(0.0);
      motors[2]->setYaw(0.0);
      motors[3]->setYaw(0.0);
  }

  void Controller::createBall()
  {
      auto pos = _qd->getPos();
      auto ball = std::make_shared<Ball>(0.05, _timerScene, pos, this);
      this->insert(ball.get());
      _balls.push_back(ball);
  }

  void Controller::removeBall(const std::shared_ptr<Ball> ball)
  {
      remove(ball.get());
      _ballQueue.push(ball);
      _balls.erase(std::find(_balls.begin(), _balls.end(), ball));
  }


  std::shared_ptr<Quad> Controller::getQuad ()
  {
      return _qd;
  }

  void Controller::localSimulate(double dt)
  {
      _timerScene += 1;
      qDebug() << _timerScene;

      if (_balls.size() > 0)
      {
          auto ball = _balls.at(0);
          long time = ball->getEndTime();

          if (_timerScene >= time)
          {
              removeBall(ball);
              qDebug() << "DELETE" << " endtime:" << time;
          }
      }

      if (_timerScene%50 == 0)
      {
          //createBall();
          qDebug() << "Inserting ball every 50 ticks.";
      }

//      auto motors = _qd->getMotors();
//      GMlib::Vector<float,4> tr;
//      for(int i = 0; i < 4; i++)
//      {
//          tr[i] = motors[i]->getThrust();
//      }
//      qDebug() << tr[0] << " " << tr[1] << " " << tr[2] << " " << tr[3];
  }
