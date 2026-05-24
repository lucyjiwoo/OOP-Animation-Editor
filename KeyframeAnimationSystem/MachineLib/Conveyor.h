/**
 * @file Conveyor.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

/**
 * Class for the conveyor components
 * which is rotation sink
 */

#include "Component.h"
#include <b2_world_callbacks.h>
#include  "PhysicsPolygon.h"
#include "IRotationSink.h"

class Conveyor: public Component, public IRotationSink, public b2ContactListener
{
private:
    /// position of this conveyor
    wxPoint2DDouble mPosition;
    /// The physics polygon object for the conveyor
    cse335::PhysicsPolygon mConveyor;
    /// Rotation sink of this conveyor
    IRotationSink  * mSink;
    /// Linear speed of this conveyor
    double mSpeed = 0;

public:
    Conveyor(const std::wstring& imagesDir);
    /// Copy constructor (disabled)
    Conveyor(const Conveyor &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Conveyor &) = delete;
    /**
     * Get a pointer to the polygon this conveyor uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon * GetPolygon() {return & mConveyor;}
    void SetPosition(double x, double y);
    /**
     * Get position of this conveyor
     * @return position of this conveyor
     */
    wxPoint2DDouble GetPosition(){return mPosition;}
    wxPoint2DDouble GetShaftPosition();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;
    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void Rotate(double rotation, double speed) override;
    void Update(double elapsed) override;
    void Reset() override;



};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
