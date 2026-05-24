/**
 * @file MachineDrawable.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"

#include "MachineDrawable.h"
#include <machine-api.h>
#include "Timeline.h"
/**
 * Constructor
 * @param name The name of this machine
 * @param resourcesDir The resources directory for this machine
 */
MachineDrawable::MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir)
: Drawable(name)
{
    MachineSystemFactory factory(resourcesDir);
    std::shared_ptr<IMachineSystem> machine = factory.CreateMachineSystem();
    mMachine = machine;
}

/**
 * Draw the machine drawable
 * @param graphics Graphics context to draw on
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    double scale = 0.5f;
    graphics->PushState();
    graphics->Translate(mPlacedPosition.x,mPlacedPosition.y);
    graphics->Scale(scale,scale);
    mMachine->SetLocation(wxPoint(0,0));
    mMachine->SetMachineFrame(mTimeline->GetCurrentFrame() - mStartFrame);
    mMachine->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Test to see if we clicked on the machine.
 * @param pos Position to test
 * @return True if clicked on
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    int machineX = pos.x - mPlacedPosition.x;
    int machineY = pos.y - mPlacedPosition.y;

    wxPoint machine = GetPosition();
    if (machine.x == machineX && machine.y == machineY){
        return true;
    }
    else{
        return false;
    }

}
/**
 * Set the timeline of this machine
 * @param timeline
 */
void MachineDrawable::SetTimeline(Timeline * timeline){
    timeline->AddChannel(GetAngleChannel());
    mTimeline = timeline;
}
/**
 * Call the machine dialog and show
 * @param mainFrame The window to pop up the dialog box
 */
void MachineDrawable::ShowMachineDlg(wxWindow * mainFrame)
{
    MachineDialog dlg(mainFrame,mMachine);
    if (dlg.ShowModal() == wxID_OK){
    }
}
/**
 * Get the keyframe of this machine
 */
void MachineDrawable::GetKeyframe()
{
    Drawable::GetKeyframe();
    mMachine->SetFrameRate(GetAngleChannel()->GetTimeline()->GetFrameRate());
    mMachine->SetMachineFrame(std::max(GetAngleChannel()->GetTimeline()->GetCurrentFrame()-mStartFrame,0));
}
