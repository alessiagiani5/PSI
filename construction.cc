#include "construction.hh"

//dealing with the construction
MyDetectorConstruction::MyDetectorConstruction()
{
  //necessary to have materials
  DefineMaterial();

  //initializing x,y,zWorld (they are half width, half lenght.. of the box we want to create)
  xWorld =10.*m;
  yWorld =10.*m;
  zWorld =10. *m;
}


MyDetectorConstruction::~MyDetectorConstruction()
{}

//this functions creates materials
void MyDetectorConstruction::DefineMaterial()
{
  //getting parameters predefinied for each material (G4NistManager is a class)
  G4NistManager *nist =  G4NistManager::Instance();

  //defining vacuum
  G4double atomicNumber =1.;
  G4double massOfMole = 1.008*g/mole;
  G4double density = 1.e-25*g/cm3;
  G4double temperature = 2.73*kelvin;
  G4double pressure = 3.e-18*pascal;

  //defining the vacuum, which will be used to fill the world
  vacuum = new G4Material("interGalactic", atomicNumber, massOfMole, density, kStateGas, temperature, pressure);
  
  //searching for a predefinined material and define plastic according to that
  plastic = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  //defining the information for the rifraction index (nb: actually rindex should vary with wavelenght, but we assume it to be constant for those values of lambda)
  //these are two values of photon energy, for which we calculate the relative values of rindex (0.2 and 0.9 are the wave lenghts of blue and red light)
  G4double energy[2] = {1.239841939*eV/0.2,1.239841939*eV/0.9};

  //rifraction index of vacuum for those values of energy
  G4double rindexWorld[2]= {1.0,1.0};

  //rindex of polystyrene
  G4double rindexPlastic[2]= {1.58,1.58};

  G4MaterialPropertiesTable *mptPlastic = new G4MaterialPropertiesTable();
  mptPlastic->AddProperty("RINDEX",energy, rindexPlastic, 2);

  //in order to let photons propagate in all the world and not only in the detector we should define also the rindex of the worldvolume
  G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
  mptWorld->AddProperty("RINDEX",energy, rindexWorld, 2);

}

void MyDetectorConstruction::ConstructScintillator()
{
  //creating scintillator number 1 (PMT7)
  solidScintillator1 = new G4Box("solidScintillator1", 13.55*cm, 24.95*cm, 1.2*cm); 
  logicScintillator1= new G4LogicalVolume(solidScintillator1, plastic, "logicScintillator1");
  physScintillator1 = new G4PVPlacement(0,G4ThreeVector(0., 0., 0.), logicScintillator1, "physScintillator1", logicWorld, false, 0, true);

  //defining scintillator1 as scoring volume number 1
  fScoringVolume1 = logicScintillator1;

  //constructing scintillator number 2 (PMT4)
  solidScintillator2 = new G4Box("solidScintillator2", 13.55*cm, 24.95*cm, 1.2*cm); 
  logicScintillator2= new G4LogicalVolume(solidScintillator2, plastic, "logicScintillator2");
  physScintillator2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,28.5*cm), logicScintillator2, "physScintillator2", logicWorld, false, 0, true);

  //defining scintillator2 as scoring volume number 2
  fScoringVolume2 = logicScintillator2;

  //constructing scintillator number 3 (PMT2)
  solidScintillator3 = new G4Box("solidScintillator3", 13.55*cm, 24.95*cm, 1.2*cm); 
  logicScintillator3= new G4LogicalVolume(solidScintillator3, plastic, "logicScintillator3");
  physScintillator3 = new G4PVPlacement(0,G4ThreeVector(0.,0.,66.5*cm), logicScintillator3, "physScintillator3", logicWorld, false, 0, true);

  //defining scintillator3 as scoring volume number 3
  fScoringVolume3 = logicScintillator3;

  //constructing scintillator number 4 (target)
  solidScintillator4 = new G4Box("solidScintillator4", 15.25*cm, 14.65*cm, 15.4*cm); 
  logicScintillator4= new G4LogicalVolume(solidScintillator4, plastic, "logicScintillator4");
  physScintillator4 = new G4PVPlacement(0,G4ThreeVector(0.,0.,86.5*cm), logicScintillator4, "physScintillator4", logicWorld, false, 0, true);

  //defining scintillator4 as scoring volume number 4
  fScoringVolume4 = logicScintillator4;

  //constructing scintillator number 5 (PMT1)
  solidScintillator5 = new G4Box("solidScintillator5", 13.55*cm, 24.95*cm, 1.2*cm); 
  logicScintillator5= new G4LogicalVolume(solidScintillator5, plastic, "logicScintillator5");
  physScintillator5 = new G4PVPlacement(0,G4ThreeVector(0.,0.,118.5*cm), logicScintillator5, "physScintillator5", logicWorld, false, 0, true);

  //defining scintillator5 as scoring volume number 5
  fScoringVolume5 = logicScintillator5;



}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  //creating the solid volume 
  solidWorld = new G4Box("solidWorld",xWorld, yWorld, zWorld);
  
  //inserting the material (vacuum) into the solid volume
  logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");

  //creating physical volume:
  //the first parameter is the rotation, but in this case we don't want any rotation, so we write 0. 
  //We also want the box to be in center of our system of coordinates, so we set G4ThreeVector to (0,0,0).
  //"logicWorld" is the parameter which says that we are going to insert the logical volume defined before. 
  //The 0 after the name ".." tells us that the volume is a "mother-volume", so it isn't contained in an other volume.
  //The false is necessary because we don't want to implement any boolean operation. 
  //The 0 after "false" says that we don't want another copy of the volume. 
  //The last parameter is set to "true" in order to check if there is some overlap with other volumes
  physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.), logicWorld, "physWorld",0, false, 0,true);  

  ConstructScintillator();

  return physWorld;
  
}

//definition of sensitive volume: we want the info coming from the interaction of the particles with this volume
void MyDetectorConstruction:: ConstructSDandField()
{
  MySensitiveDetector *sensDet4 = new MySensitiveDetector("Scintillator4");
  MySensitiveDetector *sensDet5 = new MySensitiveDetector("Scintillator5");

  //telling our logic detector that this is our sensitive detector
  // we want our scintillators to be our sensitive detector, 
  //so if logicScintillator1,2 are not a null pointer, we define them as sensitive detector 
  if(logicScintillator4 != NULL)
    logicScintillator4->SetSensitiveDetector(sensDet4);

  
  if(logicScintillator5 != NULL)
    logicScintillator5->SetSensitiveDetector(sensDet5);
  
  
}


