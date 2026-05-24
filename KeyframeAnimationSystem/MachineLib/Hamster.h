/**
 * @file Hamster.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include  "PhysicsPolygon.h"
#include "RotationSource.h"

class ContactListener;

/**
 * Class for the hamster components
 * which is rotation source
 */
class Hamster : public Component, public b2ContactListener
{
private:
    /// The position of the hamster cage
    wxPoint2DDouble mPosition;
    /// The physics polygon object for the cage
    cse335::PhysicsPolygon mCage;
    /// The polygon object for the wheel
    cse335::Polygon mWheel;
    /// The polygon objects for the hamster
    std::vector<std::shared_ptr<cse335::Polygon>> mPolygons;
    /// Speed of this hamster
    double mSpeed = 0;
    /// rotation of the wheel
    double mRotation = 0;
    /// Rotation source for this component
    RotationSource mSource;
    /// initially running
    bool mInitiallyRun = false;
    /// State of the hamster (running or sleeping)
    bool mRunning = false;

public:
    Hamster(const std::wstring& imagesDir);

    /// Copy constructor (disabled)
    Hamster(const Hamster &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Hamster &) = delete;

    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetInitiallyRunning(bool run);
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;
    /**
     * Set the speed of this hamster
     * @param speed speed of this hamster
     */
    void SetSpeed(double speed) {mSpeed = speed;}
    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void Update(double elapsed) override;
    void Reset() override;
//    /**
//     * Get a speed of this object
//     * @return speed of this object
//     */
//    double GetSpeed(){return mSpeed;}
//    /**
//     * Get a rotation of this object
//     * @return rotation of this object
//     */
//    double GetRotation(){return mRotation;}
    /**
     * Get a position of this hamster shaft
     * @return position of this hamster shaft
     */
    wxPoint2DDouble GetShaftPosition();
    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }


};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
