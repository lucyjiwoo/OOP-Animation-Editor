/**
 * @file RotationSource.cpp
 * @author Jiwoo Jeong
 */
#include "pch.h"
#include "RotationSource.h"
#include "IRotationSink.h"
#include "Component.h"
/**
 * Constructor
 * @param component
 */
RotationSource::RotationSource(Component *component) : mComponent(component)
{

}
/**
 * Add the sink of this source
 * @param sink The sink object by this source
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> sink)
{
    mSinks.push_back(sink);
}
/**
 * Rotate the sinks of this source
 * @param rotation rotation of the source
 * @param speed speed of the source
 */
void RotationSource::Rotate(double rotation, double speed)
{
    for (auto sink : mSinks){
        sink->Rotate(rotation, speed);
    }
}
