/**
 * @file HamsterAndConveyorFactory.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "HamsterAndConveyorFactory.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Machine.h"
#include "Body.h"
#include "Pulley.h"
/**
 * Constructor
 * @param machine, imagesDir machine that using this factory, image directory of the factory
 */

HamsterAndConveyorFactory::HamsterAndConveyorFactory(std::shared_ptr<Machine> machine,std::wstring imagesDir)
:mMachine(machine), mImagesDir(imagesDir){
}

/**
 * Create objects of this factory
 * @param hamsterpos, conveyorpos position of hamster and pulley
 */
void HamsterAndConveyorFactory::Create(wxPoint2DDouble hamsterpos, wxPoint2DDouble conveyorpos) {
    mHamster = std::make_shared<Hamster>(mImagesDir);
    mConveyor = std::make_shared<Conveyor>(mImagesDir);
    //create hamster
    mHamster->SetPosition(hamsterpos.m_x, hamsterpos.m_y);
    mHamster->SetInitiallyRunning(false);      // Initially running
    mMachine->AddComponent(mHamster);
    //create conveyor
    mConveyor->SetPosition(conveyorpos.m_x, conveyorpos.m_y);
    mMachine->AddComponent(mConveyor);
    //create two pulley

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(mHamster->GetShaftPosition());
    mMachine->AddComponent(pulley1);

    mHamster->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(10);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(mConveyor->GetShaftPosition());
    mMachine->AddComponent(pulley2);

    pulley1->Drive(pulley2);

    pulley2->GetSource()->AddSink(mConveyor);

}

/**
 * Add Ball on the conveyor
 * @param x x location of the ball on the conveyor
 */
 void HamsterAndConveyorFactory::AddBall(double x) {
    auto ball = std::make_shared<Body>();
    ball->Circle(12);
    ball->SetImage(mImagesDir + L"/ball1.png");
    ball->SetInitialPosition(mConveyor->GetPosition().m_x+x, mConveyor->GetPosition().m_y + 24);
    ball->SetDynamic();
    ball->SetPhysics(1, 0.5, 0.6);
    mMachine->AddComponent(ball);

 }

