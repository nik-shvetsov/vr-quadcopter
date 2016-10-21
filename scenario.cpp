#include "scenario.h"

#include "testtorus.h"
#include "testball.h"

#include "controller.h"

#include "quad.h"
#include "terrain.h"
#include "skybox.h"
#include "textureloader.h"


//// hidmanager
//#include "hidmanager/defaulthidmanager.h"


// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>
#include <QDebug>

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
  //proj_rcpair.camera->enableCulling(false);
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
  top_rcpair.camera->translateGlobal(GMlib::Vector<float,3> (0.0f, 0.0f, -45.0f));
  top_rcpair.camera->enableCulling(false);
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  //Follow cam
  auto quad_follow_rcpair = createRCPair("Follow");
  quad_follow_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  quad_follow_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  quad_follow_rcpair.camera->rotateGlobal( GMlib::Angle(-15), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  quad_follow_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -7.0f, 3.0f ) );
  quad_follow_rcpair.camera->enableCulling(false);
  scene()->insertCamera( quad_follow_rcpair.camera.get() );
  quad_follow_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );


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

//  auto ball = new Ball(0.5);
//  ball->toggleDefaultVisualizer();
//  ball->replot(200,200,1,1);
//  scene()->insert(ball);

  //controller
  //_controller = new Controller(this, quad_follow_rcpair.camera);

  //_controller = std::make_shared<Controller>(this, quad_follow_rcpair.camera);
  //scene()->insert(_controller.get());

  _controller = new Controller(this, quad_follow_rcpair.camera);
  scene()->insert(_controller);

  //tests
//  auto trajectory = new GMlib::PLine<float>(GMlib::Point<float,3>(0,0,0), GMlib::Point<float,3> (2,2,2));
//  trajectory ->toggleDefaultVisualizer();
//  trajectory->replot(1,1);
//  trajectory ->setMaterial(GMlib::GMmaterial::PolishedRed);
//  scene()->insert(trajectory);
}

void Scenario::cleanupScenario()
{

}

//QString Scenario::getHeight()
//{
//    return QString::number(_controller->getQuad()->getHeight(),'m',2);
//}

//ON PRESS CONTROLS
void Scenario::moveUp()
{
    _controller->moveUp();
}

void Scenario::moveDown()
{
    _controller->moveDown();
}

void Scenario::pitchForward()
{
    _controller->pitchForward();
}

void Scenario::pitchBackward()
{
    _controller->pitchBackward();
}
void Scenario::rollRight()
{
    _controller->rollRight();
}
void Scenario::rollLeft()
{
    _controller->rollLeft();
}
void Scenario::yawRight()
{
    _controller->yawRight();
}
void Scenario::yawLeft()
{
    _controller->yawLeft();
}

//ON RELEASE CONTROLS
void Scenario::moveUpReleased()
{
    _controller->moveUpReleased();
}
void Scenario::moveDownReleased()
{
    _controller->moveDownReleased();
}
void Scenario::pitchForwardReleased()
{
    _controller->pitchForwardReleased();
}
void Scenario::pitchBackwardReleased()
{
    _controller->pitchBackwardReleased();
}
void Scenario::rollRightReleased()
{
    _controller->rollRightReleased();
}
void Scenario::rollLeftReleased()
{
    _controller->rollLeftReleased();
}
void Scenario::yawRightReleased()
{
    _controller->yawRightReleased();
}
void Scenario::yawLeftReleased()
{
    _controller->yawLeftReleased();
}

void Scenario::createBall()
{
    _controller->createBall();
}
