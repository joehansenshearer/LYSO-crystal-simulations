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
// $Id: B4aSteppingAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file B4aSteppingAction.cc
/// \brief Implementation of the B4aSteppingAction class

#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aSteppingAction::B4aSteppingAction(
                      const B4DetectorConstruction* detectorConstruction,
                      B4aEventAction* eventAction)
  : G4UserSteppingAction(),
    cDetConstruction(detectorConstruction),
    cEventAction(eventAction),
    tDetConstruction(detectorConstruction),
    tEventAction(eventAction),
    bDetConstruction(detectorConstruction),
    bEventAction(eventAction),
    lDetConstruction(detectorConstruction),
    lEventAction(eventAction),
    rDetConstruction(detectorConstruction),
    rEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aSteppingAction::~B4aSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

  // get volume of the current step
  G4VPhysicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // energy deposit
  G4double edepC = step->GetTotalEnergyDeposit();
  G4double edepT = step->GetTotalEnergyDeposit();
  G4double edepB = step->GetTotalEnergyDeposit();
  G4double edepL = step->GetTotalEnergyDeposit();
  G4double edepR = step->GetTotalEnergyDeposit();
  //

  
  // step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }
      
  if ( volume == cDetConstruction->GetCAbsorberPV()) {
    cEventAction->AddAbsC(edepC);
  }
  if ( volume == tDetConstruction->GetTAbsorberPV() ) {
    tEventAction->AddAbsT(edepT);
  }
  if ( volume == bDetConstruction->GetBAbsorberPV() ) {
    bEventAction->AddAbsB(edepB);
  }
  if ( volume == lDetConstruction->GetLAbsorberPV() ) {
    lEventAction->AddAbsL(edepL);
  }
  if ( volume == lDetConstruction->GetRAbsorberPV() ) {
    lEventAction->AddAbsR(edepR);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
