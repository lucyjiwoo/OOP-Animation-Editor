/**
 * @file Banner.cpp
 * @author Jiwoo Jeong
 */

#include "pch.h"
#include "Banner.h"

/// Scale to draw relative to the image sizes
const double BannerScale = 0.42;

/// Height of the banner in pixels
double const BannerHeight = 150 * BannerScale;

/// Width fo the banner in pixels
const double BannerWidth = 1024 * BannerScale;

/// Height of the banner roll image in pixels
const double BannerRollHeight = 300 * BannerScale;

/// Width of the banner roll image in pixels
double const BannerRollWidth = 16 * BannerScale;

/// How fast ot unfurl the banner in pixels per second
double const BannerSpeed = 41.65;

/// Minimum number of pixels to start with as unfurled
const double BannerMinimum = 15;


/**
 * Constructor
 * @param imagesDir The image directory for this banner
 */

Banner::Banner(const std::wstring & imagesDir) : mImagesDir(imagesDir)
{
    mCrop = BannerMinimum;

}


/**
 * Draw the Banner
 * @param graphics
 */

void Banner::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    auto bannerRollImage = std::make_unique<wxImage>(mImagesDir +L"/banner-roll.png", wxBITMAP_TYPE_ANY);
    auto bannerRollBitmap = graphics->CreateBitmapFromImage(*bannerRollImage);

    auto bannerOriginalImage = std::make_unique<wxImage>(mImagesDir + L"/banner.png", wxBITMAP_TYPE_ANY);

    graphics->PushState();
    graphics->Scale(1,-1);
    graphics->DrawBitmap(bannerRollBitmap,BannerWidth/2,-400,
                         BannerRollWidth,BannerRollHeight);

    wxRect BannerCropped(0, 0, mCrop/BannerScale, 150);

    wxImage bannerCurrent = bannerOriginalImage->GetSubImage(BannerCropped);
    auto bannerBitmap = graphics->CreateBitmapFromImage(bannerCurrent);
    graphics->DrawBitmap(bannerBitmap,BannerWidth/2-mCrop,-400+BannerHeight/2, mCrop,BannerHeight);
    graphics->PopState();
}

/**
 * Update the banner running time and crop rate
 * @param elapsed
 */

void Banner::Update(double elapsed)
{
    if( mCrop <= BannerWidth ){
        mCrop += BannerSpeed *elapsed;
    }
    else{
        Reset();
    }
}

/**
 * Reset the banner
 */

void Banner::Reset()
{
    mBannerTime = 0;
    mCrop = BannerMinimum;
}
