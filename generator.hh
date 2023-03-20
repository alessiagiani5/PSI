#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"


class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  MyPrimaryGenerator();//constructor
  ~MyPrimaryGenerator(); 

  //runs the particle gun, compute the step..
  virtual void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun *fParticleGun;

};


#endif