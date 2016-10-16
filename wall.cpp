#include "wall.h"
#include "textureloader.h"

#include <QDebug>

  Wall::Wall(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2)
      :GMlib::PPlane<float>(p1, v1, v2)
  {
      TextureLoader texLoader;
      auto wallTexture = texLoader.loadTexture("../../textures/wall.jpg");
      this->insertVisualizer(wallTexture);
      this->setMaterial(GMlib::GMmaterial::Silver);
      //this->toggleDefaultVisualizer();
      this->replot(50, 50, 1, 1);
  }

  Wall::~Wall() {}
