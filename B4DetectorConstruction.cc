//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4DetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4TessellatedSolid.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4QuadrangularFacet.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnionSolid.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger *B4DetectorConstruction::fMagFieldMessenger = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
        : G4VUserDetectorConstruction(),
          cAbsorberPV(0),
          tAbsorberPV(0),
          bAbsorberPV(0),
          lAbsorberPV(0),
          rAbsorberPV(0),
          fGapPV(0),
          fCheckOverlaps(true) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *B4DetectorConstruction::Construct() {
    // Define materials
    DefineMaterials();

    // Define volumes
    return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials() {
    G4NistManager *man = G4NistManager::Instance();

    G4bool isotopes = false;

    G4Element *O = man->FindOrBuildElement("O", isotopes);
    G4Element *Si = man->FindOrBuildElement("Si", isotopes);
    G4Element *Lu = man->FindOrBuildElement("Lu", isotopes);
    G4Element *Y = man->FindOrBuildElement("Y", isotopes);
    // double x = 0.7;
    G4Material *LYSO = new G4Material("LYSO", 7.4 * g / cm3, 4);
    LYSO->AddElement(Lu, 6);
    LYSO->AddElement(Si, 10);
    LYSO->AddElement(O, 50);
    LYSO->AddElement(Y, 14);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *B4DetectorConstruction::DefineVolumes() {
    // Geometry parameters





    G4cout << "XY_Size (mm): " << G4endl;
    G4double xySize;
    G4cin >> xySize;

  //  G4double xySize = 3;
    G4double crystalSizeXY = xySize * mm;
    G4double crystalSizeZ = 22 * mm;
    G4double gap = 1 * mm;
    G4double spadnetXY = (crystalSizeXY+gap)*3 * mm;
    G4double spadnetZ = 10 * mm;


    G4double worldSizeXY = crystalSizeXY*10;
    G4double worldSizeZ = crystalSizeZ+spadnetZ *10;


    //  G4int xNoCrys = 3;
    //G4int yNoCrys = 3;

    // Get materials
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *defaultMaterial = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *absorberMaterial = nist->FindOrBuildMaterial("LYSO");
    G4Material *foilMaterial = nist->FindOrBuildMaterial("G4_Al");
    G4Material *spadnetMaterial = nist->FindOrBuildMaterial("G4_Si");

    if (!defaultMaterial || !absorberMaterial) {
        G4ExceptionDescription msg;
        msg << "Cannot retrieve materials already defined.";
        G4Exception("B4DetectorConstruction::DefineVolumes()",
                    "MyCode0001", FatalException, msg);
    }

    //
    // World
    //
    G4VSolid *worldS
            = new G4Box("World",           // its name
                        worldSizeXY / 2, worldSizeXY / 2, worldSizeZ / 2); // its size

    G4LogicalVolume *worldLV
            = new G4LogicalVolume(
                    worldS,           // its solid
                    defaultMaterial,  // its material
                    "World");         // its name

    G4VPhysicalVolume *worldPV
            = new G4PVPlacement(
                    0,                // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    worldLV,          // its logical volume
                    "World",          // its name
                    0,                // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    fCheckOverlaps);  // checking overlaps
    //Absorber geometry
    G4VSolid *absorberS
            = new G4Box("Abso",            // its name
                        crystalSizeXY / 2, crystalSizeXY / 2, crystalSizeZ / 2);

    //Foil geometry
    G4VSolid *outerBox
            = new G4Box("outerBox",            // its name
                        crystalSizeXY / 2 + gap / 2, crystalSizeXY / 2 + gap / 2,
                        crystalSizeZ / 2); // its size
    G4SubtractionSolid *foil = new G4SubtractionSolid("Foil", outerBox, absorberS);

    G4LogicalVolume *foilLV
            = new G4LogicalVolume(
                    foil,        // its solid
                    foilMaterial, // its material
                    "Foil");          // its name




    G4LogicalVolume *absorberLV
            = new G4LogicalVolume(
                    absorberS,        // its solid
                    absorberMaterial, // its material
                    "Abso");          // its name



    cAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(0, 0, 0), // its position
            absorberLV,       // its logical volume
            "Abso",           // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            1,              // copy number
            fCheckOverlaps);  // checking overlaps

    tAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(0, crystalSizeXY + gap, 0), // its position
            absorberLV,       // its logical volume
            "Abso",           // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            2,              // copy number
            fCheckOverlaps);  // checking overlaps
    bAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(0, -crystalSizeXY - gap, 0), // its position
            absorberLV,       // its logical volume
            "Abso",           // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            3,              // copy number
            fCheckOverlaps);  // checking overlaps
    lAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(crystalSizeXY + gap, 0, 0), // its position
            absorberLV,       // its logical volume
            "Abso",           // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            4,              // copy number
            fCheckOverlaps);  // checking overlaps
    rAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(-crystalSizeXY - gap, 0, 0), // its position
            absorberLV,       // its logical volume
            "Abso",           // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            5,              // copy number
            fCheckOverlaps);  // checking overlaps

    G4int counter = 0;
       for (G4int icrys = -1; icrys < 2; icrys++) {
           G4ThreeVector pos = G4ThreeVector(icrys * (crystalSizeXY + gap), 0, 0);
           fGapPV
                   = new G4PVPlacement(
                   0,                // no rotation
                   pos, // its position
                   foilLV,            // its logical volume
                   "Gap",            // its name
                   worldLV,          // its mother  volume
                   false,// no boolean operation
                   counter,                // copy number
                   fCheckOverlaps);  // checking overlaps
        counter += 1;
    }


    for (G4int jcrys = -1; jcrys < 2; jcrys+=2) {
        G4ThreeVector pos = G4ThreeVector( 0, (jcrys*(crystalSizeXY + gap)), 0);
        fGapPV
                = new G4PVPlacement(
                0,                // no rotation
                pos, // its position
                foilLV,            // its logical volume
                "Gap",            // its name
                worldLV,          // its mother  volume
                false,            // no boolean operation
                counter,                // copy number
                fCheckOverlaps);  // checking overlaps
        counter += 1;
    }




    // THE SPADNET Using lump of silicon to simulate effects of back scatterings off the detector


    G4VSolid *spadnet
            = new G4Box("spadnet",            // its name
                        spadnetXY/2,spadnetXY/2,spadnetZ/2); // its size


    G4LogicalVolume *spadnetLV
            = new G4LogicalVolume(
                    spadnet,        // its solid
                    spadnetMaterial, // its material
                    "spadnet");          // its name


    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(0, 0, crystalSizeZ/2+spadnetZ/2*mm),         //at (0,0,)
                      spadnetLV,            //its logical volume
                      "Patient",               //its name
                      worldLV,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      fCheckOverlaps);         // checking overlaps



//}
//}
//
// Visualization attributes
//

    worldLV->
            SetVisAttributes(G4VisAttributes::Invisible);

    G4VisAttributes *simpleBoxVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    simpleBoxVisAtt->SetVisibility(true);
    worldLV->
            SetVisAttributes(simpleBoxVisAtt);

//
// Always return the physical World
//
    return
            worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::ConstructSDandField() {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
