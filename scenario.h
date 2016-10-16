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

  //QString getHeight();

signals:
    void signUpdateHeight(const QString& text) const;

private:
  //Quad* _qd {nullptr};
  Controller* _controller;
  //std::shared_ptr<Controller> _controller;

};

#endif // SCENARIO_H
