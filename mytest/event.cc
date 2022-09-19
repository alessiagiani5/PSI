#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
  //initializing the value of the deposeted energy for an event
  fEdep = 0.;

}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
  //whenever a new event starts the energy accumulated should be reset to 0
  fEdep = 0.;

}

void MyEventAction::EndOfEventAction(const G4Event*)
{
  //printing the energy accumulated during the event
  G4cout << "Energy deposition:" << fEdep << G4endl;

  //storing the energy accumulated into a root file
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  //filling the 0 column of the Ntuple number 2  with fEdep
  man->FillNtupleDColumn(2,0,fEdep);

  //it creates entries for each event -> looking at the root file we should able to see the distribution of the deposited energy
  man->AddNtupleRow(2);

}
