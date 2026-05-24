/**
 * @file Body.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Body.h"
#include "PhysicsPolygon.h"

/**
 * Constructor
 */
Body::Body() : mSink(this)
{
}
/**
    * Create a rectangle.
    *
    * If the height parameter is not supplied and an image
    * has been set, the height will be computed so as to
    * keep the original image aspect ratio correct.
    *
    * @param x Left side X
    * @param y Bottom left Y
    * @param width Width of the rectangle
    * @param height Height of the rectangle
    */
void Body::Rectangle(double x, double y, double width, double height) {
    mPolygon.Rectangle(x, y, width, height);
}
/**
 * Create a circle centered on (0,0)
 * @param radius Circle radius
 */
void Body::Circle(double radius)
{
    mPolygon.Circle(radius,radius);
}

/**
* Set image for this Body
* @param filename
*/

void Body::SetImage(std::wstring filename) {
    mPolygon.SetImage(filename);
}

/**
 * Draw the body
 * @param graphics Graphics context to draw on
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}
/**
 * Make this component a dynamic component
 *
 * Dynamic components move based on the physics
 */
void Body::SetDynamic()
{
    mPolygon.SetDynamic();
}
/**
 * Make this component a dynamic component
 *
 * Dynamic components move based on the physics and
 * defined velocities.
 */
void Body::SetKinematic() {
    mPolygon.SetKinematic();
}

/**
 * Set the physics characteristics of this component.
 *
 * Must be called before InstallPhysics is called.
 * @param density Density in kg/m^2
 * @param friction Friction coefficient in the range [0, 1]
 * @param restitution Restitution value in the rnnge [0, 1]
 */
void Body::SetPhysics(double density, double friction, double restitution)
{
    mPolygon.SetPhysics(density,friction,restitution);
}

/**
 * Install this component into the physics system world.
 * @param world, contactListener Physics system world, contact listner of this world
 */
void Body::InstallPhysics(std::shared_ptr<b2World> world,  std::shared_ptr<ContactListener> contactListener){
    mPolygon.InstallPhysics(world);
}
/**
 * Update this body
 * @param elapsed time that elapsed
 */
void Body::Update(double elapsed)
{
}
/**
 * Reset this body
 */
void Body::Reset()
{
}
/**
 * Add point to polygon
 * @param x
 * @param y
 */
void Body::AddPoint(double x, double y)
{
    mPolygon.AddPoint(x,y);
}

/**
 * Rotate the body objects
 * @param rotation rotation of the body
 * @param speed speed of the body
 */
void Body::Rotate(double rotation, double speed)
{
    mPolygon.SetAngularVelocity(speed);
}

/**
 * Create a rectangle where 0,0 is the bottom center of the rectangle.
 *
 * Must set an image first if not providing a width and height.
 *
 * @param width Width of the rectangle in pixels. If not supplied, use the image width.
 * @param height Height of the rectangle in pixels. If not supplied, select a height such
 * that the aspect ratio matches that of the image.
 */

void Body::BottomCenteredRectangle(double width, double height)
{
    mPolygon.BottomCenteredRectangle(width, height);

}



