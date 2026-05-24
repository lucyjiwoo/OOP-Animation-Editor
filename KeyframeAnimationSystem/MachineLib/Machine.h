/**
 * @file Machine.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H



class ActualMachineSystem;
class Component;
class b2World;
class ContactListener;
/**
 * Class represents the machine
 */
class Machine
{
private:
    /// Machine system associated to this machine
    ActualMachineSystem * mMachineSystem;

    /// Machine Number
    int mMachineNumber;

    /// Location of this machine
    wxPoint mLocation;

    /// Time of this machine
    double mMachineTime = 0;
    /// list of components in this machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;
    /// The box2d world
    std::shared_ptr<b2World> mWorld;

public:
    ///default construtor
    Machine(int machine);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void AddComponent(std::shared_ptr<Component> component);
    /**
     * Set machine time of this machine
     * @param time Machine time for this machine
     */
    void SetTime(double time){mMachineTime = time;}

    /**
     * Set a location of this machine
     * @param location The location for this machine
     */
    void SetLocation(wxPoint location){mLocation = location;}

    /**
     * Set machine system of this machine
     * @param machinesystem Machine system for this machine
     */
     void SetMachineSystem(ActualMachineSystem * machinesystem) {mMachineSystem = machinesystem;}
    /**
     * Get a location of this machine
     * @return the location of this machine
     */
    wxPoint GetLocation(){return mLocation;}
    void Reset();
    void Update(double elapsed);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
