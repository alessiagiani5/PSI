#include "run.hh"

//if we write hear the command to generate the output file than it is created as soon as we run the programm
MyRunAction::MyRunAction()
{
  
  //a new output file is created for each run
  //to do it we have to use the class G4AnalysisManager
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("In the target","In the target");
  man->CreateNtupleDColumn("EdepTarget");
  man->CreateNtupleDColumn("Ein");
  man->CreateNtupleDColumn("Eout");
  man->CreateNtupleDColumn("EdepStep");
  man->CreateNtupleDColumn("TargetPath");
  //it's necessary to finish the Ntuple
  man->FinishNtuple(0);
}
  

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->OpenFile("simulation_output.root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  //writing on the file. it's important to write on it before close it!
  man->Write();
  //G4cout << "Number of final positrons:"<<numberOfEvents<<G4endl;
  //when we open a file we have also to close it
  man->CloseFile("simulation_output.root");
  
}
