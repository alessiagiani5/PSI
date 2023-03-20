#include "event.hh"
#include "G4RunManager.hh"

MyEventAction::MyEventAction(MyRunAction*)
{/*
  //initializing the value of the deposeted energy in the target
  fEdep = 0.;

  //setting that the particle isn't passed from the trg scintillator
  isPassed1 = false;
  isPassed2 = false;
  isPassed3 = false;
  //isPassed4 = false;
  isPassed5 = false;
 
  
  //initializing the value of the total path inside the two scintillators
  path1= 0.;
  path2 = 0.;
  isPassed2 = false;
  isPassed1 = false;
  */
  
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
  //whenever a new event starts the energy accumulated in the target and the total path in the target should be reset to 0 
  //also the flag "isPassed" has to be reset
  fEdep = 0.;
  isPassed1 = false;
  isPassed2 = false;
  isPassed3 = false;
  //isPassed4 = false;
  isPassed5 = false;
  path = 0;

  /*
  fEdep2 = 0.;
  path1= 0.;
  path2 = 0.;
  isPassed2 = false;
  isPassed1 = false;
  */
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
  
   //printing the energy accumulated during the event in the target
  //G4cout << "Energy deposition in the target:" << fEdep << G4endl;

  /*
  //printing the energy accumulated during the event in the second scintillators
  G4cout << "Energy deposition in the second scintillator:" << fEdep2 << G4endl;
 */
  
  //storing the energy accumulated in a column, only if the muon is passed from the trg scintillators
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  if(isPassed1 == true && isPassed2 == true && isPassed3 == true && isPassed5 == true)
  {
    //G4cout << "totEdep: " << fEdep << G4endl;
    //G4cout << "totLenght: " << path << G4endl;
    man->FillNtupleDColumn(0,0,fEdep);
    man->FillNtupleDColumn(0,4, path);
    man->AddNtupleRow(0);
  }
  
  /*
  //filling the column with fEdep2 only if the positron is passed in the second scintillator
  if(isPassed2 == true)
  {
    man->FillNtupleDColumn(3,0,fEdep2);
    man->FillNtupleDColumn(3,1, path2);
    man->AddNtupleRow(3);
  }
  //it creates entries for each event -> looking at the root file we should able to see the distribution of the deposited energy
  */
  
}






