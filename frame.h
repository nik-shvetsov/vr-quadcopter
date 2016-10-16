#ifndef FRAME_H
#define FRAME_H

#include <parametrics/gmpsphere>
#include <gmParametricsModule>

#include <QDebug>
#include <memory>

class Frame : public GMlib::SceneObject
{
    GM_SCENEOBJECT(Frame)

public:
  Frame(float radius);
  ~Frame();
  float getStSize();

private:
  const float _stSize = 0.5;

  std::vector<std::shared_ptr<GMlib::PCylinder<float>>> _stQuad;
  std::vector<std::shared_ptr<GMlib::PSphere<float>>> _mainsphere;

}; // END class

#endif // FRAME_H
