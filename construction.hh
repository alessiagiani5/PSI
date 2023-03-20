#ifndef CONSTRUCTION_HH 
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4UserLimits.hh"

#include "detector.hh"


//#include "detector.hh"

//definition of the class
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
  ~ MyDetectorConstruction();//deconstruct 

  //this function returns fScoringVolume, whichs is a G4LogicalVolume* variable, used in order to obtain the energy deposited only
   //in a particular volume and not in all detector
  //to set scintillator number 1 as scoring volume number 1
  G4LogicalVolume *GetScoringVolume1() const {return fScoringVolume1;}

  //to set scintillator number 2 as scoring volume number 2
  G4LogicalVolume *GetScoringVolume2() const {return fScoringVolume2;}

  //to set scintillator number 3 as scoring volume number 3
  G4LogicalVolume *GetScoringVolume3() const {return fScoringVolume3;}

  //to set scintillator number 4 (target) as scoring volume number 4
  G4LogicalVolume *GetScoringVolume4() const {return fScoringVolume4;}

  //to set scintillator number 5 as scoring volume number 5
  G4LogicalVolume *GetScoringVolume5() const {return fScoringVolume5;}
  
  //all the description of the detector has to be put in this function (it constructs all the detector)
  virtual  G4VPhysicalVolume *Construct();

private:
  
  G4double xWorld, yWorld, zWorld;

  //defining volumes
  G4Box *solidWorld, *solidScintillator1, *solidScintillator2, *solidScintillator3, *solidScintillator4, *solidScintillator5;
  G4LogicalVolume *logicWorld, *logicScintillator1, *logicScintillator2, *logicScintillator3, *logicScintillator4, *logicScintillator5;
  G4VPhysicalVolume *physWorld, *physScintillator1, *physScintillator2, *physScintillator3, *physScintillator4, *physScintillator5;
  G4Material *vacuum, *plastic;
  G4LogicalVolume *fScoringVolume1, *fScoringVolume2, *fScoringVolume3, *fScoringVolume4, *fScoringVolume5;

  
  
  //defining function that creates the scintillator
  void ConstructScintillator();

  //function that defines our sensitive detector
  virtual void ConstructSDandField();

  //defining function to define materials
  void DefineMaterial();

};

#endif
