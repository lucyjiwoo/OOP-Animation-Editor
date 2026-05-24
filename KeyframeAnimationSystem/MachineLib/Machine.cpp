/**
 * @file Machine.cpp
 * @author Jiwoo Jeong
 */

#include "pch.h"

#include "Machine.h"
#include "Component.h"
#include "MachineCFactory.h"
#include <b2_world.h>
#include "ContactListener.h"



/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Constructor
 * @param machine The number of this machine
 */
Machine::Machine(int machine) : mMachineNumber(machine)
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

}

/**
 * Draw machine
 * @param graphics
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    for (auto component : mComponents){
        component->Draw(graphics);
    }
}
/**
 * Add component into this machine
 * @param component
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
}

/**
 * Reset the machine
 */
void Machine::Reset()
{
    // Create a new world
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));


    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    // Iterate over components and reset/install physics
    for (auto component : mComponents)
    {
        component->Reset();
        component->InstallPhysics(mWorld,mContactListener);
    }

}


/**
 * Update the machine in time
 * @param elapsed Elapsed time in seconds
 */
void Machine::Update(double elapsed)
{
     //Call Update on all of our components so they can advance in time
    for (auto component : mComponents)
        component->Update(elapsed);
    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}
