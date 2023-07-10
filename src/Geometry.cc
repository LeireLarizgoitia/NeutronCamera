
/// \file Construction.cc
/// \brief Implementation of the NCamera::Construction class


#include "Geometry.hh"
#include "Materials.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"
#include <G4GenericMessenger.hh>
#include <G4PhysicalConstants.hh>

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

namespace NCamera
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Construction::Construction()
{   DefineParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Construction::~Construction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* Construction::Construct()
{
  // Define volumes
  return DefineVolumes();
}

G4VPhysicalVolume* Construction::DefineVolumes()
{

  // Construct materials form NIST database
  ConstructMaterials();
  // Get materials
  auto* vacuum     = G4Material::GetMaterial("G4_Galactic");
  auto* air        = G4Material::GetMaterial("G4_AIR");
  auto* alumina    = G4Material::GetMaterial("G4_ALUMINUM_OXIDE");
  auto* pvt        = PVT();

  if ( ! vacuum || ! air || ! alumina || ! pvt ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("Construction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  //G4cout<< "DISTANCE "<< distance_plane << G4endl;

    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;

    // World definition
    G4double world_size_x = 20*m/2;
    G4double world_size_y = 20*m/2;
    G4double world_size_z = 20*m/2;

    G4double inch = 2.54*cm;

    G4Box *solidWorld  = new G4Box("solidWorld",
                                     world_size_x, world_size_y, world_size_z);

    G4LogicalVolume   *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume *physWorld  = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.),
                                                     logicWorld, "physWorld",
                                                     0,
                                                     false, 0, checkOverlaps);

    ////////////////////////////////////
    //
    // ALUMINA STRUCTURE
    //
    ////////////////////////////////////

    // Al Profile Plane (P1 , P2)
    G4double profile_thick  = 3.*cm; //stut

    G4double innerprofile_length = scin_distance/2 + scin_rad;
    G4double profile_length = 2*(innerprofile_length + profile_thick);

    G4Box *solid_profile  = new G4Box("solidAlProfile",
                                     profile_length/2, profile_thick/2, profile_length/2);

    G4Box *solid_inner_profile  = new G4Box("solidInnerProfile",
                                            innerprofile_length, profile_thick/2 +1*mm, innerprofile_length);

    G4VSolid* sub_ProfilePlane = new G4SubtractionSolid("sub_ProfilePlane",
                                                    solid_profile, solid_inner_profile,0,G4ThreeVector());

    G4LogicalVolume *logic_profileP1 = new G4LogicalVolume(sub_ProfilePlane, alumina, "logicAlProfilePlane1");
    G4LogicalVolume *logic_profileP2 = new G4LogicalVolume(sub_ProfilePlane, alumina, "logicAlProfilePlane2");

    new G4PVPlacement(0, G4ThreeVector(0, -distance_plane/2 ,0 ),
                      logic_profileP1, "physAlProfile_P1", logicWorld,
                      false, 0, checkOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0, +distance_plane/2 ,0 ),
                      logic_profileP2, "physAlProfile_P2", logicWorld,
                      false, 0, checkOverlaps);

    // Al Profile that joins the two planes
    G4double guideprofile_length = (distance_plane - profile_thick)/2;
    G4Box *solid_guideprofile  = new G4Box("solidGuideProfile",
                                     profile_thick/2, guideprofile_length, profile_thick/2);

    G4double al_profile_pos   = profile_length/2 - profile_thick/2;

    G4ThreeVector Profile_Ps1 = G4ThreeVector(al_profile_pos, 0 , al_profile_pos);
    G4ThreeVector Profile_Ps2 = G4ThreeVector(al_profile_pos, 0 , -al_profile_pos);
    G4ThreeVector Profile_Ps3 = G4ThreeVector(-al_profile_pos, 0 , al_profile_pos);
    G4ThreeVector Profile_Ps4 = G4ThreeVector(-al_profile_pos, 0 , -al_profile_pos);

    G4LogicalVolume *logic_guideprofile1 = new G4LogicalVolume(solid_guideprofile, alumina, "logicGuideAlProfile_1");
    G4LogicalVolume *logic_guideprofile2 = new G4LogicalVolume(solid_guideprofile, alumina, "logicGuideAlProfile_2");
    G4LogicalVolume *logic_guideprofile3 = new G4LogicalVolume(solid_guideprofile, alumina, "logicGuideAlProfile_3");
    G4LogicalVolume *logic_guideprofile4 = new G4LogicalVolume(solid_guideprofile, alumina, "logicGuideAlProfile_4");

    new G4PVPlacement(0, Profile_Ps1,
                     logic_guideprofile1, "physGuideAlProfile_1", logicWorld,
                     false, 0, checkOverlaps);
    new G4PVPlacement(0, Profile_Ps2,
                     logic_guideprofile2, "physGuideAlProfile_2", logicWorld,
                     false, 0, checkOverlaps);
    new G4PVPlacement(0, Profile_Ps3,
                     logic_guideprofile3, "physGuideAlProfile_3", logicWorld,
                     false, 0, checkOverlaps);
    new G4PVPlacement(0, Profile_Ps4,
                     logic_guideprofile4, "physGuideAlProfile_4", logicWorld,
                     false, 0, checkOverlaps);

    ////////////////////////////////////
    //
    // SCINTILLATOR
    //
    ////////////////////////////////////

    // Plastic scintillator
    //G4double scin_rad = 2 *inch;
    G4double scin_h   = 2 *inch/2;
    G4Tubs *solidScin  = new G4Tubs("solidScin",
                                    0., scin_rad, scin_h, 0.,360.*deg);

    G4double scin_pos = scin_distance/2;

    //G4cout << "Distance between two parallel scintillators in the same plane: " << 2*scin_pos << " mm" << G4endl;
    //G4cout << "Thickness of the Al profile and the Scintillator: " << profile_thick + scin_rad << " mm" << G4endl;
    //G4cout << "Distance of the Al profile : " << 2*(scin_pos + profile_thick + scin_rad) << " mm" << G4endl;


    //Plane 1
    G4ThreeVector ScinP1_Ps1 = G4ThreeVector(scin_pos , -distance_plane/2, 0 );
    G4ThreeVector ScinP1_Ps2 = G4ThreeVector(-scin_pos ,-distance_plane/2, 0 );
    G4ThreeVector ScinP1_Ps3 = G4ThreeVector(0,-distance_plane/2, -scin_pos);
    G4ThreeVector ScinP1_Ps4 = G4ThreeVector(0,-distance_plane/2, scin_pos);
    //Plane 2
    G4ThreeVector ScinP2_Ps1 = G4ThreeVector(scin_pos,distance_plane/2, 0 );
    G4ThreeVector ScinP2_Ps2 = G4ThreeVector(-scin_pos,distance_plane/2, 0 );
    G4ThreeVector ScinP2_Ps3 = G4ThreeVector(0,distance_plane/2, -scin_pos);
    G4ThreeVector ScinP2_Ps4 = G4ThreeVector(0,distance_plane/2, scin_pos);


    G4RotationMatrix* RotZ = new G4RotationMatrix();
                          RotZ->rotateZ(90*deg);
                          //Rot->rotateZ(90*deg);

    G4RotationMatrix* RotY = new G4RotationMatrix();
                          RotY->rotateY(90*deg);
                          //RotXY->rotateX(90*deg);

    logicScinP1_1_ = new G4LogicalVolume(solidScin, pvt, "logicScinP1_1");
    logicScinP1_2_ = new G4LogicalVolume(solidScin, pvt, "logicScinP1_2");
    logicScinP1_3_ = new G4LogicalVolume(solidScin, pvt, "logicScinP1_3");
    logicScinP1_4_ = new G4LogicalVolume(solidScin, pvt, "logicScinP1_4");

    logicScinP2_1_ = new G4LogicalVolume(solidScin, pvt, "logicScinP2_1");
    logicScinP2_2_ = new G4LogicalVolume(solidScin, pvt, "logicScinP2_2");
    logicScinP2_3_ = new G4LogicalVolume(solidScin, pvt, "logicScinP2_3");
    logicScinP2_4_ = new G4LogicalVolume(solidScin, pvt, "logicScinP2_4");


    // Plane 1
    new G4PVPlacement(RotY, ScinP1_Ps1,
                     logicScinP1_1_, "physScinP1_1", logicWorld,
                     false, 0, checkOverlaps);

    new G4PVPlacement(RotY, ScinP1_Ps2,
                    logicScinP1_2_, "physScinP1_2", logicWorld,
                    false, 0, checkOverlaps);

    new G4PVPlacement(RotZ, ScinP1_Ps3,
                     logicScinP1_3_, "physScinP1_3", logicWorld,
                     false, 0, checkOverlaps);

    new G4PVPlacement(RotZ, ScinP1_Ps4,
                      logicScinP1_4_, "physScinP1_4", logicWorld,
                      false, 0, checkOverlaps);
    // Plane 2
    new G4PVPlacement(RotY, ScinP2_Ps1,
                     logicScinP2_1_, "physScinP2_1", logicWorld,
                     false, 0, checkOverlaps);

    new G4PVPlacement(RotY, ScinP2_Ps2,
                    logicScinP2_2_, "physScinP2_2", logicWorld,
                    false, 0, checkOverlaps);

    new G4PVPlacement(RotZ, ScinP2_Ps3,
                     logicScinP2_3_, "physScinP2_3", logicWorld,
                     false, 0, checkOverlaps);

     new G4PVPlacement(RotZ, ScinP2_Ps4,
                      logicScinP2_4_, "physScinP2_4", logicWorld,
                      false, 0, checkOverlaps);


  //
  // Always return the physical World
  //
  return physWorld;
}


