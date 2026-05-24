/**
 * @file Basket.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Basket.h"
#include "ContactListener.h"
#include <box2d/box2d.h>

/// The size of the basket in centimeters
const double BasketSize = 40;

/// Delay between when the ball hits the basket
/// and when it is shot out
const double BasketDelay = 1.0;

/// The direction we shoot the ball out of the basket
const wxPoint2DDouble BasketShot = wxPoint2DDouble(1, 7);
/**
 * Constructor of this basket
 * @param imagesDir images directory of this basket
 */
Basket::Basket(const std::wstring &imagesDir): mImagesDir(imagesDir) {

    mBasketLeft.BottomCenteredRectangle(1,BasketSize);
    mBasketLeft.SetColor(*wxBLUE);

    mBasketRight.BottomCenteredRectangle(1,BasketSize);
    mBasketRight.SetColor(*wxBLUE);

    mBasketFloor.BottomCenteredRectangle(BasketSize,5);
    mBasketFloor.SetColor(*wxBLUE);
}
/**
 * Set position of the Basket
 * @param x
 * @param y
 */
void Basket::SetPosition(double x, double y) {
    mPosition = wxPoint2DDouble(x,y);
    mBasketLeft.SetInitialPosition(mPosition.m_x, mPosition.m_y -BasketSize );
    mBasketRight.SetInitialPosition(mPosition.m_x +38, mPosition.m_y-BasketSize);
    mBasketFloor.SetInitialPosition(mPosition.m_x+20,mPosition.m_y-BasketSize);
}
/**
 * Draw the basket
 * @param graphics
 */
void Basket::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto basketImage = std::make_unique<wxImage>(mImagesDir +L"/basket.png", wxBITMAP_TYPE_ANY);
    auto basketBitmap = graphics->CreateBitmapFromImage(*basketImage);

    graphics->PushState();
    graphics->Scale(1,-1);
    graphics->DrawBitmap(basketBitmap, mPosition.m_x, -mPosition.m_y,
                         BasketSize,BasketSize);

    graphics->PopState();

//    mBasketLeft.Draw(graphics);
//    mBasketRight.Draw(graphics);
//    mBasketFloor.Draw(graphics);

}
/**
 * Install this component into the physics system world.
 * @param world, contactListener Physics system world, contact listner of this world
 */
void Basket::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) {
    mBasketLeft.InstallPhysics(world);
    mBasketRight.InstallPhysics(world);
    mBasketFloor.InstallPhysics(world);
    contactListener->Add(mBasketFloor.GetBody(), this);
}
/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Basket::BeginContact(b2Contact *contact) {
    mContacted = true;
}


/**
 * Handle a contact ending
 * @param contact Contact object
 */
void Basket::EndContact(b2Contact *contact) {
    mContacted = false;
}

/**
 * Handle shoting contact object
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Basket::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
        b2Body* ballA = contact->GetFixtureA()->GetBody();
        b2Body* ballB = contact->GetFixtureB()->GetBody();
        // Check if one of the bodies is the basket and the other is the ball
        if (ballA == mBasketFloor.GetBody()) {
            // Apply force to the ball's body
            mBall = ballB;
            }
        else {
            mBall = ballA;
        }
}

/**
 * Update the basket delay time
 * @param elapsed
 */
void Basket::Update(double elapsed) {
    if (mContacted){
        if (mTime < BasketDelay){
            mTime += elapsed;
        }
        else{
            mBall->ApplyForceToCenter(b2Vec2(1,7),true);
            Reset();
        }
    }
}

/**
 * Reset the basket
 */
void Basket::Reset() {
    mTime = 0.0;
    mContacted = false;
}