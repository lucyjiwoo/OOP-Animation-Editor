/**
 * @file RotationSource.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H


class Component;
class IRotationSink;

/**
 * Class represents the rotation source
 */

class RotationSource
{
private:
    /// component that is rotation source
    Component * mComponent;
    /// sink
    std::vector<std::shared_ptr<IRotationSink>> mSinks;

public:
    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    RotationSource(Component * component);
    void AddSink(std::shared_ptr<IRotationSink> sink);
    void Rotate(double rotation, double speed);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
