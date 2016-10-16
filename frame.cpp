#include "frame.h"

#include <QDebug>

  Frame::Frame(float radius)
  {
      //_stSize = 0.5; //0.3-0.5


      this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));
      auto mainsphere = std::make_shared<GMlib::PSphere<float>>(radius);
      mainsphere->toggleDefaultVisualizer();
      mainsphere->replot(200,200,1,1);
      mainsphere->setMaterial(GMlib::GMmaterial::BlackRubber);
      _mainsphere.emplace_back(mainsphere);
      this->insert(mainsphere.get());

      auto stSN = std::make_shared<GMlib::PCylinder<float>>(0.01,0.01,_stSize);
      stSN->toggleDefaultVisualizer();
      stSN->replot(200,200,1,1);
      stSN->setMaterial(GMlib::GMmaterial::Plastic);
      stSN->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));

      auto stEW = std::make_shared<GMlib::PCylinder<float>>(0.01,0.01,_stSize);
      stEW->toggleDefaultVisualizer();
      stEW->replot(200,200,1,1);
      stEW->setMaterial(GMlib::GMmaterial::Plastic);
      stEW->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(1,0,0));

      _stQuad.emplace_back(stSN);
      _stQuad.emplace_back(stEW);
      this->insert(stSN.get());
      this->insert(stEW.get());
  }

  Frame::~Frame()
  {
      _stQuad.clear();
  }

  float Frame::getStSize()
  {
      return _stSize;
  }
