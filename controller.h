#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <parametrics/gmpsphere>
//#include "collision.h"

#include "quad.h"
#include "terrain.h"
#include "skybox.h"
#include "textureloader.h"

#include <QDebug>

#include <memory>

class Scenario;

class Controller : public GMlib::SceneObject {
    GM_SCENEOBJECT(Controller)

public:
    Controller(Scenario* scenario);
    ~Controller();

    void moveUp();
    void moveDown();

    //void insertQuad(Ball* ball);
    //void insertWall(PWall* wall);

    //void findBBCol(Ball* ball1, Ball* ball2, GMlib::Array<Collision>& cols, double prevX);
    //void findBWCol(Ball* ball, PWall* wall, GMlib::Array<Collision>& cols, double prevX);
    //void handleBBCol(Ball* ball1, Ball* ball2, double dt_part);
    //void handleBWCol(Ball* ball, PWall* wall, double dt_part);


protected:
    void localSimulate(double dt) override;

private:
    std::shared_ptr<Quad> _qd;
    std::shared_ptr<Terrain> _terrain;
    std::shared_ptr<Skybox> _skybox;

    std::shared_ptr<GMlib::Camera> _followCam;

    std::vector<GMlib::Point<float, 3>> _traj;
    Scenario* _scenario;

    //GMlib::Array<Collision> _arrCols;
    //GMlib::Array<Ball*> _arrBalls;
    //GMlib::Array<PWall*> _arrWalls;
    //GMlib::PBezierSurf<float>* _surf;

}; // END class controller

#endif // CONTROLLER_H
