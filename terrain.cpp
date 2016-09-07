#include "terrain.h"

#include <QDebug>

  Terrain::Terrain(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2)
      :GMlib::PPlane<float>(p1, v1, v2)
  {
      this->toggleDefaultVisualizer();
      this->replot(200,200,1,1);
      this->setMaterial(GMlib::GMmaterial::Emerald);

  }

  Terrain::~Terrain() {}

  void Terrain::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

    //this->translateParent(_dS);
    //computeStep(dt);
  }
