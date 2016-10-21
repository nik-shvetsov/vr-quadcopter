#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <parametrics/gmpsphere>
#include <scene/gmsceneobject>
//#include "collision.h"

#include "quad.h"
#include "terrain.h"
#include "skybox.h"
#include "wall.h"
#include "testball.h"
#include "textureloader.h"

#include <QDebug>

#include <memory>
#include <queue>

class Scenario;

class Controller : public GMlib::SceneObject
{
    GM_SCENEOBJECT(Controller)

public:
    Controller(Scenario* scenario, std::shared_ptr<GMlib::Camera> cam);
    ~Controller();

    void moveUp();
    void moveDown();
    void pitchForward();
    void pitchBackward();
    void rollRight();
    void rollLeft();
    void yawRight();
    void yawLeft();

    void moveUpReleased();
    void moveDownReleased();
    void pitchForwardReleased();
    void pitchBackwardReleased();
    void rollRightReleased();
    void rollLeftReleased();
    void yawRightReleased();
    void yawLeftReleased();

    std::shared_ptr<Quad> getQuad();

    void createBall();
    void removeBall(const std::shared_ptr<Ball> ball);


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

    std::vector<std::shared_ptr<Wall>> _walls;

    std::shared_ptr<GMlib::Camera> _followCam;

    Scenario* _scenario;

    long _timerScene = 0;
    //std::vector<Ball*> _traj;
    std::vector<std::shared_ptr<Ball>> _balls;
    std::queue<std::shared_ptr<Ball>> _ballQueue;

    //GMlib::Array<Collision> _arrCols;
    //GMlib::Array<Ball*> _arrBalls;
    //GMlib::Array<PWall*> _arrWalls;
    //GMlib::PBezierSurf<float>* _surf;

}; // END class controller

#endif // CONTROLLER_H
