#include "PrimaryGeneratorAction.hh"


namespace NCamera
{
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    G4int nofParticles = 1;
    //fParticleGun = new G4ParticleGun(nofParticles);
    fParticleGun = new G4GeneralParticleSource();


    //DefineCommands();

    fEnergy = 10*1e6 *eV; // interested in Fast Neutrons
    fRad = 1. *cm;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    // Set Particle

    //G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    //G4String particleName = "neutron";
    //G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

    auto particleDefinition
      = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(particleDefinition);

    G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

    // Generate uniform random energy in [E_min, E_max]
    G4double kinetic_energy = fEnergy;

    // Calculate cartesian components of momentum
    G4double mass   = particle->GetPDGMass();
    G4double energy = kinetic_energy + mass;
    G4double pmod   = std::sqrt(energy*energy - mass*mass);

    // Set gun position

    G4double rad = sqrt(G4UniformRand() * fRad * fRad);
    G4double phi = G4UniformRand() * 360.*deg;
    G4double theta = G4UniformRand() * 360.*deg;

    //G4double x0 = rad * cos(phi) * sin(theta);
    //G4double y0 = rad * cos(theta);
    //G4double z0 = rad * sin(phi) * sin(theta);

    G4double x0 = 0*cm + rad * cos(phi);
    G4double y0 = -300. *cm;
    G4double z0 = -15. *cm + rad * sin(phi);

    G4ThreeVector position =  G4ThreeVector(x0,y0,z0);
    G4ThreeVector momentum =  G4ThreeVector(0., 1., 0);

    //fParticleGun->SetParticleEnergy(energy);
    //fParticleGun->SetParticlePosition(position);
    //fParticleGun->SetParticleMomentum(pmod * momentum);
    //fParticleGun->SetParticleMomentumDirection(momentum);
    //fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::DefineCommands()
{
    // Define /NCamera/generator command directory using generic messenger class
    fMessenger
      = new G4GenericMessenger(this,
                               "/NCamera/Generator/",
                               "Primary generator control");


    // energy command
    G4GenericMessenger::Command& energyCmd
      = fMessenger->DeclarePropertyWithUnit("energy", "eV", fEnergy,
                                    "Mean energy of primaries.");
    energyCmd.SetParameterName("p", true);
    energyCmd.SetRange("p>=0.");
    energyCmd.SetDefaultValue("1*1e6 eV");

    // Beam radius
    G4GenericMessenger::Command& radCmd
      = fMessenger->DeclarePropertyWithUnit("radius", "cm", fRad,
                                    "Beam radius");
    radCmd.SetParameterName("rad", true);
    radCmd.SetRange("rad>=0.");
    radCmd.SetDefaultValue("20 cm");
}



}
