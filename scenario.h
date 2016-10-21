#ifndef SCENARIO_H
#define SCENARIO_H

#include "application/gmlibwrapper.h"

#include <memory>

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
  void rollRight();
  void rollLeft();
  void pitchForward();
  void pitchBackward();
  void yawRight();
  void yawLeft();

  void moveUpReleased();
  void moveDownReleased();
  void rollRightReleased();
  void rollLeftReleased();
  void pitchForwardReleased();
  void pitchBackwardReleased();
  void yawRightReleased();
  void yawLeftReleased();

  void createBall();

signals:
    void signUpdateHeight(const QString& text) const;

private:
  Controller* _controller;

  //Quad* _qd {nullptr};
  //std::shared_ptr<Controller> _controller;

};

#endif // SCENARIO_H
