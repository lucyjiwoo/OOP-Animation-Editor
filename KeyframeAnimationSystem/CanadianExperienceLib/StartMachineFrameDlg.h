/**
 * @file StartMachineFrameDlg.h
 * @author Jiwoo Jeong
 *
 * StartFrame dialog box
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_STARTMACHINEFRAMEDLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_STARTMACHINEFRAMEDLG_H


class MachineDrawable;

/**
 * StartMachineFrame dialog box
 */
class StartMachineFrameDlg final : public wxDialog
{
private:
    void OnOK(wxCommandEvent& event);

    /// The pointer to the Machine
    std::shared_ptr<MachineDrawable> mMachine;
    /// The start frame of this machine
    int mStartFrame = 0;


public:
    StartMachineFrameDlg(wxWindow* parent,  std::shared_ptr<MachineDrawable> machine, int machinenum);

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_STARTMACHINEFRAMEDLG_H
