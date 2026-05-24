/**
 * @file StartMachineFrameDlg.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>

#include "StartMachineFrameDlg.h"
#include "MachineDrawable.h"


/**
 * Constructor
 * @param parent The parent window we will center in
 * @param machine Pointer to the timeline we are editing
 * @param machinenum The machine number
 */
StartMachineFrameDlg::StartMachineFrameDlg(wxWindow* parent, std::shared_ptr<MachineDrawable> machine, int machinenum) : mMachine(machine)
{
    if (machinenum ==1){
        wxXmlResource::Get()->LoadDialog(this, parent, L"StartMachineFrameDialog1");
        mStartFrame = machine->GetStartFrame();
        Bind(wxEVT_BUTTON, &StartMachineFrameDlg::OnOK, this, wxID_OK);

        auto startFramesCtrl = XRCCTRL(*this, "StartFrameMachine1", wxTextCtrl);
        wxIntegerValidator<int> numFramesValidator(&mStartFrame);
        numFramesValidator.SetRange(1, 10000);
        startFramesCtrl->SetValidator(numFramesValidator);

    }

    else{
        wxXmlResource::Get()->LoadDialog(this, parent, L"StartMachineFrameDialog2");
        mStartFrame = machine->GetStartFrame();
        Bind(wxEVT_BUTTON, &StartMachineFrameDlg::OnOK, this, wxID_OK);

        auto startFramesCtrl = XRCCTRL(*this, "StartFrameMachine2", wxTextCtrl);
        wxIntegerValidator<int> numFramesValidator(&mStartFrame);
        numFramesValidator.SetRange(1, 10000);
        startFramesCtrl->SetValidator(numFramesValidator);
    }

}

/**
 * Handle an OK button press
 * @param event Button event
 */
void StartMachineFrameDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mMachine->SetStartFrame(mStartFrame);
        EndModal(wxID_OK);
    }
}