/**
 * @file Pulley.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

/**
 * Class represents the pulley components in the machine
 * which is rotation sink and rotation source
 */
#include "Component.h"
#include  "PhysicsPolygon.h"
#include "IRotationSink.h"
#include "RotationSource.h"

class Pulley : public Component , public IRotationSink
{
private:
    /// Radius of this pulley
    double mRadius = 0;
    /// Polygon object of this pulley
    cse335::Polygon mPolygon;
    /// position of this pulley
    wxPoint2DDouble mPosition;

    /// Rotation of this pulley
    double mRotation;
    /// Rotation sink of this pulley
    IRotationSink  * mSink;

    /// Rotation source of this pulley
    RotationSource mSource;

    /// Driven pulley
    std::shared_ptr<Pulley> mDriving = nullptr;


public:
    Pulley(double radius);

    /// Copy constructor (disabled)
    Pulley(const Pulley &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Pulley &) = delete;

    /**
     * Get a pointer to the polygon this pulley uses
     * @return Pointer to the polygon object
     */
    cse335::Polygon * GetPolygon() {return & mPolygon;}
    void SetImage(std::wstring filename);
    /**
     * Set the component position in the machine
     * @param position The position of this pulley
     */
    void SetPosition(wxPoint2DDouble position) {mPosition = position;}
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;
    void Update(double elapsed) override;
    void Reset() override;
    void Rotate(double rotation, double speed) override;

    void Drive(std::shared_ptr<Pulley> pulley);
    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }
    /**
     * Get radius of this pulley
     * @return Radius of the pulley
     */
    double GetRadius(){return mRadius;}

    /**
     * Get position of this pulley
     * @return center position of this pulley
     */
    wxPoint2DDouble GetPosition() {return mPosition;}


};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
