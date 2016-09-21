#include "frame.h"

#include <QDebug>

  Frame::Frame(double radius)
      :GMlib::PSphere<float>(radius)
  {
      this->_radius = radius;

      this->toggleDefaultVisualizer();
      this->replot(200,200,1,1);
      this->setMaterial(GMlib::GMmaterial::BlackRubber);

      _stSize = 0.5; //0.3-0.5 //5

      auto stSN = new GMlib::PCylinder<float>(0.01,0.01,_stSize); //0.1
      stSN->toggleDefaultVisualizer();
      stSN->replot(200,200,1,1);
      stSN->setMaterial(GMlib::GMmaterial::Plastic);
      this->insert(stSN);
      stSN->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));

      auto stEW = new GMlib::PCylinder<float>(0.01,0.01,_stSize); //0.1
      stEW->toggleDefaultVisualizer();
      stEW->replot(200,200,1,1);
      stEW->setMaterial(GMlib::GMmaterial::Plastic);
      this->insert(stEW);
      stEW->rotateGlobal(GMlib::Angle(90), GMlib::Vector<float,3>(1,0,0));

      _dS = GMlib::Vector<float,3> (0,0,0);
  }

  Frame::~Frame() {}

  float Frame::getStSize()
  {
      return _stSize;
  }

  void Frame::localSimulate(double dt)
  {
    //rotateGlobal(GMlib::Angle(_dS.getLength()/this->getRadius()), this->getSurfNormal()^_dS);
    //rotateParent(_dS.getLength(), this->getGlobalPos(), this->getSurfNormal()^_dS);

  }