void Construction::DefineParameters()
{
  // Define /NCamera/geometry command directory using generic messenger class
  msg_ = new G4GenericMessenger(this,
                            "/NCamera/Geometry/",
                            "Geometry control");
  ///Distance between detector planes.
  //distance_plane = 1*m;
   G4GenericMessenger::Command& distance_plane_cmd =
   msg_->DeclareProperty("distance_plane",distance_plane,
   				"Distance between detector planes.");
   distance_plane_cmd.SetUnitCategory("Length");
   distance_plane_cmd.SetParameterName("distance_plane",false); //omittible
   distance_plane_cmd.SetRange("distance_plane>0.");

   ///Distance between scintillators in same plane
   G4GenericMessenger::Command& scin_distance_cmd =
   msg_->DeclareProperty("scin_distance",scin_distance,
   				"Distance between scintillators in same plane.");
   scin_distance_cmd.SetUnitCategory("Length");
   scin_distance_cmd.SetParameterName("scin_distance",false);
   scin_distance_cmd.SetRange("scin_distance>0.");

}


void Construction::ConstructMaterials()
{
  //G4cout << G4endl << "The materials defined are from NIST : " << G4endl << G4endl;
  auto nistManager = G4NistManager::Instance();
  // Air
  nistManager->FindOrBuildMaterial("G4_AIR");
  // Vacuum
  nistManager->FindOrBuildMaterial("G4_Galactic");
  // Alumina
  nistManager->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");

}


void Construction::ConstructSDandField() //SD : Sensitive Detector
{

  G4String sdNamePlane1 = "NCamera/TrackerPlane1";
  SensitiveDetector* sensDetPlane1 = new SensitiveDetector(sdNamePlane1, "HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(sensDetPlane1);

  SetSensitiveDetector(logicScinP1_1_,  sensDetPlane1 );
  SetSensitiveDetector(logicScinP1_2_,  sensDetPlane1 );
  SetSensitiveDetector(logicScinP1_3_,  sensDetPlane1 );
  SetSensitiveDetector(logicScinP1_4_,  sensDetPlane1 );

  //Plane 2
  G4String sdNamePlane2 = "NCamera/TrackerPlane2";
  SensitiveDetector* sensDetPlane2 = new SensitiveDetector(sdNamePlane2, "Plane2_HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(sensDetPlane2);

  SetSensitiveDetector(logicScinP2_1_,  sensDetPlane2 );
  SetSensitiveDetector(logicScinP2_2_,  sensDetPlane2 );
  SetSensitiveDetector(logicScinP2_3_,  sensDetPlane2 );
  SetSensitiveDetector(logicScinP2_4_,  sensDetPlane2 );

}


}
