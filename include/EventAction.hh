#ifndef NCameraEventAction_h
#define NCameraEventAction_h 1

#include "G4UserEventAction.hh"
#include "TrackerHit.hh"


#include "globals.hh"

namespace NCamera
{

/// Event action class

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    ~EventAction() override;

    void  BeginOfEventAction(const G4Event* ) override;
    void  EndOfEventAction(const G4Event* ) override;

  private:
  // methods
  TrackerHitsCollection* GetHitsCollection(G4int hcID,
                                            const G4Event* event) const;
  void PrintEventStatistics(G4double trackEdep, G4ThreeVector trackTrackLength) const;
  void FillNtuple(const G4Event* event, G4int fTrackHCID, G4int tuple_id);

  // data members
  G4int fTrackHCPlane1 = -1;
  G4int fTrackHCPlane2 = -1;

};

}

#endif
