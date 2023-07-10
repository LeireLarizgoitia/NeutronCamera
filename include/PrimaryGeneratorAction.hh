#ifndef NCameraGenerator_hh
#define NCameraGenerator_hh 1

#include "G4RunManager.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include <G4VUserDetectorConstruction.hh>

#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include <G4RandomDirection.hh>
#include "G4GenericMessenger.hh"
#include "Randomize.hh"

namespace NCamera
{
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

private:
    //G4ParticleGun* fParticleGun = nullptr; // pointer a to G4 gun class
    G4GeneralParticleSource* fParticleGun = nullptr; // pointer a to G4 gun class


    G4GenericMessenger* fMessenger;

    G4double fRad;
    G4double fEnergy;

private:
    void DefineCommands();
};
}
#endif
