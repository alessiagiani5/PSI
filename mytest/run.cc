#include "run.hh"

//if we write hear the command to generate the output file than it is created as soon as we run the programm
MyRunAction::MyRunAction()
{
  //a new output file is created for each run: to do it we have to use the class G4AnalysisManager
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  //creating Ntuples (or Tree) inside the output file in order to store our information

  //storing the info about the exact postion of photons when the hit photosensors or theri momentum. they are all variables that are not known when we do our experiment
  man->CreateNtuple("Photons","Photons");

  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  //wavelenght of each photon that hits our detector
  man->CreateNtupleDColumn("fWlen");

  man->FinishNtuple(0);

  //creating another Ntuple
  man->CreateNtuple("Hits","Hits");

  //creating columns (I stands for integer, D for double) with event number (which hits are releted to which event) and the coordinates of our detector
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");

  //1 is because this the Ntuple number 1 we create. if we create another Ntupla then we will set FinishNtuple(2) and so on
  man->FinishNtuple(1);

  //creating another Ntuple in order to store the deposited energy
  man->CreateNtuple("Scoring","Scoring");
  man->CreateNtupleDColumn("fEdep");

  //it's necessary to finish the Ntuple
  man->FinishNtuple(2);
}


MyRunAction::~MyRunAction()
{}


void MyRunAction::BeginOfRunAction(const G4Run* run)
{
  //inserting event number in to output file name
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  //getting the ID of the run
  G4int runID = run->GetRunID();

  //converting it into a string
  std::stringstream strRunID;
  strRunID << runID;

  man->OpenFile("output"+strRunID.str()+".root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  //writing on the file. it's important to write on it before close it!
  man->Write();

  //when we open a file we have also to close it
  man->CloseFile("output.root");


}
