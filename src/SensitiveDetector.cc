#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

namespace NCamera
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetector::SensitiveDetector(const G4String& name,
                                     const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetector::~SensitiveDetector()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection
    = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool SensitiveDetector::ProcessHits(G4Step* aStep,
                                      G4TouchableHistory*)
{
  // energy deposit
  G4double edep = aStep->GetTotalEnergyDeposit(); //MeV  (* 1000; //MeV to keV)

  // step length
  //G4double stepLength = 0.;
  //if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
  //  stepLength = step->GetStepLength();
  //}
  //if ( edep==0. && stepLength == 0. ) return false;

  if (edep==0.) return false;

  auto tr      = aStep->GetTrack();
  auto trackID = tr->GetTrackID();
  auto hmap     = fHitsCollection->GetMap();
  auto track_elem = hmap->find(trackID);
  auto pname = tr->GetParticleDefinition()->GetParticleName();

  G4StepPoint *thePrePoint = aStep->GetPreStepPoint();
  G4StepPoint *thePostPoint = aStep->GetPostStepPoint();
  G4ThreeVector pre = thePrePoint->GetPosition();
  G4ThreeVector pos = thePostPoint->GetPosition();

  auto ptime = thePrePoint->GetProperTime();


  if (track_elem == hmap->end()) // (pname !="gamma"))
  {
    TrackerHit* newHit = new TrackerHit();
    newHit->SetTrackID (trackID);
    newHit->SetParentID(tr->GetParentID());

    //if      (pname=="neutron") {return true;}
    //else if (pname=="gamma")   {return true;}

    newHit->SetParticleName (pname);
    newHit->SetEdep         (edep);
    newHit->SetGlobalTime   (tr->GetGlobalTime());
    newHit->SetProperTime   (thePrePoint->GetProperTime());
    //newHit->SetPos          (aStep->GetPostStepPoint()->GetPosition());
    auto vpos = tr->GetVertexPosition();
    //newHit->SetVertexPos    (vpos);
    newHit->SetInitialVolume(thePrePoint->GetPhysicalVolume()->GetName()); //newHit->SetInitialVolume(tr->GetLogicalVolumeAtVertex()->GetName());
    newHit->SetFinalVolume(thePostPoint->GetPhysicalVolume()->GetName());
    auto creator = (tr->GetTrackID() <= 1 && pname=="neutron") ? "source" : tr->GetCreatorProcess()->GetProcessName();
    newHit->SetCreatorProcess(creator);
    newHit->SetInitialPos   (thePrePoint->GetPosition());
    newHit->SetFinalPos   (thePostPoint->GetPosition());

    hmap->insert({trackID, newHit});
  }
  else
  {
    //track_elem->SetGlobalTime(min(track_elem->GetGlobalTime(), tr->GetGlobalTime()))
    track_elem->second->SetEdep(track_elem->second->GetEdep()+edep);
  }
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
