/**
 * @file IRotationSink.h
 * @author Jiwoo Jeong
 *
 * Interface that represents a rotation sink.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H


/**
 * Interface class for the rotation sink
 * Rotation sink which is rotating by the rotation source
 */

class IRotationSink
{
private:

public:
    /// Destructor
    virtual ~IRotationSink() = default; // Virtual destructor for proper polymorphic behavior

    // Pure virtual function to be implemented by derived classes
    /**
     * Rotate this rotation sink
     * @param rotation, speed rotation and speed of this sink
     */
    virtual void Rotate(double rotation, double speed) = 0;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
