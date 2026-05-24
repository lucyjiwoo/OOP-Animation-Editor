/**
 * @file Curtain.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Curtain.h"

/// Height of our curtains in pixels
const double CurtainHeight = 500;

/// Total width of the curtains in pixels
const double CurtainWidth = 750;

/// Number of seconds to open the curtains
const double CurtainOpenTime = 2.0;

/// Minimum scaling factor for when the curtains are open
const double CurtainMinScale = 0.2;

/**
 * Constructor
 * @param imagesDir The image directory for this curtain
 */

Curtain::Curtain(const std::wstring&imagesDir) : mImagesDir(imagesDir)
{

}


/**
 * Draw the curtain
 * @param graphics
 */

void Curtain::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto curtainLeftImage = std::make_unique<wxImage>(mImagesDir +L"/curtain1.png", wxBITMAP_TYPE_ANY);
    auto curtainLeftBitmap = graphics->CreateBitmapFromImage(*curtainLeftImage);

    auto curtainRightImage = std::make_unique<wxImage>(mImagesDir + L"/curtain2.png", wxBITMAP_TYPE_ANY);
    auto curtainRightBitmap = graphics->CreateBitmapFromImage(*curtainRightImage);

    auto curtainRodImage = std::make_unique<wxImage>(mImagesDir+L"/curtain-rod.png", wxBITMAP_TYPE_ANY);
    auto curtainRodBitmap = graphics->CreateBitmapFromImage(*curtainRodImage);

    graphics->PushState();
    graphics->Scale(1,-1);
    graphics->DrawBitmap(curtainRodBitmap,-CurtainWidth/2,-390,
                         CurtainWidth, curtainRodImage->GetHeight());
    graphics->Scale(1,1);
    //draw left curtain
    graphics->DrawBitmap(curtainLeftBitmap,-CurtainWidth/2,-390,
                         CurtainWidth/2 * mScale, CurtainHeight);
    //draw right curtain
    graphics->DrawBitmap(curtainRightBitmap,0 + CurtainWidth/2 * (1-mScale),-390,
                         CurtainWidth/2 * mScale, CurtainHeight);



    graphics->PopState();

}

/**
 * Update the curtain running time and scale
 * @param elapsed
 */

void Curtain::Update(double elapsed)
{
    if (mCurtainTime <= CurtainOpenTime && mScale >= CurtainMinScale) {
        mCurtainTime+= elapsed;
        mScale = 1 - mCurtainTime * 0.4;
    }
}

/**
 * Reset the curtain
 */

void Curtain::Reset()
{
    mCurtainTime = 0;
    mScale = 1;
}


