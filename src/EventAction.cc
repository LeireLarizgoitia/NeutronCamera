#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "G4VTrajectory.hh"
#include "G4TrajectoryContainer.hh"



namespace NCamera
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  EventAction::EventAction()
  {
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  EventAction::~EventAction()
  {}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  TrackerHitsCollection*
  EventAction::GetHitsCollection(G4int hcID,
                                    const G4Event* event) const
  {
    auto hitsCollection
      = static_cast<TrackerHitsCollection*>(
          event->GetHCofThisEvent()->GetHC(hcID));

    if ( ! hitsCollection ) {
      G4ExceptionDescription msg;
      msg << "Cannot access hitsCollection ID " << hcID;
      G4Exception("EventAction::GetHitsCollection()",
        "MyCode0003", FatalException, msg);
    }

    return hitsCollection;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void EventAction::BeginOfEventAction(const G4Event*)
  {}


  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{

  if ( fTrackHCPlane1 == -1 ) {
  fTrackHCPlane1
   = G4SDManager::GetSDMpointer()->GetCollectionID("HitsCollection");
  }
  FillNtuple(event, fTrackHCPlane1, 0);
  if ( fTrackHCPlane2 == -1 ) {
   fTrackHCPlane2
     = G4SDManager::GetSDMpointer()->GetCollectionID("Plane2_HitsCollection");
  }
  FillNtuple(event, fTrackHCPlane2, 1);

}

 void EventAction::FillNtuple(const G4Event* event, G4int fTrackHCID, G4int tuple_id)
 {
 // Get hits collections
 auto trackHC = GetHitsCollection(fTrackHCID, event);

 // Get hit with total values
 if (trackHC->GetSize() == 0){return;}

 auto analysisManager = G4AnalysisManager::Instance();
 auto eventID = event->GetEventID();

 for (auto itr = trackHC->GetMap()->begin(); itr != trackHC->GetMap()->end(); itr++) {
   auto trackHit = itr->second;
   auto pname = trackHit->GetParticleName();
   auto ene   = trackHit->GetEdep     ();
   auto gtime = trackHit->GetGlobalTime();
   auto ptime = trackHit->GetProperTime();

   G4ThreeVector posInit = trackHit->GetInitialPosition();
   G4ThreeVector posFinal = trackHit->GetFinalPosition();

   // fill ntuples
   analysisManager->FillNtupleIColumn(tuple_id, 0, eventID);
   analysisManager->FillNtupleIColumn(tuple_id, 1, trackHit->GetTrackID());
   analysisManager->FillNtupleIColumn(tuple_id, 2, trackHit->GetParentID());
   analysisManager->FillNtupleSColumn(tuple_id, 3, trackHit->GetParticleName());
   analysisManager->FillNtupleDColumn(tuple_id, 4, ene);
   analysisManager->FillNtupleDColumn(tuple_id, 5, gtime);
   analysisManager->FillNtupleDColumn(tuple_id, 6, ptime);
   analysisManager->FillNtupleSColumn(tuple_id, 7, trackHit->GetInitialVolume());
   analysisManager->FillNtupleSColumn(tuple_id, 8, trackHit->GetFinalVolume());
   analysisManager->FillNtupleSColumn(tuple_id, 9, trackHit->GetCreatorProcess());
   analysisManager->FillNtupleDColumn(tuple_id, 10, posInit[0]);
   analysisManager->FillNtupleDColumn(tuple_id, 11, posInit[1]);
   analysisManager->FillNtupleDColumn(tuple_id, 12, posInit[2]);
   analysisManager->FillNtupleDColumn(tuple_id, 13, posFinal[0]);
   analysisManager->FillNtupleDColumn(tuple_id, 14, posFinal[1]);
   analysisManager->FillNtupleDColumn(tuple_id, 15, posFinal[2]);

   analysisManager->AddNtupleRow(tuple_id);
 }
 }

 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 }
