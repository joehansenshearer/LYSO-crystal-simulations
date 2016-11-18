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
// $Id: B4DetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4DetectorConstruction.hh
/// \brief Definition of the B4DetectorConstruction class

#ifndef B4DetectorConstruction_h
#define B4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;


/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class B4DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4DetectorConstruction();
    virtual ~B4DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    virtual void ConstructSDandField();

    // get methods
    //
    const G4VPhysicalVolume* GetCAbsorberPV() const;
    const G4VPhysicalVolume* GetTAbsorberPV() const;
    const G4VPhysicalVolume* GetBAbsorberPV() const;
    const G4VPhysicalVolume* GetLAbsorberPV() const;
    const G4VPhysicalVolume* GetRAbsorberPV() const;

    const G4VPhysicalVolume* GetGapPV() const;

     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
     
    G4VPhysicalVolume*   cAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   tAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   bAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   lAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   rAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   fGapPV;      // the gap physical volume
    
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* B4DetectorConstruction::GetCAbsorberPV() const {
  return cAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetTAbsorberPV() const {
    return tAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetBAbsorberPV() const {
    return bAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetLAbsorberPV() const {
    return lAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetRAbsorberPV() const {
    return rAbsorberPV;
}

inline const G4VPhysicalVolume* B4DetectorConstruction::GetGapPV() const  { 
  return fGapPV; 
}
     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

