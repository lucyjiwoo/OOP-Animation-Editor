/**
 * @file Component.h
 * @author Jiwoo Jeong
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H


class b2World;
class ContactListener;

/**
 * Class for the components
 * derive class for all components
 */
class Component{
private:
    /// position of this component
    wxPoint mPosition;

public:
    /// Default constructor
    Component();

    /// Copy constructor (disabled)
    Component(const Component &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Component &) = delete;

    /**
     * Draw the component
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics){}
    /**
     * Install physics for this components
     * @param world
     * @param contactListener
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) = 0;
    virtual void Update(double elapsed);
    virtual void Reset();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
