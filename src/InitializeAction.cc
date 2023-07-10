#include "InitializeAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

namespace NCamera
{
InitializeAction::InitializeAction()
{}

InitializeAction::~InitializeAction()
{}

void InitializeAction::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void InitializeAction::Build() const
{
    PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
    SetUserAction(generator);
    // Event action
    SetUserAction(new EventAction());
    // Run action
    SetUserAction(new RunAction());
}

}
