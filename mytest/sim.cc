#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//including our detector
#include "construction.hh"

//to make sure the run manager uses the right physics
#include "physics.hh"

#include "action.hh"

int main(int argc, char** argv)
{
  G4RunManager *runManager = new G4RunManager();

  //telling the run manager the geometry we want create
  runManager->SetUserInitialization(new MyDetectorConstruction());

  //telling the run manager the physics of the process
  runManager->SetUserInitialization(new MyPhysicsList());

  runManager->SetUserInitialization(new MyActionInitialization());

  //necessary for using the geometry created
  runManager->Initialize();

  G4UIExecutive *ui = 0;

  if(argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }


  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  //if ui exist then we create our graphic output
  if(ui)
  {
    
    //telling geant4 that it has to load the macrofile vis.cc and execute all the commands
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
  } 

  else
  {
    G4String command = "/command/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  
   }
  

  return 0;
}
