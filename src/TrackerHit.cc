#include "TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

namespace NCamera
{

G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerHit::TrackerHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerHit::~TrackerHit() {}


G4bool TrackerHit::operator==(const TrackerHit& right) const
{
  return ( this == &right ) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerHit::Print()
{
  /*
  G4cout
     << "Edep: "
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << " position: "
     << std::setw(7) << G4BestUnit(fPos,"Length")
     << G4endl;
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
