#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
  //in order to get access to the objet we created
  fEventAction = eventAction;
}

MySteppingAction::~ MySteppingAction()
{}


//the deposited energy is stored in each step, so we have to get access to G4Step* step
void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  //in order to obtain the volume where the particle is
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4Track *track =step->GetTrack();
  G4bool first_time = step->IsFirstStepInVolume();
  G4String nameVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  //G4String processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  
  //we have to check if the volume where the particle is,
  //is the scoring volume we defined in construction.cc (thanks to GetScoringVolume1, GetScoringVolume2...)
  const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());


  //in order to know which are the scoring volumes
  G4LogicalVolume *fScoringVolume1 = detectorConstruction->GetScoringVolume1();
  G4LogicalVolume *fScoringVolume2 = detectorConstruction->GetScoringVolume2();
  G4LogicalVolume *fScoringVolume3 = detectorConstruction->GetScoringVolume3();
  G4LogicalVolume *fScoringVolume4 = detectorConstruction->GetScoringVolume4();
  G4LogicalVolume *fScoringVolume5 = detectorConstruction->GetScoringVolume5();
  
  //if the particle isn't in the first or in the second scintillator we don't have to accumulate energy
  if(nameVol == "logicWorld")
    return;

  //if the particle is in the target (fourth scintillator)
  //for every step we get the energy deposition during that step and the step lenght
  G4double edep = step->GetTotalEnergyDeposit();
  G4double steplenght = step->GetStepLength();

  
  

  //if the primary particle is in the fourth scintillator (target) we add to fEdep the energy edep deposited in the current step 
  //the second condition is necessary in order not to accumulate secondaries energy
  if(volume == fScoringVolume4 && track->GetTrackID() == 1)
  { 
    //storing energy only if positron has enetered the scintillator
    //fEventAction->SetIsPassed1();
    //accumulating the energy deposition step by step
    //G4cout << "edep: " << edep << G4endl;
    //G4cout << "steplenght: " << steplenght << G4endl;
    fEventAction->AddEdep(edep);

    //calculating the path inside the target, step by step
    fEventAction->AddStepLenght(steplenght);

    /*
    //filling the column with the process done at each step
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleSColumn(4,0,processName);
    man->AddNtupleRow(4);
    */

    //filling the column of the tuple with the energy deposition at each step
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0,3,edep);
    
  }

  //as soon as the particle enters the scintillator isPassed becomes true
  if(volume == fScoringVolume1 && track->GetTrackID() == 1 && first_time == true)
  {
    fEventAction->SetIsPassed1();

  }


  //as soon as the particle enters the scintillator isPassed becomes true
  if(volume == fScoringVolume2 && track->GetTrackID() == 1 && first_time == true)
  {
    fEventAction->SetIsPassed2();

  }

  //as soon as the particle enters the scintillator isPassed becomes true
  if(volume == fScoringVolume3 && track->GetTrackID() == 1 && first_time == true)
  {
    fEventAction->SetIsPassed3();

  }

  /*
  if(volume == fScoringVolume4 && track->GetTrackID() == 1 && first_time == true)
  {
    fEventAction->SetIsPassed4();

  }
  */


  //as soon as the particle enters the last scintillator isPassed5 becomes true
  if(volume == fScoringVolume5 && track->GetTrackID() == 1 && first_time == true)
  {
    fEventAction->SetIsPassed5();

  }

  /*
  //if the particle is in the second scintillator and it's the initial positron we add to fEdep2 the energy edep deposited in the current step 
  if(volume == fScoringVolume2 && track->GetTrackID() == 1)
  {
    fEventAction->SetIsPassed2();
    
    //accumulating the energy deposition step by step
    fEventAction->AddEdep2(edep);
    fEventAction->AddStepLenght2(steplenght);
    //filling the column with the process done at each step
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleSColumn(5,0,processName);
    man->AddNtupleRow(5);
  }
  
  */



}
