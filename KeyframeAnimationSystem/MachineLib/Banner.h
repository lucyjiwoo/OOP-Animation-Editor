/**
 * @file Banner.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BANNER_H
#define CANADIANEXPERIENCE_MACHINELIB_BANNER_H

#include "Component.h"
/**
 * Class for the banner components
 * banner in the machine
 */

class Banner: public Component
{
private:

/// current running time for banner
    double mBannerTime = 0;

    /// Cropped pixel of this banner
    double mCrop = 0;

    /// The image directory for this banner
    std::wstring mImagesDir;

public:
    Banner(const std::wstring& imagesDir);
    /// Copy constructor (disabled)
    Banner(const Banner &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Banner &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Install this component into the physics system world.
     * @param world, contactListener Physics system world, contact listner of this world
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)override {}
    void Update(double elapsed) override;
    void Reset() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BANNER_H
