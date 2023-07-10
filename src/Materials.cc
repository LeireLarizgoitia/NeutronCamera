#include "Materials.hh"


namespace NCamera
{
  // Plastic Scintillator: Polyvinyl Toluene (PVT). PNNL database Vinyltouene
  G4Material* PVT()
  {
    G4String name = "PVT";

     G4Material* mat = new G4Material(name, 1.032*g/cm3,2,kStateSolid);

     G4Element* PVT_H   = new G4Element("Hydrogen"  ,"H" , 1., 1.0079*g/mole);
     G4Element* PVT_C   = new G4Element("Carbon"    ,"C" , 6., 12.01*g/mole);
     mat->AddElement(PVT_H, 0.085); // weighted fraction 0.085 , atomic fraction  0.53
     mat->AddElement(PVT_C, 0.915 ); // 0.915 | 0.47

    return mat;
  }



}
