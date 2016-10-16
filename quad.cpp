#include "quad.h"
#include "scenario.h"
#include <cmath>

#include <QDebug>

Quad::Quad(Scenario* scenario)
{
    this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));
    _sc = scenario;

    //collision sphere (for walls)

    _colSphere = std::make_shared<GMlib::PSphere<float>>(0.29);
    _colSphere->toggleDefaultVisualizer();
    _colSphere->replot(200,200,1,1);
    _colSphere->setMaterial(GMlib::GMmaterial::PolishedRed);
    _colSphere->setVisible(false);
    this->insert(_colSphere.get());


    _frame = std::make_shared<Frame>(0.1);
    this->insert(_frame.get());

    _d = (_frame->getStSize()) / 2.0;

    //motors
    float motorSize = 0.05; //0.5
    auto motor1 = std::make_shared<Motor>(motorSize);
    _motors.emplace_back(motor1); //better than push_back due to r-value ref
    auto motor2 = std::make_shared<Motor>(motorSize);
    _motors.emplace_back(motor2);
    auto motor3 = std::make_shared<Motor>(motorSize);
    _motors.emplace_back(motor3);
    auto motor4 = std::make_shared<Motor>(motorSize);
    _motors.emplace_back(motor4);

    std::vector<GMlib::Vector<float,3>> translateVecSt;
    translateVecSt.emplace_back(GMlib::Vector<float,3>(-_d,0,0));
    translateVecSt.emplace_back(GMlib::Vector<float,3>(0,-_d,0));
    translateVecSt.emplace_back(GMlib::Vector<float,3>(_d,0,0));
    translateVecSt.emplace_back(GMlib::Vector<float,3>(0,_d,0));

    for (int i = 0; i < 4; i++)
    {
        _motors[i]->translate(translateVecSt[i]);
        this->insert(_motors[i].get());
    }

    _rotors.clear();

    //initializing rotor parameters

    for (auto mot : _motors)
    {
        _rotors.emplace_back(mot->getRotor());
    }

    for (int i = 0; i < 4; i++)
    {
        if (i%2==0) _rotors[i]->setDir(-1);
        else _rotors[i]->setDir(1);
        //rotors[i]->setVelocityRot(10);
    }

    //ended object manipulation--------------------------------------------------

    //preparing values

    initializeMat();


    _inMatr[0][0] = 0.047316;
    _inMatr[0][1] = 0;
    _inMatr[0][2] = 0;

    _inMatr[1][0] = 0;
    _inMatr[1][1] = 0.047316;
    _inMatr[1][2] = 0;

    _inMatr[2][0] = 0;
    _inMatr[2][1] = 0;
    _inMatr[2][2] = 0.539632;

    _invInMatr = _inMatr;
    _invInMatr.invert();
}

Quad::~Quad()
{
    _frame.reset();
    _motors.clear();
    _rotors.clear();

}

//methods for setting Quad properties

float Quad::computeForce()
{
    float force = 0.0;
    for(int i = 0; i < 4; i++)
    {
        force += _Ct * std::pow(_motors[i]->getAngularVelocity(), 2);
    }
    return force;
}

std::vector<std::shared_ptr<Motor>> Quad::getMotors()
{
    return _motors;
}

GMlib::Vector<double,3> Quad::calculateTorque()
{
    _torq[0] = _d * _Ct * (std::pow(_motors[1]->getAngularVelocity(),2) - std::pow(_motors[3]->getAngularVelocity(),2));
    _torq[1] = _d * _Ct * (std::pow(_motors[0]->getAngularVelocity(),2) - std::pow(_motors[2]->getAngularVelocity(),2));
    _torq[2] = _Cq * (-1 * std::pow(_motors[0]->getAngularVelocity(),2) + std::pow(_motors[1]->getAngularVelocity(),2) -
            std::pow(_motors[2]->getAngularVelocity(),2) + std::pow(_motors[3]->getAngularVelocity(),2));

    return _torq;
}

