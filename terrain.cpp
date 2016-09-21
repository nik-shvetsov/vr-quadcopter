#include "terrain.h"
#include "textureloader.h"

#include <QDebug>

  Terrain::Terrain(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2)
      :GMlib::PPlane<float>(p1, v1, v2)
  {
      TextureLoader texLoader;
      auto grassTexture = texLoader.loadTexture("../../textures/gr.jpg");

      this->insertVisualizer(grassTexture);
      this->replot(50, 50, 1, 1);
      this->setMaterial(GMlib::GMmaterial::Emerald);
  }

  Terrain::~Terrain() {}

  void Terrain::localSimulate(double dt)
  {

  }
