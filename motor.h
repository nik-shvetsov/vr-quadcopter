#ifndef MOTOR_H
#define MOTOR_H
#include <parametrics/gmpsphere>
#include <gmParametricsModule>
#include <memory>
#include "rotor.h"

#include <QDebug>

class Motor : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Motor)

public:
  Motor(double radius);
  ~Motor();

    std::shared_ptr<Rotor> getRotor();

    void setThrust(float thrust);
    float getThrust();

    void updateThrust(float thrust);
    float getAngularVelocity(double dt);

    void setPitch(float pitchVal);
    void setRoll(float rollVal);
    void setYaw(float yawVal);

//-----------------------------
    float getTotalThrust();

protected:
  void localSimulate(double dt) override;

private:
  std::shared_ptr<Rotor> _rotor;

  float _thrust;
  float _velRoll;
  float _velYaw;
  float _velPitch;


}; // END class
#endif // MOTOR_H
