/**
 * @file Pulley.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Pulley.h"

/// Maximum amount to rock the belt
/// No, I'm not going to tell you what
/// the units are.
const double BeltRockAmount = 0.01;

/// How quickly to rock the belt in radians per second
/// This is divided by the length to get the actual rate
const double BeltRockBaseRate = M_PI * 1000;


/**
 * Constructor
 * @param radius The radius of this pulley
 */

Pulley::Pulley(double radius) : mSink(this), mSource(this)
{
    mRadius = radius;

    mPolygon.CenteredSquare(mRadius * 2);
}

/**
* Set image for this Pulley
* @param filename
*/

void Pulley::SetImage(std::wstring filename) {
    mPolygon.SetImage(filename);
}

/**
 * Draw the pulley
 * @param graphics Graphics context to draw on
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mDriving != nullptr){
        graphics->PushState();
        wxPen blackPen(*wxBLACK, 2);
        ///Draw the belt
        graphics->SetPen(blackPen);
        wxPoint2DDouble p1_to_p2 = mDriving->GetPosition()-mPosition;
        double theta = atan2(p1_to_p2.m_y,p1_to_p2.m_x);
        double phi = asin((mDriving->GetRadius()-mRadius)/sqrt(p1_to_p2.m_x*p1_to_p2.m_x+p1_to_p2.m_y*p1_to_p2.m_y));
        double beta = theta + phi + M_PI/2;
        wxPoint2DDouble endPoint1_1 = mPosition + (mRadius-1) * wxPoint2DDouble(cos(beta),sin(beta));
        wxPoint2DDouble endPoint2_1 = mDriving->GetPosition() + (mDriving->GetRadius()-1) * wxPoint2DDouble(cos(beta),sin(beta));
        wxPoint2DDouble endPoint1_2 = mPosition - (mRadius-1) * wxPoint2DDouble(cos(beta),sin(beta));
        wxPoint2DDouble endPoint2_2 = mDriving->GetPosition() - (mDriving->GetRadius()-1) * wxPoint2DDouble(cos(beta),sin(beta));
//        wxPoint2DDouble alpha = (mRadius-1)* (p1_to_p2)/sqrt(p1_to_p2.m_x*p1_to_p2.m_x+p1_to_p2.m_y*p1_to_p2.m_y);
//        wxPoint2DDouble beta = wxPoint2DDouble(-alpha.m_y,alpha.m_x);
        graphics->StrokeLine(endPoint1_1.m_x, endPoint1_1.m_y, endPoint2_1.m_x, endPoint2_1.m_y);
        graphics->StrokeLine(endPoint1_2.m_x, endPoint1_2.m_y, endPoint2_2.m_x, endPoint2_2.m_y);
        graphics->PopState();
    }
    mPolygon.DrawPolygon(graphics,mPosition.m_x,mPosition.m_y,mRotation);

}

/**
 * Install this component into the physics system world.
 * @param world, contactListener Physics system world, contact listner of this world
 */
void Pulley::InstallPhysics(std::shared_ptr<b2World> world,  std::shared_ptr<ContactListener> contactListener){
}
/**
 * Update this pulley
 * @param elapsed time that elapsed
 */
void Pulley::Update(double elapsed)
{
    if (mRotation != 0){
    }
}
/**
 * Reset this pulley
 */
void Pulley::Reset()
{
}
/**
 * Rotate the pulley objects
 * @param rotation rotation of the pulley
 * @param speed speed of the pulley
 */
void Pulley::Rotate(double rotation, double speed)
{
    mRotation = rotation;
    if (mDriving != nullptr){
        mDriving->Rotate(rotation* mRadius/mDriving->GetRadius(), speed);
    }
    mSource.Rotate(rotation,speed);

}
/**
 * Drive other pulley as rotation sink of this pulley
 * @param pulley driven pulley
 */
void Pulley::Drive(std::shared_ptr<Pulley> pulley){
    mDriving = pulley;
}
