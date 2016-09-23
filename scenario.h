#ifndef SCENARIO_H
#define SCENARIO_H

#include "application/gmlibwrapper.h"

// qt
#include <QObject>



class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;

  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void moveForward();
  void moveBackward();
  void yawRight();
  void yawLeft();

  //void  keyPressed(const QString& name, QKeyEvent* event);

private:

  //Quad* _qd {nullptr};
  std::shared_ptr<Quad> _qd;

  //Terrain* _terrain;
  std::shared_ptr<Terrain> _terrain;

  //Skybox* _skybox;
  std::shared_ptr<Skybox> _skybox;

  //std::vector<std::shared_ptr<GMlib::Sphere>> _traj;


};

#endif // SCENARIO_H
