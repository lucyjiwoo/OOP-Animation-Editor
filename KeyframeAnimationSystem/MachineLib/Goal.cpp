/**
 * @file Goal.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "Goal.h"
#include "ContactListener.h"
#include <box2d/box2d.h>


/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);


/**
 * Constructor
 * @param imagesDir image directory of the goal image
 */
Goal::Goal(const std::wstring & imagesDir){
    mPolygon.BottomCenteredRectangle(GoalSize);
    mPolygon.SetImage(imagesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mGoal.BottomCenteredRectangle(TargetSize);
    mGoal.SetColor(*wxBLUE);
}
/**
 * Set position of the goal
 * @param x
 * @param y
 */
void Goal::SetPosition(double x, double y) {
    mPosition = wxPoint2DDouble(x,y);
    mPost.SetInitialPosition(mPosition.m_x + PostPosition.m_x, mPosition.m_y + PostPosition.m_y);
    mGoal.SetInitialPosition(mPosition.m_x + GoalPosition.m_x, mPosition.m_y + GoalPosition.m_y);
}
/**
 * Draw the goal
 * @param graphics Graphics context to draw on
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y, 0);

    // Uncomment the following lines if needed
    // mPost.Draw(graphics);
    // mGoal.Draw(graphics);

    // Draw the rectangle(Scoreboard)
    graphics->PushState();
    graphics->Translate(mPosition.m_x , mPosition.m_y );
    graphics->SetBrush(ScoreboardBackgroundColor);
    wxPen linePen(*wxBLACK, ScoreboarderLineWidth);
    graphics->SetPen(linePen);

    graphics->DrawRectangle(ScoreboardRectangle.m_x, ScoreboardRectangle.m_y,
                            ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);
    graphics->PopState();

    // Draw the text(Scoreboard)
    graphics->PushState();
    graphics->Translate(mPosition.m_x + ScoreboardTextLocation.m_x, mPosition.m_y + ScoreboardTextLocation.m_y);
    graphics->Scale(1, -1);
    wxFont font(ScoreboardFontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);
    if (mScore <10){
        graphics->DrawText("0" + std::to_wstring(mScore), 0, 0);
    }
    else{
        graphics->DrawText(std::to_wstring(mScore), 0, 0);}

    graphics->PopState();
}





/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}

/**
 * Install this component into the physics system world.
 * @param world, contactListener Physics system world, contact listner of this world
 */
void Goal::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener){
    mPost.InstallPhysics(world);
    mGoal.InstallPhysics(world);
    contactListener->Add(mGoal.GetBody(), this);
}
/**
 * Update this Goal
 * @param elapsed time that elapsed
 */
void Goal::Update(double elapsed)
{

}

/**
 * Reset this Goal
 */
void Goal::Reset()
{
    mScore = 0;
}
