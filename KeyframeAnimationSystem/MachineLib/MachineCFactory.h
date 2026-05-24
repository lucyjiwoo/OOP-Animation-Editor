/**
 * @file MachineCFactory.h
 * @author Jiwoo Jeong
 *
 * Factory that creates just the parts of the machine
 * necessary for the checkpoint.
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINECFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINECFACTORY_H

#include <memory>
#include <string>

class Machine;

/**
 * Factory that creates just the parts of the machine
 * necessary for the checkpoint.
 */
class MachineCFactory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    MachineCFactory(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINECFACTORY_H
