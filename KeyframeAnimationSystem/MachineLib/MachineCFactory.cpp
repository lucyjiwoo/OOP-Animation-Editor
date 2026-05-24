/**
 * @file MachineCFactory.cpp
 * @author Jiwoo Jeong
 */

#include "pch.h"
#include "MachineCFactory.h"
#include "Machine.h"
#include "Body.h"
#include "Goal.h"
#include "Hamster.h"
#include "Pulley.h"
#include "Conveyor.h"
#include "Curtain.h"
#include "Banner.h"
#include "Basket.h"
/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
MachineCFactory::MachineCFactory(std::wstring resourcesDir)
    :mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * Create a machine
 * @return Pointer to newly created machine
 */
std::shared_ptr<Machine> MachineCFactory::Create()
{
    auto machine = std::make_shared<Machine>(1);

    // Notice: All dimensions are in centimeters and assume
    // the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // The floor
    //
    // The values are chosen so the top of the floor
    // is at Y=0
    //
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    machine->AddComponent(floor);

    const double BeamX = -25;

    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->SetInitialPosition(100, 100);
//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);

    // Basketball 2
    auto basketball2 = std::make_shared<Body>();
    basketball2->Circle(12);
    basketball2->SetImage(mImagesDir + L"/basketball1.png");
    basketball2->SetInitialPosition(-70, 100);
//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball2->SetDynamic();
    basketball2->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball2);

    // Basketball 3
    auto basketball3 = std::make_shared<Body>();
    basketball3->Circle(12);
    basketball3->SetImage(mImagesDir + L"/basketball1.png");
    basketball3->SetInitialPosition(-30, 100);
//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball3->SetDynamic();
    basketball3->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball3);


    // Basketball 4
    auto basketball4 = std::make_shared<Body>();
    basketball4->Circle(12);
    basketball4->SetImage(mImagesDir + L"/basketball1.png");
    basketball4->SetInitialPosition(-110, 100);
//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball4->SetDynamic();
    basketball4->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball4);


    // Basketball 5
    auto basketball5 = std::make_shared<Body>();
    basketball5->Circle(12);
    basketball5->SetImage(mImagesDir + L"/basketball1.png");
    basketball5->SetInitialPosition(-150, 100);
//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball5->SetDynamic();
    basketball5->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball5);


    // Basketball 6
    auto basketball6 = std::make_shared<Body>();
    basketball6->Circle(12);
    basketball6->SetImage(mImagesDir + L"/basketball1.png");
    basketball6->SetInitialPosition(10, 100);

//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball6->SetDynamic();
    basketball6->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball6);

    // Basketball 7
    auto basketball7 = std::make_shared<Body>();
    basketball7->Circle(12);
    basketball7->SetImage(mImagesDir + L"/basketball1.png");
    basketball7->SetInitialPosition(-210, 100);

//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball7->SetDynamic();
    basketball7->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball7);
    // Basketball 8
    auto basketball8 = std::make_shared<Body>();
    basketball8->Circle(12);
    basketball8->SetImage(mImagesDir + L"/basketball1.png");
    basketball8->SetInitialPosition(40, 100);

//    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball8->SetDynamic();
    basketball8->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball8);


    auto goal = std::make_shared<Goal>(mImagesDir);
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);

    //
    // The hamster motor for the second-beam
    //
//    auto hamster = std::make_shared<Hamster>(mImagesDir);
//    hamster->SetPosition(-220, 185);
//    hamster->SetInitiallyRunning(false);      // Initially running
//    hamster->SetSpeed(0.60);
//    machine->AddComponent(hamster);
//
//    auto arm = std::make_shared<Body>();
//    arm->SetInitialPosition(hamster->GetShaftPosition().m_x,hamster->GetShaftPosition().m_y);
//    arm->AddPoint(-7, 10);
//    arm->AddPoint(7, 10);
//    arm->AddPoint(7, -60);
//    arm->AddPoint(-7, -60);
//    arm->SetImage(mImagesDir + L"/arm.png");
//    arm->SetKinematic();
//    machine->AddComponent(arm);
//
//    hamster->GetSource()->AddSink(arm);

    auto hamster1 = std::make_shared<Hamster>(mImagesDir);
    hamster1->SetSpeed(2.0);
    hamster1->SetInitiallyRunning(true);
    machine->AddComponent(hamster1);
    hamster1->SetPosition(150, 150);



    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    conveyor->SetPosition(150,250);
    machine ->AddComponent(conveyor);

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamster1->GetShaftPosition());
    machine->AddComponent(pulley1);

    hamster1->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(30);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyor->GetShaftPosition());
    machine->AddComponent(pulley2);

    pulley1->Drive(pulley2);


    pulley2->GetSource()->AddSink(conveyor);

    auto basket1 = std::make_shared<Basket>(mImagesDir);
    basket1->SetPosition(150,40);
    machine->AddComponent(basket1);



    auto basket2 = std::make_shared<Basket>(mImagesDir);
    basket2->SetPosition(110,40);
    machine->AddComponent(basket2);


    auto basket3 = std::make_shared<Basket>(mImagesDir);
    basket3->SetPosition(70,40);
    machine->AddComponent(basket3);


    auto basket4 = std::make_shared<Basket>(mImagesDir);
    basket4->SetPosition(30,40);
    machine->AddComponent(basket4);

    auto basket5 = std::make_shared<Basket>(mImagesDir);
    basket5->SetPosition(-10,40);
    machine->AddComponent(basket5);

    auto basket6 = std::make_shared<Basket>(mImagesDir);
    basket6->SetPosition(-50,40);
    machine->AddComponent(basket6);

    auto basket7 = std::make_shared<Basket>(mImagesDir);
    basket7->SetPosition(-90,40);
    machine->AddComponent(basket7);

    auto basket8 = std::make_shared<Basket>(mImagesDir);
    basket8->SetPosition(-130,40);
    machine->AddComponent(basket8);

    auto basket9 = std::make_shared<Basket>(mImagesDir);
    basket9->SetPosition(-170,40);
    machine->AddComponent(basket9);


    auto basket10 = std::make_shared<Basket>(mImagesDir);
    basket10->SetPosition(-210,40);
    machine->AddComponent(basket10);


    auto basket11 = std::make_shared<Basket>(mImagesDir);
    basket11->SetPosition(-250,40);
    machine->AddComponent(basket11);

    auto banner = std::make_shared<Banner>(mImagesDir);
    machine->AddComponent(banner);

    auto curtain = std::make_shared<Curtain>(mImagesDir);
    machine->AddComponent(curtain);
    return machine;
}
