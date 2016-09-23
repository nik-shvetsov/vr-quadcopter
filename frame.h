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
  float getStSize();

private:
  float _stSize;

}; // END class

#endif // FRAME_H
