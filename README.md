# OOP Animation Editor — 2D Keyframe Animation System

A C++ desktop animation application built with **wxWidgets**, implementing a keyframe-based 2D character animation system. Characters (actors) are composed of hierarchical drawable parts that can be independently positioned, rotated, and animated over a timeline.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Build Requirements](#build-requirements)
- [Project Structure](#project-structure)
- [System Architecture](#system-architecture)
- [Class Diagrams](#class-diagrams)
  - [Core Domain](#core-domain-class-diagram)
  - [Animation System](#animation-system-class-diagram)
  - [UI Layer (Observer Pattern)](#ui-layer--observer-pattern)
  - [Factory Pattern](#factory-pattern)
- [Design Patterns](#design-patterns)
- [Component Descriptions](#component-descriptions)
- [Data Flow](#data-flow)

---

## Overview

OOP Animation Editor is a 2D keyframe animation editor that allows users to:
- Place animated characters (Harold, Sparty) into a scene
- Attach interactive machines to the scene via an adapter interface
- Scrub through a frame-based timeline and set keyframes
- Interpolate (tween) between keyframes for smooth animation
- Save and load animation state as XML

---

## Features

| Feature | Description |
|---|---|
| Keyframe Animation | Set position/rotation keyframes per drawable |
| Tweening | Linear interpolation between keyframes |
| Multiple Characters | Harold and Sparty actors, each with articulated body parts |
| Machine Integration | External machines embedded via Adapter pattern |
| Observer-driven UI | Two views (Edit + Timeline) auto-update via Observer pattern |
| XML Persistence | Full save/load of animation state |
| Mouse Interaction | Click to select, drag to move/rotate drawables |

---

## Build Requirements

- **C++17** or later
- **wxWidgets 3.x** (GUI framework)
- **CMake 3.15+**
- Machine API library (`machine-api.h`)

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

---

## Project Structure

```
OOP-Animation-Editor/
└── KeyframeAnimationSystem/
    ├── CanadianExperienceApp.cpp/.h     # wxApp entry point
    ├── CMakeLists.txt
    └── CanadianExperienceLib/
        ├── MainFrame.h/.cpp             # Top-level window
        ├── ViewEdit.h/.cpp              # Canvas view (Observer)
        ├── ViewTimeline.h/.cpp          # Timeline view (Observer)
        │
        ├── Picture.h/.cpp              # Scene container
        ├── PictureObserver.h/.cpp      # Observer base class
        ├── PictureFactory.h/.cpp       # Builds the full scene
        │
        ├── Actor.h/.cpp                # Character container
        ├── HaroldFactory.h/.cpp        # Builds Harold actor
        ├── SpartyFactory.h/.cpp        # Builds Sparty actor
        │
        ├── Drawable.h/.cpp             # Abstract drawable part
        ├── ImageDrawable.h/.cpp        # Bitmap-based drawable
        ├── PolyDrawable.h/.cpp         # Polygon-based drawable
        ├── HeadTop.h/.cpp              # Specialized head drawable
        ├── MachineDrawable.h/.cpp      # Adapter for IMachineSystem
        ├── RotatedBitmap.h/.cpp        # Rotated bitmap renderer
        │
        ├── Timeline.h/.cpp             # Frame/time manager
        ├── AnimChannel.h/.cpp          # Abstract animation channel
        ├── AnimChannelAngle.h/.cpp     # Angle interpolation channel
        └── AnimChannelPoint.h/.cpp     # Position interpolation channel
```

---

## System Architecture

The application is divided into four main layers:

```
┌─────────────────────────────────────────────────────┐
│                   UI Layer (wxWidgets)               │
│         MainFrame → ViewEdit + ViewTimeline         │
└───────────────────────┬─────────────────────────────┘
                        │ Observer Pattern
┌───────────────────────▼─────────────────────────────┐
│                  Domain Layer                        │
│         Picture ──▶ Actor ──▶ Drawable (tree)       │
└───────────────────────┬─────────────────────────────┘
                        │
┌───────────────────────▼─────────────────────────────┐
│               Animation Layer                        │
│      Timeline ──▶ AnimChannel ──▶ Keyframes         │
└───────────────────────┬─────────────────────────────┘
                        │ Adapter Pattern
┌───────────────────────▼─────────────────────────────┐
│              External Machine API                    │
│                 IMachineSystem                       │
└─────────────────────────────────────────────────────┘
```

---

## Class Diagrams

### Core Domain Class Diagram

```mermaid
classDiagram
    class Picture {
        -wxSize mSize
        -vector~PictureObserver*~ mObservers
        -vector~shared_ptr~Actor~~ mActors
        -Timeline mTimeline
        -shared_ptr~MachineDrawable~ mMachine1
        -shared_ptr~MachineDrawable~ mMachine2
        +AddActor(actor)
        +AddObserver(observer)
        +UpdateObservers()
        +Draw(graphics)
        +SetAnimationTime(time)
        +Save(filename)
        +Load(filename)
    }

    class Actor {
        -wstring mName
        -wxPoint mPosition
        -bool mEnabled
        -bool mClickable
        -shared_ptr~Drawable~ mRoot
        -vector~shared_ptr~Drawable~~ mDrawablesInOrder
        -AnimChannelPoint mChannel
        +Draw(graphics)
        +HitTest(pos) shared_ptr~Drawable~
        +AddDrawable(drawable)
        +SetRoot(root)
        +SetKeyframe()
        +GetKeyframe()
    }

    class Drawable {
        <<abstract>>
        -wstring mName
        -wxPoint mPosition
        -double mRotation
        -Actor* mActor
        -Drawable* mParent
        -vector~shared_ptr~Drawable~~ mChildren
        -AnimChannelAngle mChannel
        #wxPoint mPlacedPosition
        #double mPlacedR
        +Draw(graphics)* 
        +HitTest(pos)* bool
        +IsMovable() bool
        +Place(offset, rotate)
        +AddChild(child)
        +Move(delta)
        +SetTimeline(timeline)
        +SetKeyframe()
        +GetKeyframe()
    }

    Picture "1" *-- "many" Actor : contains
    Actor "1" *-- "many" Drawable : has
    Drawable "1" *-- "many" Drawable : children
    Picture "1" *-- "1" Timeline : owns
```

---

### Animation System Class Diagram

```mermaid
classDiagram
    class Timeline {
        -int mNumFrames
        -int mFrameRate
        -double mCurrentTime
        -vector~AnimChannel*~ mChannels
        +AddChannel(channel)
        +SetCurrentTime(time)
        +GetCurrentFrame() int
        +GetDuration() double
        +Clear()
        +Save(root)
        +Load(root)
    }

    class AnimChannel {
        <<abstract>>
        -wstring mName
        -int mKeyframe1
        -int mKeyframe2
        -Timeline* mTimeline
        -vector~shared_ptr~Keyframe~~ mKeyframes
        +SetFrame(currFrame)
        +IsValid() bool
        +ClearKeyframe()
        +XmlSave(node)*
        +XmlLoad(node)*
        #InsertKeyframe(keyframe)
        #XmlLoadKeyframe(node)*
        #Tween(t)*
    }

    class Keyframe {
        <<abstract>>
        -AnimChannel* mChannel
        -int mFrame
        +GetFrame() int
        +SetFrame(f)
        +UseAs1()*
        +UseAs2()*
        +UseOnly()*
        +XmlSave(node)
    }

    class AnimChannelAngle {
        -double mAngle
        -KeyframeAngle* mKeyframe1
        -KeyframeAngle* mKeyframe2
        +GetAngle() double
        +SetKeyframe(angle)
        +Tween(t)
        #XmlLoadKeyframe(node)
    }

    class KeyframeAngle {
        -double mAngle
        -AnimChannelAngle* mChannel
        +GetAngle() double
        +UseAs1()
        +UseAs2()
        +UseOnly()
        +XmlSave(node)
    }

    class AnimChannelPoint {
        -wxPoint mPoint
        -KeyframePoint* mKeyframe1
        -KeyframePoint* mKeyframe2
        +GetPoint() wxPoint
        +SetKeyframe(point)
        +Tween(t)
        #XmlLoadKeyframe(node)
    }

    class KeyframePoint {
        -wxPoint mPoint
        -AnimChannelPoint* mChannel
        +GetPoint() wxPoint
        +UseAs1()
        +UseAs2()
        +UseOnly()
        +XmlSave(node)
    }

    Timeline "1" o-- "many" AnimChannel : manages
    AnimChannel <|-- AnimChannelAngle
    AnimChannel <|-- AnimChannelPoint
    AnimChannel "1" *-- "many" Keyframe
    Keyframe <|-- KeyframeAngle
    Keyframe <|-- KeyframePoint
    AnimChannelAngle ..> KeyframeAngle
    AnimChannelPoint ..> KeyframePoint
```

---

### Drawable Inheritance Hierarchy

```mermaid
classDiagram
    class Drawable {
        <<abstract>>
        +Draw(graphics)*
        +HitTest(pos)* bool
        +IsMovable() bool
    }

    class ImageDrawable {
        -unique_ptr~wxImage~ mImage
        -wxGraphicsBitmap mBitmap
        -wxPoint mCenter
        +Draw(graphics)
        +HitTest(pos) bool
        +SetCenter(center)
    }

    class HeadTop {
        -wxPoint mEyesCenter
        -int mInterocularDistance
        -RotatedBitmap mLeftEye
        -RotatedBitmap mRightEye
        -AnimChannelPoint mPositionChannel
        +Draw(graphics)
        +IsMovable() bool
        +DrawEye(graphics, p1)
        +DrawEyebrow(graphics, p1, p2)
        +SetTimeline(timeline)
        +SetKeyframe()
        +GetKeyframe()
    }

    class PolyDrawable {
        -wxColour mColor
        -vector~wxPoint~ mPoints
        -wxGraphicsPath mPath
        +Draw(graphics)
        +HitTest(pos) bool
        +AddPoint(point)
        +SetColor(color)
    }

    class MachineDrawable {
        -shared_ptr~IMachineSystem~ mMachine
        -Timeline* mTimeline
        -int mStartFrame
        +Draw(graphics)
        +HitTest(pos) bool
        +SetMachineNumber(number)
        +GetMachineNumber() int
        +SetTimeline(timeline)
        +GetKeyframe()
        +ShowMachineDlg(mainFrame)
    }

    class IMachineSystem {
        <<interface>>
        +SetMachineNumber()*
        +GetMachineNumber()*
    }

    Drawable <|-- ImageDrawable
    ImageDrawable <|-- HeadTop
    Drawable <|-- PolyDrawable
    Drawable <|-- MachineDrawable
    MachineDrawable ..> IMachineSystem : adapts
```

---

### UI Layer / Observer Pattern

```mermaid
classDiagram
    class PictureObserver {
        <<abstract>>
        -shared_ptr~Picture~ mPicture
        +UpdateObserver()*
        +SetPicture(picture)
        +GetPicture() shared_ptr~Picture~
    }

    class ViewEdit {
        -wxPoint mLastMouse
        -shared_ptr~Actor~ mSelectedActor
        -shared_ptr~Drawable~ mSelectedDrawable
        -Mode mMode
        +UpdateObserver()
        +OnLeftDown(event)
        +OnMouseMove(event)
        +OnPaint(event)
    }

    class ViewTimeline {
        -wxTimer mTimer
        -wxStopWatch mStopWatch
        -bool mPlaying
        -bool mMovingPointer
        +UpdateObserver()
        +OnPaint(event)
        +OnTimer(event)
        +Stop()
    }

    class Picture {
        -vector~PictureObserver*~ mObservers
        +AddObserver(observer)
        +RemoveObserver(observer)
        +UpdateObservers()
    }

    class MainFrame {
        -ViewEdit* mViewEdit
        -ViewTimeline* mViewTimeline
        -shared_ptr~Picture~ mPicture
        +Initialize()
    }

    PictureObserver <|-- ViewEdit
    PictureObserver <|-- ViewTimeline
    Picture "1" o-- "many" PictureObserver : notifies
    MainFrame *-- ViewEdit
    MainFrame *-- ViewTimeline
    MainFrame *-- Picture
```

---

### Factory Pattern

```mermaid
classDiagram
    class PictureFactory {
        +Create(resourcesDir) shared_ptr~Picture~
    }

    class HaroldFactory {
        +Create(imagesDir) shared_ptr~Actor~
    }

    class SpartyFactory {
        +Create(imagesDir) shared_ptr~Actor~
    }

    class Picture {
    }

    class Actor {
    }

    PictureFactory ..> Picture : creates
    PictureFactory ..> HaroldFactory : uses
    PictureFactory ..> SpartyFactory : uses
    HaroldFactory ..> Actor : creates
    SpartyFactory ..> Actor : creates
```

---

## Design Patterns

### 1. Observer Pattern
**Where:** `Picture` (Subject) → `PictureObserver` → `ViewEdit`, `ViewTimeline`

`Picture` maintains a list of observers. When the animation time changes or state is modified, `Picture::UpdateObservers()` notifies all registered views to redraw themselves. This decouples the domain model from the UI completely.

```
Picture::UpdateObservers()
    └─► ViewEdit::UpdateObserver()     → redraws canvas
    └─► ViewTimeline::UpdateObserver() → redraws timeline
```

---

### 2. Factory Method Pattern
**Where:** `PictureFactory`, `HaroldFactory`, `SpartyFactory`

Character construction is encapsulated in dedicated factory classes. `PictureFactory::Create()` assembles the full scene by delegating character creation to `HaroldFactory` and `SpartyFactory`, keeping complex object construction outside of the domain classes themselves.

---

### 3. Composite Pattern
**Where:** `Drawable` parent/child tree inside each `Actor`

Each `Drawable` can have child `Drawable` objects, forming a tree. `Place()` recursively propagates position and rotation transformations down the tree — so moving a body part (e.g. torso) automatically moves all attached children (arms, head, etc.).

```
Actor
 └── Body (PolyDrawable)           ← root
      ├── LeftArm (PolyDrawable)
      ├── RightArm (PolyDrawable)
      └── HeadTop (HeadTop)
           ├── LeftEye (RotatedBitmap)
           └── RightEye (RotatedBitmap)
```

---

### 4. Adapter Pattern
**Where:** `MachineDrawable` adapts `IMachineSystem` into `Drawable`

The external machine library exposes an `IMachineSystem` interface. `MachineDrawable` wraps it as a standard `Drawable`, allowing machines to be inserted into an `Actor`'s drawable tree and participate in the animation timeline without any changes to the machine library.

```
Drawable (interface expected by the system)
    └── MachineDrawable
            └── IMachineSystem  ← external API, unchanged
```

---

### 5. Template Method Pattern
**Where:** `AnimChannel` base class

`AnimChannel::SetFrame()` is the template method — it calls the abstract `Tween(t)` and `XmlLoadKeyframe(node)` hooks, which subclasses (`AnimChannelAngle`, `AnimChannelPoint`) implement with type-specific interpolation logic. The frame-selection algorithm is shared; only the data-type behavior varies.

---

## Component Descriptions

| Class | Role |
|---|---|
| `CanadianExperienceApp` | wxWidgets application entry point (`OnInit`) |
| `MainFrame` | Top-level window; owns `ViewEdit`, `ViewTimeline`, and `Picture` |
| `Picture` | Central scene object — holds all actors, the timeline, and machine references |
| `Actor` | A character in the scene. Owns a tree of `Drawable` parts and a position `AnimChannelPoint` |
| `Drawable` | Abstract base for a single visual component. Has position, rotation, parent/child links, and an angle channel |
| `ImageDrawable` | Renders a bitmap image at a computed position/rotation |
| `HeadTop` | Extends `ImageDrawable` to draw procedural eyes and eyebrows; has its own `AnimChannelPoint` for head position |
| `PolyDrawable` | Renders a filled polygon from a list of points |
| `MachineDrawable` | Adapts `IMachineSystem` into the `Drawable` interface |
| `RotatedBitmap` | Utility for rendering a bitmap with arbitrary rotation |
| `Timeline` | Tracks frame count, frame rate, current time; owns all registered `AnimChannel` pointers |
| `AnimChannel` | Abstract channel storing keyframes for one animatable property |
| `AnimChannelAngle` | Concrete channel that interpolates `double` angles (radians) |
| `AnimChannelPoint` | Concrete channel that interpolates `wxPoint` positions |
| `PictureObserver` | Abstract observer; subclassed by any UI view that needs to react to picture changes |
| `ViewEdit` | Scrollable canvas showing the scene; handles mouse selection, move, and rotate |
| `ViewTimeline` | Scrollable canvas showing the animation timeline; handles playback, keyframe setting |
| `PictureFactory` | Assembles a `Picture` with actors and machines from resource directories |
| `HaroldFactory` | Builds the Harold character as an `Actor` with attached drawables |
| `SpartyFactory` | Builds the Sparty character as an `Actor` with attached drawables |

---

## Data Flow

### Rendering Flow

```
MainFrame::Initialize()
    └─► PictureFactory::Create()
            └─► HaroldFactory::Create()  → builds Actor + Drawables
            └─► SpartyFactory::Create()  → builds Actor + Drawables
            └─► MachineDrawable created  → wraps IMachineSystem

ViewEdit::OnPaint()
    └─► Picture::Draw(graphics)
            └─► for each Actor
                    └─► Actor::Draw(graphics)
                            └─► Drawable::Place(offset, rotate)  ← recursive tree traversal
                            └─► Drawable::Draw(graphics)
```

### Animation Flow

```
User drags timeline pointer
    └─► ViewTimeline::OnMouseMove()
            └─► Picture::SetAnimationTime(t)
                    └─► Timeline::SetCurrentTime(t)
                            └─► for each AnimChannel
                                    └─► AnimChannel::SetFrame(frame)
                                            └─► Tween(t)  ← interpolates keyframes
                    └─► Picture::UpdateObservers()
                            └─► ViewEdit::UpdateObserver()   → Refresh()
                            └─► ViewTimeline::UpdateObserver() → Refresh()
```

### Keyframe Save/Load (XML)

```
Picture::Save(filename)
    └─► Timeline::Save(xmlRoot)
            └─► for each AnimChannel
                    └─► AnimChannel::XmlSave(node)
                            └─► for each Keyframe
                                    └─► Keyframe::XmlSave(node)

Picture::Load(filename)
    └─► Timeline::Load(xmlRoot)
            └─► AnimChannel::XmlLoad(node)
                    └─► XmlLoadKeyframe(node)  ← creates typed Keyframe objects
```
