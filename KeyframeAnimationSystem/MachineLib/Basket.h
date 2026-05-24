/**
 * @file Basket.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BASKET_H
#define CANADIANEXPERIENCE_MACHINELIB_BASKET_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include  "PhysicsPolygon.h"

class ContactListener;
/**
 * Class for the curtain components
 * curtain that opening the machine
 */
class Basket : public Component, public b2ContactListener
{
private:
    /// position of the basket
    wxPoint2DDouble mPosition;

    /// Physics polygon for the basket left
    cse335::PhysicsPolygon mBasketLeft;

    /// Physics polygon for the basket right
    cse335::PhysicsPolygon mBasketRight;

    /// Polygon that we are going to hit to
    /// determine the basket to add force to the ball
    cse335::PhysicsPolygon mBasketFloor;

    /// The image directory for this basket
    std::wstring mImagesDir;

    /// The time of object stay in the basket
    double mTime = 0.0;

    /// Check if ball in the basket
    bool mContacted = false;

    /// The ball object in the basket
    b2Body * mBall = nullptr;

public:
    Basket(const std::wstring& imagesDir);
    /// Copy constructor (disabled)
    Basket(const Basket &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Basket &) = delete;
    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)override;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void Update(double elapsed) override;
    void Reset() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BASKET_H
