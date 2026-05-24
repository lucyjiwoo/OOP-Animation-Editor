/**
 * @file MachineDrawable.h
 * @author Jiwoo Jeong
 *
 * An Adapter class that display machine
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include <machine-api.h>

#include "Drawable.h"

/**
 * An Adapter class that display machine
 */

class MachineDrawable : public Drawable {
private:
    /// The machine that we are drawing
    std::shared_ptr<IMachineSystem> mMachine;
    /// The timeline of this machine
    Timeline * mTimeline;
    /// The start frame of this machine
    int mStartFrame = 0;

public:
    MachineDrawable(const std::wstring& name, const std::wstring& resourcesDir);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;
    /**
     * Set machinenumber of this machine
     * @param number
     */
    void SetMachineNumber(int number){
        mMachine->SetMachineNumber(number);
    }
    /**
     * Get machinenumber of this machine
     * @return  number machine number
     */
    int GetMachineNumber(){
        return mMachine->GetMachineNumber();
    }

    void SetTimeline(Timeline * timeline) override;
    void GetKeyframe() override;
    /**
     * Get the keyframe of this machine
     * @return startframe of this machine
     */
    int GetStartFrame(){return mStartFrame;}
    /**
     * Set the keyframe of this machine
     * @param startframe startframe of this machine
     */
    void SetStartFrame(int startframe){mStartFrame=startframe;}
    void ShowMachineDlg(wxWindow * mainFrame);

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
