#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4VUserPhysicsList.hh"
#include "G4EmStandardPhysics.hh"

#include "G4DecayPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4StepLimiterPhysics.hh"

/*
#include "G4Electron.hh"
#include "G4MuonMinus.hh"


#include "G4MultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
*/

//using the class MyPhisicsList
class MyPhysicsList : public G4VModularPhysicsList
{
public:
  MyPhysicsList();//construct
  ~MyPhysicsList(); //deconstruct


 
};
/*
class MyUserPhysicsList : public G4VUserPhysicsList
{
public:
    MyUserPhysicsList();
    ~MyUserPhysicsList();

    virtual void ConstructParticle();
    virtual void ConstructEM();
    //virtual void ConstructProcess();

    //void ContructGeneral();
};
*/
#endif
