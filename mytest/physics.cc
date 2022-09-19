#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
  //remember: we want to create a Cherenkov detector
  //dealing with electromagnetism
  RegisterPhysics (new G4EmStandardPhysics());

  //in this case it's necessary to have Cherenkov light 
  RegisterPhysics (new G4OpticalPhysics());
  //for any particle decay
  RegisterPhysics (new G4DecayPhysics());
  //for radioactive decay
  RegisterPhysics (new G4RadioactiveDecayPhysics());
}

MyPhysicsList:: ~MyPhysicsList()
{}
