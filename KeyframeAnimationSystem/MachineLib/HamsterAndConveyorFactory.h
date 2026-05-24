/**
 * @file HamsterAndConveyorFactory.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H



class Machine;
class Hamster;
class Conveyor;

/**
 * Factory which is creating
 * hamster, conveyor, pulleys and the ball
 */

class HamsterAndConveyorFactory
{
private:
    /// Machine for this factory
    std::shared_ptr<Machine> mMachine;
    /// Images directory of this factory
    std::wstring mImagesDir;
    /// Hamster of this factory
    std::shared_ptr<Hamster> mHamster;
    /// Conveyor of this factory
    std::shared_ptr<Conveyor> mConveyor;

public:
    HamsterAndConveyorFactory(std::shared_ptr<Machine> machine,std::wstring imagesDir);
    void Create(wxPoint2DDouble hamsterpos, wxPoint2DDouble conveyorpos);
    void AddBall(double x);
    /**
     * Get hamster of this factory
     * @return shared pointer of the hamster
     */
    std::shared_ptr<Hamster> GetHamster(){return mHamster;}
    /**
     * Get conveyor of this factory
     * @return shared pointer of the conveyor
     */
    std::shared_ptr<Conveyor> GetConveyor(){return mConveyor;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
