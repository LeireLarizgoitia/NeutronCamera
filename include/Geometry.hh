#ifndef NCameraGeometry_hh
#define NCameraGeometry_hh 1

#include "G4SystemOfUnits.hh"
#include "G4Types.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4SDManager.hh"
#include "G4GenericMessenger.hh"
#include "SensitiveDetector.hh"

#include "Param.hh"

namespace NCamera
{
class Construction: public G4VUserDetectorConstruction
{
public:
    Construction();
    ~Construction();


    virtual G4VPhysicalVolume *Construct();
    void ConstructMaterials();
    void DefineParameters();


private:
    G4GenericMessenger* msg_;

    G4double distance_plane;
    G4double scin_distance;
    G4double scin_rad = 2*2.54*cm/2;


    //Plane 1
    G4LogicalVolume * logicScinP1_1_;
    G4LogicalVolume * logicScinP1_2_;
    G4LogicalVolume * logicScinP1_3_;
    G4LogicalVolume * logicScinP1_4_;
    //Plane 2
    G4LogicalVolume * logicScinP2_1_;
    G4LogicalVolume * logicScinP2_2_;
    G4LogicalVolume * logicScinP2_3_;
    G4LogicalVolume * logicScinP2_4_;


    virtual void ConstructSDandField();
    G4VPhysicalVolume* DefineVolumes();
};

}
#endif
