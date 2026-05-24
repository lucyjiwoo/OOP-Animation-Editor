/**
 * @file Body.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

/**
 * Class for the body components
 * which is rotation sink
 */

#include "Component.h"
#include  "PhysicsPolygon.h"
#include "IRotationSink.h"


class Body : public Component, public IRotationSink
{
private:
    /// position of this body
    wxPoint2DDouble mPosition;
    /// The physics polygon object for the body
    cse335::PhysicsPolygon mPolygon;
    /// Rotation sink of this body
    IRotationSink  * mSink;

public:
    Body();
    /// Copy constructor (disabled)
    Body(const Body &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Body &) = delete;


    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon * GetPolygon() {return & mPolygon;}
    void Rectangle(double x, double y, double width, double height);
    void BottomCenteredRectangle(double width, double height);
    void Circle(double radius);
    void SetImage(std::wstring filename);
    /**
     * Set the component position in the machine
     * @param x X position in centimeters
     * @param y Y position in centimeters
     */
    void SetInitialPosition(double x, double y) { mPolygon.SetInitialPosition(x,y); }
    /**
     * Set the component rotation in the machine
     * @param rotation rotation of this body
     */
    void SetInitialRotation(double rotation){mPolygon.SetInitialRotation(rotation);}
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void AddPoint(double x, double y);
    void SetDynamic();
    void SetKinematic();
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;
    void SetPhysics(double density, double friction, double restitution);
    void Rotate(double rotation, double speed) override;
    void Update(double elapsed) override;
    void Reset() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
