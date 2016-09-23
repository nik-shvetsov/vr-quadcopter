#ifndef SCENARIO_H
#define SCENARIO_H

#include "application/gmlibwrapper.h"

// qt
#include <QObject>


class Controller;

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

  Controller* _controller;

};

#endif // SCENARIO_H
