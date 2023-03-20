#include "generator.hh"
#include "TF1.h"
#include "TMath.h"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  //brackets contain the number of particles per event
  fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  //all the proprieties of the particle we want to use are stored in this table
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  
  G4String particleName ="mu-";
  //obtaining the definition of that particle from the table and inserting it in the variable "particle". we decide to use a generic particle, called geantino and then we can always replace it in a macrofile. if we don't replace, so if we use geantino, then we will take the radioactive dacay of cobalt. To do that we have to use an if clause in the function MyPrimaryGenerator
  G4ParticleDefinition *particle = particleTable->FindParticle("mu-"); 

  //defining the angular distribution 
  TF1 *fPhi = new TF1("fPhi", "1", 0., 2*TMath::Pi());
  TF1 *fTheta = new TF1("fTheta", "cos(x) * cos(x)", - TMath::Pi()/2, TMath::Pi()/2);
  

  //generating theta and phi
  G4double phi, theta;
  phi = fPhi->GetRandom();
  theta = fTheta->GetRandom();

  //generating initial direction of momentum
  G4double x_0, y_0, z_0;
  x_0 = TMath::Sin(theta) * TMath::Cos(phi);
  y_0 = TMath::Sin(theta) * TMath::Sin(phi);
  z_0 = TMath::Cos(theta);

  //defining the initial direction of momentum
  G4ThreeVector mom(x_0, y_0, z_0);


  //defining the distribution of the position: x and y are uniformly distributed in the scintillator 
  TF1 * fPos_X = new TF1("fPos_X", "1", -13.55, 13.55);
  TF1 * fPos_Y = new TF1("fPos_Y", "1", -24.95, 24.95);

  //generating initial x and y position (z is fixed to the biginning of the scintillator)
  G4double pos_x, pos_y;
  pos_x = fPos_X->GetRandom() * cm;
  pos_y = fPos_Y->GetRandom() * cm;

  //defining the position where the particle will be created 
  G4ThreeVector pos(pos_x, pos_y, -1.2*cm);

  //defining energy distribution of cosmic muons
  TF1 * fEn = new TF1("fEn", "1", 1., 1000.);
  
  //generating initial energy 
  G4double en;
  en = fEn->GetRandom() * MeV;

  //imposing the position and the direction defined before.
  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);


  //---------------------CONTROLLARE: È L'ENERGIA CINETICA???

  //Defining its momentum (Geant4 uses MeV)
  fParticleGun->SetParticleEnergy(en);
  //imposing what kind of particle we want to use
  fParticleGun->SetParticleDefinition(particle);

  //telling Geant4 to generate the primary vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
  
}
