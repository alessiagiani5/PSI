#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
  //remember: we want to create a Cherenkov detector
  //dealing with electromagnetism
  RegisterPhysics (new G4EmStandardPhysics());

  //in this case it's necessary to have Cherenkov light 
  RegisterPhysics (new G4OpticalPhysics());

  RegisterPhysics(new G4DecayPhysics());

  G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
  RegisterPhysics(stepLimitPhys);
  
  
}

MyPhysicsList:: ~MyPhysicsList()
{}
/*
MyUserPhysicsList::MyUserPhysicsList()
{
    ConstructParticle();
    //ConstructProcess();
}

MyUserPhysicsList::~MyUserPhysicsList()
{
}

void MyUserPhysicsList::ConstructParticle()
{
    G4MuonMinus::Definition();
    G4Electron::Definition();
    
}

void MyUserPhysicsList::ConstructEM()
{
  //G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  //G4String particleName = particle->GetParticleName();

  G4PhysicsListHelper *ph = G4PhysicsListHelper::GetPhysicsListHelper();
  auto particleIterator = GetParticleIterator();
  particleIterator->reset();
  while ((*particleIterator)())
  {
    G4ParticleDefinition *particleDefinition = particleIterator->value();

    if (particleDefinition == G4MuonMinus::Definition() ) 
    {
      ph->RegisterProcess(new G4MultipleScattering(), particleDefinition);
      ph->RegisterProcess(new G4MuIonisation(), particleDefinition);
      ph->RegisterProcess(new G4MuBremsstrahlung(), particleDefinition);
      ph->RegisterProcess(new G4MuPairProduction(), particleDefinition);
    } 
    else if ( particleDefinition == G4Electron::Definition() ) 
    {
      ph->RegisterProcess(new G4eMultipleScattering(), particleDefinition);
      ph->RegisterProcess(new G4eIonisation(), particleDefinition);
      ph->RegisterProcess(new G4eBremsstrahlung(), particleDefinition);
   
    }
  }

} 
*/