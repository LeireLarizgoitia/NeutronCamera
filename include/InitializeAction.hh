#ifndef NCameraInitializeAction_hh
#define NCameraInitializeAction_hh 1

#include "PrimaryGeneratorAction.hh"

#include "G4VUserActionInitialization.hh"

namespace NCamera
{
class InitializeAction: public G4VUserActionInitialization
{
public:
    InitializeAction();
    ~InitializeAction();

    virtual void Build() const;
    virtual void BuildForMaster() const;


};
}
#endif
