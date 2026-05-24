/**
 * @file Picture.h
 *
 * @author Charles B. Owen
 *
 *  Class that represents our animation picture
 */

#pragma once

#include "Timeline.h"

class PictureObserver;
class Actor;
class MachineDrawable;

/**
 *  Class that represents our animation picture
 */
class Picture
{
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

    /// The actors associated with this picture
    std::vector<std::shared_ptr<Actor>> mActors;

    /// The animation timeline
    Timeline mTimeline;

    /// The first machine
    std::shared_ptr<MachineDrawable> mMachine1;
    /// The second machine
    std::shared_ptr<MachineDrawable> mMachine2;

public:
    Picture();

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Destructor
    */
    virtual ~Picture() = default;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    /**
     * Get a pointer to the Timeline object
     * @return Pointer to the Timeline object
     */
    Timeline *GetTimeline() {return &mTimeline;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void AddActor(std::shared_ptr<Actor> actor);


    /**
     * Set the first machine of this picture
     * @param machine1 The pointer to the first machine
     */
    void SetMachine1(std::shared_ptr<MachineDrawable> machine1){mMachine1 = machine1;}
    /**
     * Set the second machine of this picture
     * @param machine2  The pointer to second machine
     */
     void SetMachine2(std::shared_ptr<MachineDrawable> machine2){mMachine2 = machine2;}

    /**
    * Get the first machine of this picture
    * @return machine1 The pointer to the first machine
    */
    std::shared_ptr<MachineDrawable> GetMachine1(){return mMachine1;}

    /**
    * Get the second machine of this picture
    * @return machine2 The pointer to the second machine
    */
    std::shared_ptr<MachineDrawable> GetMachine2(){return mMachine2;}

    /** Iterator that iterates over the actors in a picture */
    class ActorIter
    {
    public:
        /**
         * Constructor
         * @param picture Picture we are iterating
         * @param pos Starting position \
         */
        ActorIter(Picture *picture, int pos) : mPicture(picture), mPos(pos) {}

        /**
         * Test for end of the iterator
         * @param other Other object to test against
         * @return True if we this position equals not equal to the other position
         */
        bool operator!=(const ActorIter &other) const
        {
            return mPos != other.mPos;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Actor> operator *() const { return mPicture->mActors[mPos]; }

        /** Increment the iterator
        * @return Reference to this iterator */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }


    private:
        Picture *mPicture;  ///< Picture we are iterating over
        int mPos;           ///< Position in the collection
    };

    /**
     * Get an iterator for the beginning of the collection
     * @return Iter object at position 0
     */
    ActorIter begin() { return ActorIter(this, 0); }

    /**
     * Get an iterator for the end of the collection
     * @return Iter object at position past the end
     */
    ActorIter end() { return ActorIter(this, mActors.size()); }

    void SetAnimationTime(double time);

    double GetAnimationTime();

    void Load(const wxString& filename);

    void Save(const wxString& filename);
};

