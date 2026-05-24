/**
 * @file Curtain.h
 * @author Jiwoo Jeong
 *
 * Curtain class for the machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H
#define CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H

#include "Component.h"

/**
 * Class for the curtain components
 * curtain that opening the machine
 */

class Curtain : public Component
{
private:
    /// current running time for curtain
    double mCurtainTime = 0 ;

    /// Scale rate of this curtain
    double mScale = 1;

    /// The image directory for this curtain
    std::wstring mImagesDir;

public:

    Curtain(const std::wstring& imagesDir);
    /// Copy constructor (disabled)
    Curtain(const Curtain &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Curtain &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Install this component into the physics system world.
     * @param world, contactListener Physics system world, contact listner of this world
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)override {}
    void Update(double elapsed) override;
    void Reset() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H
