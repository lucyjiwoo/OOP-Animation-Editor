/**
 * @file ActualMachineSystem.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"

#include "ActualMachineSystem.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"



/**
 * Constructor
 * @param resourcesDir resource directory of this machine system
 */
ActualMachineSystem::ActualMachineSystem(std::wstring resourcesDir)
:mResourcesDir(resourcesDir)
{
    SetMachineNumber(2);
    mMachine->SetMachineSystem(this);
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void ActualMachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{

    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

    mMachine->Draw(graphics);

    graphics->PopState();




}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void ActualMachineSystem::SetMachineNumber(int machine) {

    mMachineNum = machine;
    if(machine == 1)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->Reset();
    }
    else
    {
        MachineCFactory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->Reset();
    }
}


void ActualMachineSystem::SetMachineFrame(int frame)
{
    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }

    for( ; mFrame < frame;  mFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }

    // May need more than these, but you'll figure that out...
    mMachine->SetTime(GetMachineTime());

}