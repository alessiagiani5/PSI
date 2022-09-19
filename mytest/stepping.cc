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
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

  //if volume != fScoringVolume we don't want to accumulate energy deposition
  if(volume != fScoringVolume)
    return;

  //for every step we get the energy deposition in all volume
  G4double edep = step->GetTotalEnergyDeposit();

  //accumulating the energy deposition step by step
  fEventAction->AddEdep(edep);

}
