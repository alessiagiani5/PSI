#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//including our detector
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
  G4Random::setTheEngine(new CLHEP::RanecuEngine());
  //std::vector<long int> evSeed{935670103,306800375};
  G4Random::setTheSeed(0);
  //CLHEP::HepRandom::getTheEngine()->restoreStatus ("./status");
  G4RunManager *runManager = new G4RunManager();
  
  //telling the run manager the geometry we want create
  runManager->SetUserInitialization(new MyDetectorConstruction());

  //telling the run manager our physics
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());

  //necessary for using the geometry created
  runManager->Initialize();

  G4UIExecutive *ui = new G4UIExecutive(argc, argv);

  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  
  //in order to let geant4 open the window 
  UImanager->ApplyCommand("/vis/open OGL");

  //UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");

  //UImanager->ApplyCommand("/vis/scene/add/scale 10 cm");
  //UImanager->ApplyCommand("/vis/scene/add/axes");

  //in order to let geant4 draw volumes
  UImanager->ApplyCommand("/vis/drawVolume");

  //refresh between an event and another
  UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");

  //in order to let geant4 draw trajectories
  UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");

  //UImanager->ApplyCommand("/vis/scene/add/scale 10 mm");
  UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 865 mm");
  //UImanager->ApplyCommand("/vis/scene/add/eventID");

  //in order to accumulate all the events of the same run 
  UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

  //in order to not display the world
  UImanager->ApplyCommand("/vis/geometry/set/visibility logicWorld 0 false");

  UImanager->ApplyCommand("/run/beamOn 10000");

  ui->SessionStart();
  
  return 0;
}