void Quad::calculateAngVelXMatrix(double dt)
{
    _rotMatr += _dotRotMatr * dt;

    _angVelMatX[0][0] = 0;
    _angVelMatX[0][1] = -_angVel[2];
    _angVelMatX[0][2] = _angVel[1];

    _angVelMatX[1][0] = _angVel[2];
    _angVelMatX[1][1] = 0;
    _angVelMatX[1][2] = -_angVel[0];

    _angVelMatX[2][0] = -_angVel[1];
    _angVelMatX[2][1] = _angVel[0];
    _angVelMatX[2][2] = 0;

    _dotRotMatr = _rotMatr * _angVelMatX;

    _angVel  += _dotAngVel * dt;

    _dotAngVel = _invInMatr * (calculateTorque() - (_angVel ^ (_inMatr * _angVel)));
}

void Quad::initializeMat()
{
    _angVel = GMlib::Vector<double,3> (0.0,0.0,0.0);
    _dotAngVel = GMlib::Vector<double,3> (0.0,0.0,0.0);
    _torq = GMlib::Vector<double,3> (0.0,0.0,0.0);

    _rotMatr[0][0] = 1.0;
    _rotMatr[0][1] = 0.0;
    _rotMatr[0][2] = 0.0;

    _rotMatr[1][0] = 0.0;
    _rotMatr[1][1] = 1.0;
    _rotMatr[1][2] = 0.0;

    _rotMatr[2][0] = 0.0;
    _rotMatr[2][1] = 0.0;
    _rotMatr[2][2] = 1.0;

    _dotRotMatr[0][0] = 0;
    _dotRotMatr[0][1] = 0;
    _dotRotMatr[0][2] = 0;

    _dotRotMatr[1][0] = 0;
    _dotRotMatr[1][1] = 0;
    _dotRotMatr[1][2] = 0;

    _dotRotMatr[2][0] = 0;
    _dotRotMatr[2][1] = 0;
    _dotRotMatr[2][2] = 0;

    _angVelMatX[0][0] = 0;
    _angVelMatX[0][1] = 0;
    _angVelMatX[0][2] = 0;

    _angVelMatX[1][0] = 0;
    _angVelMatX[1][1] = 0;
    _angVelMatX[1][2] = 0;

    _angVelMatX[2][0] = 0;
    _angVelMatX[2][1] = 0;
    _angVelMatX[2][2] = 0;
}

void Quad::reinitializeMat()
{

}


double Quad::getMass()
{
    return _mass;
}

double Quad::getHeight()
{
    return _height;
}

GMlib::Point<float,3> Quad::getPosition()
{
    _position = this->getPos();
    return _position;
}

void Quad::switchDirRotors()
{
    std::vector<std::shared_ptr<Rotor>> rotors;
    for (auto mot : _motors)
    {
        rotors.emplace_back(mot->getRotor());
    }

    for (auto rot : rotors) //for (auto rot : _rotors) int i = 0; i < 4; i++
    {
        //int direction = rot->getDir() * (-1); //_rotors[i]
        rot->setDir((rot->getDir() * (-1))); //direction
    }
}

std::shared_ptr<GMlib::PSphere<float>> Quad::getColSphere()
{
    return _colSphere;
}

void Quad::localSimulate(double dt)
{
    auto globalMatrix = getMatrixGlobal();
    globalMatrix.invert();

    float force = computeForce();

    GMlib::Vector<float,3> step = globalMatrix * _g +  (1.0 / _mass) * GMlib::Vector<float,3>(0,0,force);



    //_position = this->getPos();

    if ((getPos() + step * dt)[2] < 0.099)
    {
        initializeMat();
    }

    calculateAngVelXMatrix(dt);

    _dir = GMlib::Vector<float, 3>(_rotMatr[0][0], _rotMatr[0][1], _rotMatr[0][2]);
    _up = GMlib::Vector<float, 3>(_rotMatr[2][0], _rotMatr[2][1], _rotMatr[2][2]);

    set(getPos(),_dir,_up);


    //height display
    _height = getPos()(2);
    QString heightString = "H: " + QString::number(_height,'g',3) + " m";
    emit _sc->signUpdateHeight(heightString);
    //--------------------------------------------

    //if ((this->getPos() + step*dt)[2] > 0) //check for stationary position
    if ((getPos() + step * dt)[2] > 0.099)
    {
        translate(step * dt);
        //qDebug() << step[0] << " " << step[1] << " " << step[2];
    }
    else
    {
        set(GMlib::Point<float, 3>(getPos()(0), getPos()(1), 0.09), _dir, _up);
    }





}
