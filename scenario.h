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

  void    keyPressed(const QString& name, QKeyEvent* event);


  //void  initQuad( Quad& quad );

private:

  Quad* _qd {nullptr};

};

#endif // SCENARIO_H
