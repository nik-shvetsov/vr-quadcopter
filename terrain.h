#ifndef TERRAIN_H
#define TERRAIN_H

#include <gmParametricsModule>

#include <QDebug>

class Terrain : public GMlib::PPlane<float> {
    GM_SCENEOBJECT(Terrain)

public:
  Terrain(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2);
  ~Terrain();

//methods for properties

private:

}; // END class

#endif // TERRAIN_H
