#ifndef FRAME_H
#define FRAME_H

#include <parametrics/gmpsphere>
#include <gmParametricsModule>

#include <QDebug>

class Frame : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Frame)

public:
  Frame(double radius);
  ~Frame();

protected:
  void localSimulate(double dt);

private:

}; // END class

#endif // FRAME_H
