#include "scenario.h"

#include "testtorus.h"
#include "quad.h"
#include "terrain.h"

//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>
#include <QDebug>

//void Scenario::initQuad(Quad& quad)
//{
//  _qd = &quad;
//}

void Scenario::initializeScenario() {

  // Insert a light
  GMlib::Point<GLfloat,3> init_light_pos( 2.0, 4.0, 10 );
  GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                     GMlib::GMcolor::White, init_light_pos );
  light->setAttenuation(0.8, 0.002, 0.0008);
  scene()->insertLight( light, false );

  // Insert Sun
  scene()->insertSun();

  // Default camera parameters
  int init_viewport_size = 600;
  GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

  // Projection cam
  auto proj_rcpair = createRCPair("Projection");
  proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  proj_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -7.0f, 7.0f ) );
  proj_rcpair.camera->enableCulling(false);
  //proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -50.0f, 50.0f ) );
  //proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) ); //orig
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );
  proj_rcpair.renderer->setClearColor(GMlib::GMcolor::Black);

  // Front cam
  auto front_rcpair = createRCPair("Front");
  front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -50.0f, 0.0f ), init_cam_dir, init_cam_up );
  front_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( front_rcpair.camera.get() );
  front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Side cam
  auto side_rcpair = createRCPair("Side");
  side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -50.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
  side_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( side_rcpair.camera.get() );
  side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Top cam
  auto top_rcpair = createRCPair("Top");
  top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
  top_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );


  // Surface visualizers
  //auto surface_visualizer = new GMlib::PSurfNormalsVisualizer<float,3>;
  //auto surface_visualizer = new GMlib::PSurfParamLinesVisualizer<float,3>;

  // Surface
//  auto surface = new TestTorus;
//  surface->toggleDefaultVisualizer();
//  surface->insertVisualizer(surface_visualizer);
//  surface->replot(200,200,1,1);
//  scene()->insert(surface);

//  surface->test01();

  //adding my objects

  //terrain
  auto floor = new Terrain(GMlib::Point<float,3>(-3,-2,0), GMlib::Vector<float,3>(0,10,0), GMlib::Vector<float,3>(6,0,0));
  scene()->insert(floor);

  //quadcopter
  _qd = std::make_shared<Quad>(0.1,1.25,GMlib::Vector<float,3>(0,0,1.0)); //rad, mass, vel
  _qd->translateGlobal(GMlib::Vector<float,3>(0,0,1));
  scene()->insert(_qd.get());


//  auto trajectory = new GMlib::PLine<float>(GMlib::Point<float,3>(0,0,0), GMlib::Point<float,3> (2,2,2));
//  trajectory ->toggleDefaultVisualizer();
//  trajectory->replot(1,1);
//  trajectory ->setMaterial(GMlib::GMmaterial::PolishedRed);
//  scene()->insert(trajectory);
}

void Scenario::cleanupScenario() {

}


void Scenario::moveUp() //uplift actually throttle
{
    //_qd->translate(GMlib::Vector<float,3>(0,0,1)); //placeholder for checking

    GMlib::Vector<float,3> newVelVect = _qd->getVelocity();
    if (newVelVect[2] < 10.0 && newVelVect[2] > -10.0)
    {
        if (newVelVect[2] < 0.0)
        {
            newVelVect[2] = 0.0;
        }

        newVelVect[2] += 0.9;
        newVelVect[1] *= 0.5;
        newVelVect[0] *= 0.5;

        _qd->setVelocity(newVelVect);
    }
    else
    {
        while (newVelVect[2] >= 10.0 || newVelVect[2] <= -10.0)
        {
            newVelVect[2] *= 0.9;
            _qd->setVelocity(newVelVect);
        }
    }

//    GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();
//    for (int i = 0; i < 4; i++)
//    {
//        moveVec[i] += 1.0; //value?
//    }
//    _qd->setMotorThrust(moveVec);

}

/*
void Scenario::moveUp() //for method 2
{
    std::vector<Rotor*> rotors = _qd->getRotors();
    rotors[0]->setVelocityRot(rotors[0]->getVelocityRot()+10);
    rotors[1]->setVelocityRot(rotors[1]->getVelocityRot()+10);
    rotors[2]->setVelocityRot(rotors[2]->getVelocityRot()+10);
    rotors[3]->setVelocityRot(rotors[3]->getVelocityRot()+10);
}
*/

void Scenario::moveDown() //will be used for prototype quadromovment //downfall
{
    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();
    for (int i = 0; i < 4; i++)
    {
        //moveVec[i] -= 1.0; //value?
    }
   // _qd->setMotorThrust(moveVec);
}

void Scenario::moveForward() //pitch
{
    //_qd->switchDirRotors();

    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();
    //moveVec[2] += 2.0; //diametrically opposite motor to the disired direction
    //moveVec[1] -= 0.5;

    //_qd->setMotorThrust(moveVec);
}

void Scenario::moveBackward() //pitch
{
    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();
    //moveVec[1] += 2.0; //diametrically opposite motor to the disired direction
    //moveVec[2] -= 0.5;

    //_qd->setMotorThrust(moveVec);
}

void Scenario::moveRight() //roll
{
    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();
    //moveVec[0] += 2.0; //diametrically opposite motor to the disired direction
    //moveVec[2] -= 0.5;

    //_qd->setMotorThrust(moveVec);
}
void Scenario::moveLeft() //roll
{
    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();
    //moveVec[2] += 2.0; //diametrically opposite motor to the disired direction
    //moveVec[0] -= 0.5;

    //_qd->setMotorThrust(moveVec);
}

//need 2 for yaw
void Scenario::yawLeft() //yaw
{
    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();

    //moveVec[2] *= 1.1;
    //moveVec[0] *= 1.1;

    //moveVec[1] *= 0.1;
    //moveVec[3] *= 0.1;

    //_qd->setMotorThrust(moveVec);
}//

void Scenario::yawRight() //yaw
{
    //GMlib::Vector<float,4> moveVec = _qd->getMotorThrust();

    //moveVec[1] *= 1.1;
    //moveVec[3] *= 1.1;

    //moveVec[0] *= 0.1;
    //moveVec[2] *= 0.1;

    //_qd->setMotorThrust(moveVec);
}

