#ifndef NCameraPhysics_hh
#define NCameraPhysics_hh 1

#include "G4VModularPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "GammaNuclearPhysics.hh"

namespace NCamera
{
class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList();
    ~PhysicsList();
};
}
#endif
