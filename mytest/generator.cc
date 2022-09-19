#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{

  //brackets contain the number of particles per event
  fParticleGun = new G4ParticleGun(1);

  //defining what kind of particle we want create

  //all the proprieties of the particle we want to use are stored in this table
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  
  //obtaining the definition of that particle from the table and inserting it in the variable "particle". we decide to use a generic particle, called geantino and then we can always replace it in a macrofile. if we don't replace, so if we use geantino, then we will take the radioactive dacay of cobalt. To do that we have to use an if clause in the function MyPrimaryGenerator
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino"); 

  //defining where the particle will be created and the direction of its momentum
  G4ThreeVector pos(0.,0.,0.);
  G4ThreeVector mom(0.,0.,1.);

  //imposing the position and the direction defined before.Defining its momentum (Geant4 uses MeV) and imposing what kind of particle we want to use
  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(0.*GeV);
  fParticleGun->SetParticleDefinition(particle);

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;

}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  //getting the definition of particle, that we set in our construct
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

   //if we don't replace geantino in a macro with other particle, we take into account the radioactive decay of cobalt. we define in the if clause how our radioactive decay looks like

  if(particle == G4Geantino::Geantino())
  {
    G4int Z = 27;
    G4int A = 60;//now we use cobalt 60
    
    G4double charge = 0.*eplus;//we use a neutral athom (eplus is the elementary charge
    G4double energy = 0.*keV;

    //getting physical info about the ion which has Z=27, A=60.. from the iontable
    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);

    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);

  }   
  //telling Geant4 to generate the primary vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
  
}
