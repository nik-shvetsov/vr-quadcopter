#ifndef WALL_H
#define WALL_H

#include <gmParametricsModule>

#include <QDebug>

class Wall : public GMlib::PPlane<float> {
    GM_SCENEOBJECT(Wall)

public:
  Wall(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2);
  ~Wall();

//methods for properties

private:

}; // END class



#endif // WALL_H
