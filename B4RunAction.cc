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
// $Id: B4RunAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B4RunAction.cc
/// \brief Implementation of the B4RunAction class

#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4RunAction::B4RunAction()
        : G4UserRunAction() {
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Create analysis manager
    // The choice of analysis technology is done via selectin of a namespace
    // in B4Analysis.hh
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    // Create directories
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);

    // Book histograms, ntuple
    //

    // Creating histograms
    analysisManager->CreateH1("1", "Edep in centre absorber", 10, 0., 800 * keV);
    analysisManager->CreateH1("2", "Edep in top absorber", 10, 0., 800 * keV);
    analysisManager->CreateH1("3", "Edep in bottom absorber", 10, 0., 800 * keV);
    analysisManager->CreateH1("4", "Edep in left absorber", 10, 0., 800 * keV);
    analysisManager->CreateH1("5", "Edep in right absorber", 10, 0., 800 * keV);

    // Creating ntuple
    //
    analysisManager->CreateNtuple("1", "Energy Deposited");
    analysisManager->CreateNtupleDColumn("EabsC");
    /*
    analysisManager->CreateNtupleDColumn("EabsT");


    analysisManager->CreateNtupleDColumn("EabsB");
    analysisManager->CreateNtupleDColumn("EabsL");
    analysisManager->CreateNtupleDColumn("EabsR");

    analysisManager->FinishNtuple();
   */
    analysisManager->CreateNtuple("2", "Energy Deposited");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->FinishNtuple();
    analysisManager->CreateNtuple("3", "Energy Deposited");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->FinishNtuple();
    analysisManager->CreateNtuple("4", "Energy Deposited");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->FinishNtuple();
    analysisManager->CreateNtuple("5", "Energy Deposited");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4RunAction::~B4RunAction() {
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4RunAction::BeginOfRunAction(const G4Run * /*run*/) {
    //inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

    // Get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    //

   G4cout << "Name of Root file: " << G4endl;
    G4String filename;
    G4cin >> filename;


    analysisManager->OpenFile(filename);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4RunAction::EndOfRunAction(const G4Run * /*run*/) {
    // print histogram statistics
    //
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();


    // save histograms & ntuple
    //
    analysisManager->Write();
    analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
