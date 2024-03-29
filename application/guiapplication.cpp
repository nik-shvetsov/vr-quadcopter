#include "guiapplication.h"

// local
#include "window.h"
#include "gmlibwrapper.h"

// hidmanager
#include "../hidmanager/defaulthidmanager.h"
#include "../hidmanager/hidmanagertreemodel.h"

// qt
#include <QQmlContext>
#include <QQuickItem>
#include <QStringListModel>
#include <QOpenGLContext>

// stl
#include <cassert>


std::unique_ptr<GuiApplication> GuiApplication::_instance {nullptr};


GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

  assert(!_instance);
  _instance = std::unique_ptr<GuiApplication>(this);


  qRegisterMetaType<HidInputEvent::HidInputParams> ("HidInputEvent::HidInputParams");

  connect( &_window, &Window::sceneGraphInitialized,
           this,     &GuiApplication::onSceneGraphInitialized,
           Qt::DirectConnection );

  connect( &_window, &Window::sceneGraphInvalidated,
           this,     &GuiApplication::onSceneGraphInvalidated,
           Qt::DirectConnection );

  connect( this, &GuiApplication::signOnSceneGraphInitializedDone,
           this, &GuiApplication::afterOnSceneGraphInitialized );

  connect( this, &QGuiApplication::lastWindowClosed,
           this, &QGuiApplication::quit );

  _window.rootContext()->setContextProperty( "scenario", &_scenario);
  _window.rootContext()->setContextProperty( "rc_name_model", &_scenario.rcNameModel() );
  _window.rootContext()->setContextProperty( "hidmanager_model", _hidmanager.getModel() );

  _window.setSource(QUrl("qrc:///qml/main.qml"));

  _window.show();
}

GuiApplication::~GuiApplication() {

  _scenario.stop();
  _window.setPersistentOpenGLContext(false);
  _window.setPersistentSceneGraph(false);
  _window.releaseResources();
  _instance.release();

  qDebug() << "Bye bye ^^, ~~ \"emerge --oneshot life\"";
}

void
GuiApplication::onSceneGraphInitialized() {

  // Print format
  qDebug() << "Surface format: " << QOpenGLContext::currentContext()->format();

  // Init GMlibWrapper
  _scenario.initialize();
  _hidmanager.init(_scenario);
  connect( &_scenario,  &GMlibWrapper::signFrameReady,
           &_window,    &Window::update );

  // Init test scene of the GMlib wrapper
  _scenario.initializeScenario();
  _scenario.prepare();

  emit signOnSceneGraphInitializedDone();
}

void GuiApplication::onSceneGraphInvalidated() {

  _scenario.cleanUp();
}

void
GuiApplication::afterOnSceneGraphInitialized() {

  // Hidmanager setup
  _hidmanager.setupDefaultHidBindings();
  connect( &_window, &Window::signKeyPressed,         &_hidmanager, &StandardHidManager::registerKeyPressEvent );
  connect( &_window, &Window::signKeyReleased,        &_hidmanager, &StandardHidManager::registerKeyReleaseEvent );
  connect( &_window, &Window::signMouseDoubleClicked, &_hidmanager, &StandardHidManager::registerMouseDoubleClickEvent);
  connect( &_window, &Window::signMouseMoved,         &_hidmanager, &StandardHidManager::registerMouseMoveEvent );
  connect( &_window, &Window::signMousePressed,       &_hidmanager, &StandardHidManager::registerMousePressEvent );
  connect( &_window, &Window::signMouseReleased,      &_hidmanager, &StandardHidManager::registerMouseReleaseEvent );
  connect( &_window, &Window::signWheelEventOccurred, &_hidmanager, &StandardHidManager::registerWheelEvent );

  // Handle HID OpenGL actions; needs to have the OGL context bound;
  // QQuickWindow's beforeRendering singnal provides that on a DirectConnection
  connect( &_window, &Window::beforeRendering,        &_hidmanager, &DefaultHidManager::triggerOGLActions,
           Qt::DirectConnection );

  // Register an application close event in the hidmanager;
  // the QWindow must be closed instead of the application being quitted,
  // this is to make sure that GL exits gracefully
  QString ha_id_var_close_app =
  _hidmanager.registerHidAction( "Application", "Quit", "Close application!", &_window, SLOT(close()));
  _hidmanager.registerHidMapping( ha_id_var_close_app, new KeyPressInput( Qt::Key_Q, Qt::ControlModifier) );

  // Connect some application spesific inputs.
  connect( &_hidmanager, &DefaultHidManager::signToggleSimulation,
           &_scenario,   &GMlibWrapper::toggleSimulation );

  connect( &_hidmanager,          SIGNAL(signOpenCloseHidHelp()),
           _window.rootObject(),  SIGNAL(toggleHidBindView()) );

  //colntrols of the quad

    connect( &_hidmanager, &DefaultHidManager::signMoveUp,
             &_scenario, &Scenario::moveUp );

    connect( &_hidmanager, &DefaultHidManager::signMoveDown,
             &_scenario, &Scenario::moveDown );

    connect( &_hidmanager, &DefaultHidManager::signPitchForward,
             &_scenario, &Scenario::pitchForward );

    connect( &_hidmanager, &DefaultHidManager::signPitchBackward,
             &_scenario, &Scenario::pitchBackward );

    connect( &_hidmanager, &DefaultHidManager::signRollRight,
             &_scenario, &Scenario::rollRight );

    connect( &_hidmanager, &DefaultHidManager::signRollLeft,
             &_scenario, &Scenario::rollLeft );

    connect( &_hidmanager, &DefaultHidManager::signYawRight,
             &_scenario, &Scenario::yawRight );

    connect( &_hidmanager, &DefaultHidManager::signYawLeft,
             &_scenario, &Scenario::yawLeft );

    //

    connect( &_hidmanager, &DefaultHidManager::signMoveUpReleased,
             &_scenario, &Scenario::moveUpReleased );

    connect( &_hidmanager, &DefaultHidManager::signMoveDownReleased,
             &_scenario, &Scenario::moveDownReleased );

    connect( &_hidmanager, &DefaultHidManager::signPitchForwardReleased,
             &_scenario, &Scenario::pitchForwardReleased );

    connect( &_hidmanager, &DefaultHidManager::signPitchBackwardReleased,
             &_scenario, &Scenario::pitchBackwardReleased );

    connect( &_hidmanager, &DefaultHidManager::signRollRightReleased,
             &_scenario, &Scenario::rollRightReleased );

    connect( &_hidmanager, &DefaultHidManager::signRollLeftReleased,
             &_scenario, &Scenario::rollLeftReleased );

    connect( &_hidmanager, &DefaultHidManager::signYawRightReleased,
             &_scenario, &Scenario::yawRightReleased );

    connect( &_hidmanager, &DefaultHidManager::signYawLeftReleased,
             &_scenario, &Scenario::yawLeftReleased );

    //---------------

    connect( &_hidmanager, &DefaultHidManager::signLeaveBall,
             this, &GuiApplication::leaveBall, Qt::DirectConnection );


    auto qml_rootobject = _window.rootObject();

    connect( &_scenario, SIGNAL(signUpdateHeight(QString)),
             qml_rootobject, SIGNAL(updateHeight(QString)) );


  // Update RCPair name model
  _scenario.updateRCPairNameModel();

  // Start simulator
  _scenario.start();


}


void GuiApplication::leaveBall()
{
    _scenario.createBall();
}

const GuiApplication& GuiApplication::instance() {  return *_instance; }
