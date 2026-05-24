/**
 * @file Conveyor.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Conveyor.h"
#include "ContactListener.h"
#include <box2d/box2d.h>

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";




/**
 * Constructor
 * @param imagesDir image directory of this conveyor
 */
Conveyor::Conveyor(const std::wstring& imagesDir)
{
    mConveyor.BottomCenteredRectangle(ConveyorSize);
    mConveyor.SetImage(imagesDir + ConveyorImageName);
}

/**
 * Draw the conveyor
 * @param graphics Graphics context to draw on
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics){
    mConveyor.Draw(graphics);
}

/**
 * Set position of the conveyor
 * @param x
 * @param y
 */
void Conveyor::SetPosition(double x, double y) {
    mPosition = wxPoint(x,y);
    mConveyor.SetInitialPosition(mPosition.m_x, mPosition.m_y);


}

/**
 * Install this component into the physics system world.
 * @param world, contactListener Physics system world, contactlistner of this world
 */
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world,  std::shared_ptr<ContactListener> contactListener){
    mConveyor.InstallPhysics(world);
    contactListener->Add(mConveyor.GetBody(), this);
}

/**
 * Make contacted object to have a speed
 * @param contact Contact object
 * @param oldManifold Manifold object
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Conveyor::BeginContact(b2Contact *contact)
{
    b2ContactListener::BeginContact(contact);
}
/**
 * Reset this conveyor
 */
void Conveyor::Reset()
{
    mSpeed = 0;
}
/**
 * Update this conveyor
 * @param elapsed time that elapsed
 */
void Conveyor::Update(double elapsed)
{
}

/**
 * Rotate the conveyor objects
 * @param rotation rotation of the conveyor
 * @param speed speed of the conveyor
 */
void Conveyor::Rotate(double rotation, double speed)
{
    mSpeed = speed;
    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-speed, 0));
        }

        contact = contact->next;
    }
}
/**
 * Get shaft position of this conveyor
 * @return position of the shaft of this conveyor
 */
wxPoint2DDouble Conveyor::GetShaftPosition(){
    return mPosition + ConveyorShaftOffset;

}

