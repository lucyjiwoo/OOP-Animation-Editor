/**
 * @file Goal.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include  "PhysicsPolygon.h"

class ContactListener;
/**
 * Class for the goal components
 * scoreboard and post
 */

class Goal : public Component, public b2ContactListener
{
private:
    /// position of the goal
    wxPoint2DDouble mPosition;

    /// The polygon object for the goal image
    cse335::Polygon mPolygon;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mGoal;

    ///The score
    int mScore = 0;

public:

    Goal(const std::wstring & imagesDir);
    /// Copy constructor (disabled)
    Goal(const Goal &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Goal &) = delete;

    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;
    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void Update(double elapsed) override;
    void Reset() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
