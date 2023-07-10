#ifndef NCameraTrackerHit_h
#define NCameraTrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4THitsMap.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

namespace NCamera
{

/// Tracker hit class
///
/// It defines data members to store the the energy deposit and track lengths
/// of charged particles in a selected volume:
/// - fEdep, fTrackLength

class TrackerHit : public G4VHit
{
  public:
    TrackerHit();
    TrackerHit(const TrackerHit&) = default;
    ~TrackerHit() override;

    // Operators (from G4Trajectory.hh)
    TrackerHit& operator=(const TrackerHit&) = default;
    G4bool operator==(const TrackerHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    void Draw()  override{}
    void Print() override;

   // Getters and setters
   // Proper time of the current track
    //inline G4double GetProperTime() const
    //{ return fPTime; }
    //inline void SetProperTime(const G4double ptime)
    //{ fPTime = ptime; }


    // Set methods
    void SetTrackID       (G4int track)      { fTrackID = track; };
    void SetParentID      (G4int parent)     { fParentID = parent; };
    void SetParticleName  (G4String name)    { fParticleName = name; };
    void SetEdep          (G4double de)      { fEdep = de; };
    void SetGlobalTime    (G4double gtime)   { fGTime = gtime; };
    void SetProperTime    (G4double ptime)   { fPTime = ptime; };
    void SetPos           (G4ThreeVector xyz){ fPos = xyz; };
    void SetVertexPos     (G4ThreeVector xyz){ fVertexPos = xyz; };
    void SetInitialVolume (G4String name)    { fInitVolume = name; };
    void SetFinalVolume   (G4String name)    { fFinalVolume = name; };
    void SetCreatorProcess(G4String name)    { fCreator    = name; };

    void SetInitialPos         (G4ThreeVector xyz){ fPosInit = xyz; };
    void SetFinalPos           (G4ThreeVector xyz){ fPosFin = xyz; };

    // Get methods
    G4int GetTrackID() const           { return fTrackID; };
    G4int GetParentID() const          { return fParentID; };
    G4String GetParticleName() const   { return fParticleName; };
    G4double GetEdep() const           { return fEdep; };
    G4double GetGlobalTime() const     { return fGTime; };
    G4double GetProperTime() const     { return fPTime; };
    G4ThreeVector GetPos() const       { return fPos; };
    G4ThreeVector GetVertexPos() const { return fVertexPos; };
    G4String GetInitialVolume() const  { return fInitVolume; };
    G4String GetFinalVolume() const  { return fFinalVolume; };
    G4String GetCreatorProcess() const { return fCreator; };
    G4ThreeVector GetInitialPosition() const { return fPosInit; };
    G4ThreeVector GetFinalPosition() const { return fPosFin; };



  private:
    G4int         fTrackID = -1;
    G4int         fParentID = -1;
    G4double      fEdep = 0.;
    G4double      fGTime = 0.;
    G4double      fPTime;
    G4ThreeVector fPos;
    G4ThreeVector fVertexPos;
    G4String      fParticleName;
    G4String      fInitVolume;
    G4String      fFinalVolume;
    G4String      fCreator;
    G4ThreeVector fPosInit;
    G4ThreeVector fPosFin;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//using TrackerHitsCollection = G4THitsMap<TrackerHit>;
using TrackerHitsCollection = G4THitsMap<TrackerHit>;

extern G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerHit::operator new(size_t)
{
  if (!TrackerHitAllocator) {
    TrackerHitAllocator = new G4Allocator<TrackerHit>;
  }
  //void *hit;
  //hit = (void *) TrackerHitAllocator->MallocSingle();
  //return hit;
  return	(void	*)	TrackerHitAllocator->MallocSingle();
}

inline void TrackerHit::operator delete(void *hit)
{
  if (!TrackerHitAllocator) {
    TrackerHitAllocator = new G4Allocator<TrackerHit>;
  }
  TrackerHitAllocator->FreeSingle((TrackerHit*) hit);
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
