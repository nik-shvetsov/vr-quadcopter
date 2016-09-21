#include "skybox.h"
#include "textureloader.h"

#include <QDebug>

  Skybox::Skybox(float radius)
      :GMlib::PSphere<float>(radius)
  {
      TextureLoader texLoader;
      auto skyTexture = texLoader.loadTexture("../../textures/sky.jpg");

      this->insertVisualizer(skyTexture);
      this->replot(50, 50, 1, 1);
      this->setMaterial(GMlib::GMmaterial::Snow);
  }

  Skybox::~Skybox() {}

  void Skybox::localSimulate(double dt)
  {

  }
