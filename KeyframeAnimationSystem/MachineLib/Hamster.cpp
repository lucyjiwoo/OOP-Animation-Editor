/**
 * @file Hamster.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Hamster.h"
#include "ContactListener.h"
#include <box2d/box2d.h>

/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};


/**
 * Constructor
 * @param imagesDir the images directory of hamster images
 */
Hamster::Hamster(const std::wstring& imagesDir): mSource(this)
{
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mCage.SetImage(imagesDir + HamsterCageImage);

    mWheel.CenteredSquare(HamsterWheelSize);
    mWheel.SetImage(imagesDir+ HamsterWheelImage);

    for (int i = 0; i < 4; i++)
    {
        auto hamster = std::make_shared<cse335::PhysicsPolygon>();
        hamster->BottomCenteredRectangle(HamsterSize,HamsterSize);
        hamster->SetImage(imagesDir + HamsterImages[i]);
        mPolygons.push_back(hamster);
    }

}


/**
 * Set position of the hamster
 * @param x
 * @param y
 */
void Hamster::SetPosition(double x, double y) {
    mPosition = wxPoint(x,y);
    mCage.SetInitialPosition(mPosition.m_x, mPosition.m_y);

}
/**
 * Set initial state of hamster(run/sleep)
 * @param run  running state bool
 */
void Hamster::SetInitiallyRunning(bool run)
{
    mInitiallyRun = run;
}

/**
 * Draw the hamster, wheel,and cage
 * @param graphics Graphics context to draw on
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mCage.Draw(graphics);
    mWheel.DrawPolygon(graphics,mPosition.m_x + WheelCenter.m_x,mPosition.m_y + WheelCenter.m_y, mRotation);
    graphics->PushState();
    graphics->Translate(mPosition.m_x + WheelCenter.m_x, mPosition.m_y);

    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }
    if (mRunning){
        int hamsterIndex = int(abs(mRotation * 16))%4;
        hamsterIndex ++;
        if (hamsterIndex == 4){
            hamsterIndex = 2;
        }
        // Draw the running image
        mPolygons[hamsterIndex]->DrawPolygon(graphics, 0, 0, 0);
    }
    else{
        mPolygons[0]->DrawPolygon(graphics, 0, 0, 0);
    }


    graphics->PopState();
}
/**
 * Handle contact with the hamster
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Hamster::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    mRunning = true;
}

/**
 * Install this hamster into the physics system world.
 * @param world, contactListener Physics system world, contact listner of this world
 */
void Hamster::InstallPhysics(std::shared_ptr<b2World> world,  std::shared_ptr<ContactListener> contactListener)
{
    mCage.InstallPhysics(world);
    contactListener->Add(mCage.GetBody(), this);
}

/**
 * Update this hamster
 * @param elapsed time that elapsed
 */
void Hamster::Update(double elapsed)
{
    if (mRunning) {
        mRotation -= mSpeed * elapsed;
        mSource.Rotate(mRotation,-mSpeed);
    }
}
/**
 * Reset this hamster
 */
void Hamster::Reset()
{
    mRunning = mInitiallyRun;
}

/**
 * Get a position of this hamster shaft
 * @return position of this hamster shaft
 */

wxPoint2DDouble Hamster::GetShaftPosition(){
    wxPoint2DDouble shaft(mPosition.m_x + HamsterShaftOffset.m_x, mPosition.m_y + HamsterShaftOffset.m_y);
    return shaft;
}


