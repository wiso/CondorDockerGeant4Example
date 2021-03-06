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
/// \file electromagnetic/TestEm3/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//
// $Id: TrackingAction.cc 73035 2013-08-15 09:27:10Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"

#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4Positron.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(DetectorConstruction* det,RunAction* run)
:G4UserTrackingAction(),fDetector(det), fRunAct(run)
{ }
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* track )
{
  // Energy flow initialisation for primary particle
  //
  if (track->GetTrackID() == 1) {
    G4int Idnow = 1;
    if (track->GetVolume() != fDetector->GetphysiWorld()) {
      // unique identificator of layer+absorber
      const G4VTouchable* touchable = track->GetTouchable();
      G4int absorNum = touchable->GetCopyNumber();
      G4int layerNum = touchable->GetReplicaNumber(1);
      Idnow = (fDetector->GetNbOfAbsor())*layerNum + absorNum;
    }
    
    G4double Eflow = track->GetKineticEnergy();
    if (track->GetDefinition() == G4Positron::Positron())
      Eflow += 2*electron_mass_c2; 
         
    //flux artefact, if primary vertex is inside the calorimeter   
    for (G4int pl=1; pl<=Idnow; pl++) {fRunAct->SumEnergyFlow(pl, Eflow);}
  } else {
    fRunAct->AddSecondaryTrack(track);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track* )
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

