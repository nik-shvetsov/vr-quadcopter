#ifndef MOTOR_H
#define MOTOR_H
#include <parametrics/gmpsphere>
#include <gmParametricsModule>

#include <QDebug>

class Motor : public GMlib::PSphere<float> {
    GM_SCENEOBJECT(Motor)

public:
  Motor(double radius, float thrust);
  ~Motor();

//methods for quad properties

    void setThrust(float thrust);
    float getThrust();

protected:
  void localSimulate(double dt);

private:
  float _thrust;

}; // END class
#endif // MOTOR_H
