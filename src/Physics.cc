#include "Physics.hh"
#include "NeutronHPphysics.hh"
#include "GammaNuclearPhysics.hh"


namespace NCamera
{
PhysicsList::PhysicsList()
{
  G4int verb = 0;
  SetVerboseLevel(verb);

  // EM Physics
  RegisterPhysics(new G4EmStandardPhysics_option4(verb));
  //RegisterPhysics(new G4EmStandardPhysics(verb));

  // Synchroton Radiation & Gamma Nuclear Physics
  RegisterPhysics(new G4EmExtraPhysics(verb));

  // Decays
  RegisterPhysics(new G4DecayPhysics(verb));

  // Hadron Elastic scattering
  RegisterPhysics(new G4HadronElasticPhysicsHP(verb));

  // Hadron Physics
  RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP(verb));
  //RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP(verb));
  //RegisterPhysics(new G4HadronPhysicsQGSP_INCLXX(verb));

  // Stopping Physics
  RegisterPhysics(new G4StoppingPhysics(verb));

  // Ion Physics
  RegisterPhysics(new G4IonPhysics(verb));


  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics(verb));


  // Neutron Physics
  RegisterPhysics( new NeutronHPphysics("neutronHP"));

  // Gamma physics
  //
  RegisterPhysics( new GammaNuclearPhysics("gamma"));


  }

PhysicsList::~PhysicsList()
{}
}
