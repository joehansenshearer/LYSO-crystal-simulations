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
// $Id: B4aEventAction.cc 75604 2013-11-04 13:17:26Z gcosmo $
// 
/// \file B4aEventAction.cc
/// \brief Implementation of the B4aEventAction class

#include "B4aEventAction.hh"
#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aEventAction::B4aEventAction()
        : G4UserEventAction(),
          cEnergyAbs(0.),
          tEnergyAbs(0.),
          bEnergyAbs(0.),
          lEnergyAbs(0.),
          rEnergyAbs(0.) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aEventAction::~B4aEventAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aEventAction::BeginOfEventAction(const G4Event * /*event*/) {
    // initialisation per event
    cEnergyAbs = 0.;
    tEnergyAbs = 0.;
    bEnergyAbs = 0.;
    lEnergyAbs = 0.;
    rEnergyAbs = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aEventAction::EndOfEventAction(const G4Event *event) {
    // Accumulate statistics
    //

    // get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // fill histograms
    analysisManager->FillH1(1, cEnergyAbs);
    analysisManager->FillH1(2, tEnergyAbs);
    analysisManager->FillH1(3, bEnergyAbs);
    analysisManager->FillH1(4, lEnergyAbs);
    analysisManager->FillH1(5, rEnergyAbs);

    // fill ntuple
    if (cEnergyAbs != 0) {
        G4cout << "Energy Absorbed: " << cEnergyAbs << G4endl;
        analysisManager->FillNtupleDColumn(0,0, cEnergyAbs);
        analysisManager->AddNtupleRow(0);
    }
    if (tEnergyAbs != 0) {
        analysisManager->FillNtupleDColumn(1,0, tEnergyAbs);
        analysisManager->AddNtupleRow(1);
    }
    if (bEnergyAbs != 0) {
        analysisManager->FillNtupleDColumn(2,0, bEnergyAbs);
        analysisManager->AddNtupleRow(2);
    }
    if (lEnergyAbs != 0) {
        analysisManager->FillNtupleDColumn(3,0, lEnergyAbs);
        analysisManager->AddNtupleRow(3);
    }
    if (rEnergyAbs != 0) {
        analysisManager->FillNtupleDColumn(4,0, rEnergyAbs);
        analysisManager->AddNtupleRow(4);
    }

  // analysisManager->AddNtupleRow(0);
  //  analysisManager->AddNtupleRow(1);
   // analysisManager->AddNtupleRow(2);
    //analysisManager->AddNtupleRow(3);
    //analysisManager->AddNtupleRow(4);

    //analysisManager->AddNtupleRow();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
