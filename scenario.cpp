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
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -50.0f, 50.0f ) );
  //proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

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

  //check sphere
//  GMlib::PSphere<float>* sphere = new GMlib::PSphere<float>(1.0);
//  sphere->insertVisualizer(surface_visualizer);
//  sphere->replot(200,200,1,1);
//  sphere->translateGlobal(GMlib::Vector<float,3>(0,0,1.0));
//  sphere->setMaterial(GMlib::GMmaterial::Obsidian);
//  scene()->insert(sphere);




//  GMlib::PLine<float>* cyl = new GMlib::PLine<float>(GMlib::Point<float,3>(0,0,0), GMlib::Vector<float,3>(-7,0,0));
//  cyl->toggleDefaultVisualizer();
//  cyl->replot(0,2);
//  cyl->setColor(GMlib::GMcolor::Black);
//  cyl->translateGlobal(GMlib::Vector<float,3>(-10,0,1.0));
//  cyl->setMaterial(GMlib::GMmaterial::Obsidian);
//  scene()->insert(cyl);

  //terrain
  auto floor = new Terrain
          (GMlib::Point<float,3>(-20,-10,0), GMlib::Vector<float,3>(0,70,0), GMlib::Vector<float,3>(40,0,0));
  scene()->insert(floor);

  //quadcopter
  _qd = new Quad(1,1,GMlib::Vector<float,3>(0,0,1));
  //initQuad(quad);
  _qd->translateGlobal(GMlib::Vector<float,3>(0,0,1));
  //_qd->insert(sphere);
  scene()->insert(_qd);








  //_qd->translateGlobal(GMlib::Vector<float,3>(0,10,5));


//  auto cl1 = new Rotor(GMlib::Vector<float,3>(0,0,0), 1);
//  cl1->toggleDefaultVisualizer();
//  cl1->replot(200,200,1,1);
//  cl1->translateGlobal(GMlib::Vector<float,3>(5,-5,3.0));
//  cl1->setMaterial(GMlib::GMmaterial::Obsidian);
//  cl1->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0,1,0));
//  scene()->insert(cl1);

}

void Scenario::cleanupScenario() {

}
