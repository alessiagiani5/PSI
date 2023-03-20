#include "detector.hh"


MySensitiveDetector::MySensitiveDetector(G4String name): G4VSensitiveDetector(name)
{}


MySensitiveDetector::~MySensitiveDetector()
{}

//everytime a photon hits our sensitive detector the class G4Track is activated and the info obtained are stored in our tuples

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  //in order to get the information about the photon when it enters our sensitive detector
  //G4Track *track =aStep->GetTrack();
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
  G4Track *track = aStep->GetTrack();
  G4double first_time =aStep->IsFirstStepInVolume();
  G4double last_time =aStep->IsLastStepInVolume();
  G4String nameVol = preStepPoint->GetSensitiveDetector()->GetName();
  G4ThreeVector pos = preStepPoint->GetPosition();
  G4double kinEnergy = postStepPoint->GetKineticEnergy();
  G4double kineticEnergy = preStepPoint->GetKineticEnergy(); 
  //G4double totEnergy = postStepPoint->GetTotalEnergy();
  G4double totEnergy = preStepPoint->GetTotalEnergy();

  //G4String nameVol = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
 
  if((nameVol=="Scintillator4") && (track->GetTrackID() == 1) && (first_time==true))
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    //G4cout <<"totEn_in: " << totEnergy<<G4endl;
    //G4cout <<"kinEn_in: " << kineticEnergy<<G4endl;
    man->FillNtupleDColumn(0,1,kineticEnergy);   
    //man->AddNtupleRow(0); 
  }

  if((nameVol=="Scintillator4") && (track->GetTrackID() == 1) && (last_time==true))
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    //G4cout << "kinEn_out: " <<  kinEnergy <<G4endl;
    man->FillNtupleDColumn(0,2,kinEnergy);   
    //man->AddNtupleRow(0); 
  }


/*

  if((nameVol=="Scintillator1") && (track->GetTrackID() == 1) && (first_time==true))
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0,0,pos[0]);
    man->FillNtupleDColumn(0,1,pos[1]);  
    man->FillNtupleDColumn(0,2,pos[2]); 
    //G4cout << preStepPoint->GetTotalEnergy()<<G4endl;
    man->FillNtupleDColumn(0,3,kineticEnergy);   
    man->AddNtupleRow(0); 
  }

  //info about position and kinetic energy of positrons when they stop (K=0) in the first scintillator
  if((nameVol=="Scintillator1") && (track->GetTrackID() == 1) && (track->GetTrackStatus() == 2) )
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    man->FillNtupleDColumn(1,0,aStep->GetPostStepPoint()->GetPosition()[0]);
    man->FillNtupleDColumn(1,1,aStep->GetPostStepPoint()->GetPosition()[1]);  
    man->FillNtupleDColumn(1,2,aStep->GetPostStepPoint()->GetPosition()[2]); 
    //G4cout << preStepPoint->GetTotalEnergy()<<G4endl;
    man->FillNtupleDColumn(1,3,kinEnergy);   
    man->AddNtupleRow(1); 
  }


  //info about position and kinetic energy of positrons when they stop (K=0) in the first scintillator
  if((nameVol=="Scintillator1") && (track->GetTrackID() == 1) && (last_time == true) )
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    man->FillNtupleDColumn(3,0,pos[0]);
    man->FillNtupleDColumn(3,1,pos[1]);  
    man->FillNtupleDColumn(3,2,pos[2]); 
    //G4cout << preStepPoint->GetTotalEnergy()<<G4endl;
    man->FillNtupleDColumn(3,3,kinEnergy);   
    man->AddNtupleRow(3); 
  }
  
  
  //filling the column of the Ntuple with the z coordinate inside the scintillator
  if((nameVol=="Scintillator1") && (track->GetTrackID() == 1))
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    man->FillNtupleDColumn(2,0,pos[2]); 
    //G4cout << "z: " << pos[2] << G4endl;   
    man->AddNtupleRow(2); 
  }

  if((nameVol=="Scintillator2") && (track->GetTrackID() == 1) && (first_time==true))
  {
    G4AnalysisManager *man =  G4AnalysisManager::Instance();
    man->FillNtupleDColumn(4,0,preStepPoint->GetPosition()[0]);
    man->FillNtupleDColumn(4,1,preStepPoint->GetPosition()[1]);  
    man->FillNtupleDColumn(4,2,preStepPoint->GetPosition()[2]); 
    man->FillNtupleDColumn(4,3,kineticEnergy);   
    man->AddNtupleRow(4); 
    //G4cout<<"A particle!" << G4endl;
    MyRunAction::numberOfEvents +=1;
    //G4cout << "Number of final positrons:"<<MyRunAction::numberOfEvents<<G4endl;
    //G4cout << MyRunAction::numberOfEvents << G4endl;
    //as soon as the entered the second detector we kill them
    //track->SetTrackStatus(fStopAndKill);
  }
  */
  return true;

}  

