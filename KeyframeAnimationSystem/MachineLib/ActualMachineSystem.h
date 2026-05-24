/**
 * @file ActualMachineSystem.h
 * @author Jiwoo Jeong
 *
 * Actual Machine System
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H

/**
 * The Class for actual machine system for the machine
 */
#include "IMachineSystem.h"
#include "Machine.h"
class ActualMachineSystem : public IMachineSystem
{
private:
    /// frame rate of this machine system
    double mFrameRate = 30;

    /// frame number of this machine system
    int mFrame = 0 ;

    /// location of this machine system
    wxPoint mLocation;

    /// Machine Number
    int mMachineNum;

    /// Machine of this system
    std::shared_ptr<Machine>  mMachine;
    /// The resources directory
    std::wstring mResourcesDir;
    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;






public:
    /// Destructor
    ~ActualMachineSystem() override= default;

    ActualMachineSystem(std::wstring resourcesDir);

    /**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
    void SetLocation(wxPoint location) {mLocation = location;}

    /**
     * Get the location of hte machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() override {return mLocation;}

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    void SetMachineFrame(int frame) override;

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override {mFrameRate = rate;}

    void SetMachineNumber(int machine) override;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() override {return mMachineNum;}

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() override {return mFrame/mFrameRate;}

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag) override {}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H
