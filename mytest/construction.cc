#include "construction.hh"

//dealing with the construction
MyDetectorConstruction::MyDetectorConstruction()
{
  //defining initial values of nCols and nRows
  nCols = 100;
  nRows = 100;

  //it's used to choose between different detectors that we created, but also the number of columns and rows
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

  //nCols is the number of photosensor in a column
  fMessenger->DeclareProperty("nCols",nCols, "Number of columns");
  
  //nRows is the number of photosensor in a column
  fMessenger->DeclareProperty("nRows",nRows, "Number of rows");

  //let us decide which kind of geometry will be loaded
  fMessenger->DeclareProperty("isCherenkov",isCherenkov, "Toggle Cherenkov setup");
  fMessenger->DeclareProperty("isScintillator",isScintillator, "Toggle Scintillator setup");

  //necessary to have materials
  DefineMaterial();

  //initializing x,y,zWorld
  xWorld =0.5*m;
  yWorld =0.5*m;
  zWorld =0.5*m;

  
  //initializing the two boolean variables
  isCherenkov = false;
  isScintillator = true;


}


MyDetectorConstruction::~MyDetectorConstruction()
{}

//this functions create materials
void MyDetectorConstruction::DefineMaterial()
{
  //getting parameters predefinied for each material (G4NistManager is a class)
  G4NistManager *nist =  G4NistManager::Instance();

  //defining carbon
  C = nist->FindOrBuildElement("C");
  //G4Material's first parameter is the name of the material, the second is the density and the third is the number of component
  SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
  //defining aerogel
  Aerogel = new G4Material("Aerogel",0.200*g/cm3,3);
  //searching for a predefinined material and define worldMat according for that
  worldMat = nist->FindOrBuildMaterial("G4_AIR");
  //defining H2O:
  H2O = new G4Material("H2O",1.000*g/cm3, 2);

  //adding detector volume: its an aerogel, composed by SiO2, C and H2O
  //we start defining all the three components of the aerogel and than we will put them together in the right %
  //defining the SiO2:
  //the 1 is because the Silicon in SiO2 has only 1 atoms, whereas the oxigen has 2 atoms
  SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
  SiO2->AddElement(nist->FindOrBuildElement("O"),2);

  H2O->AddElement(nist->FindOrBuildElement("H"),2);
  H2O->AddElement(nist->FindOrBuildElement("O"),1);

  Aerogel->AddMaterial(SiO2,62.5*perCent);
  Aerogel->AddMaterial(H2O,37.4*perCent);
  Aerogel->AddElement(C,0.1*perCent);

  //defining the information for the rifraction index (nb: actually rindex should vary with wavelenght, but we assume it to be constant for those values of lambda)
  //these are two values of photon energy, for which we calculate the relative values of rindex (0.2 and 0.9 are the wave lenghts of blue and red light)
  G4double energy[2] = {1.239841939*eV/0.2,1.239841939*eV/0.9};

  //rifraction index of aerogel for those values of photon  energy
  G4double rindexAerogel[2]= {1.1,1.1};

  //rifraction index of air for those values of energy
  G4double rindexWorld[2]= {1.0,1.0};

  //rindex of NaI for those values of photon energy
  G4double rindexNaI[2]= {1.78,1.78};

  //we want all photons to be reflected when hit the mirror surface, so the reflectivity should be 1.0 (it's the fraction of photons that will be reflected)
  G4double reflectivity[2] = {1.0,1.0};

  //we have to add the rindex to our material
  G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();

  //inserting the two values 2 for the energy and 2 for the rindex) in the proprieties
  mptAerogel->AddProperty("RINDEX",energy, rindexAerogel, 2);

  Aerogel->SetMaterialPropertiesTable(mptAerogel);

  //in order to let photons propagate in all the world and not only in the radiator we should define also the rindex of the worldvolume
  G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
  mptWorld->AddProperty("RINDEX",energy, rindexWorld, 2);

  

  //defining NaI
  Na = nist->FindOrBuildElement("Na");
  I = nist->FindOrBuildElement("I");
  NaI = new G4Material("NaI", 3.67*g/cm3, 2);
  NaI->AddElement(Na,1);
  NaI->AddElement(I,1);

  //actually we will have maybe more photons in the blue spetrum or in the red one so we should define the fraction of wavelenght, but for semplicity we assume that each wavelenght will appeare with the same intensity (the same number of red photons and blue ones)

  G4double fraction[2]= {1.0,1.0};

  //we have a mesure of the energy deposition, but we also  want to see how many photons are created: without rindex there is no scintillation light
  G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
  mptNaI->AddProperty("RINDEX", energy, rindexNaI,2);

  //telling Geant4 how many photons for each wavelenght (interval) will be created
  mptNaI->AddProperty("FASTCOMPONENT", energy, fraction, 2);

  //telling Geant4 how many photons per energy loss of the particle we create (for NaI we have 38 photons per keV)
  mptNaI->AddConstProperty("SCINTILLATIONYIELD", 38./keV);

  mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0);

  //when the particles loses energy in the scintillator, than the photons are emitted according to exponential function-> time constant gives the decay time of that scintillator (it is 250*ns for NaI)
  mptNaI->AddConstProperty("FASTTIMECONSTANT", 250*ns);

  //has something to do with the distribution of the number of photons: ww won't have a constant number of emitted photons, but a fluctuation around mean value (the sigma of this distribution should be write into brackets -> we use 1)
  mptNaI->AddConstProperty("YIELDRATIO",1.);

  NaI->SetMaterialPropertiesTable(mptNaI);

  //LO COMMENTO IN MODO DA NON AVERE PROPAGAZIONE FUORI DALLO SCINTILLATORE
  worldMat->SetMaterialPropertiesTable(mptWorld);

  //creating mirror surface arounf scintillators in order to trap photons into scintillators
  mirrorSurface = new G4OpticalSurface("mirrorSurface");

  //defining the type of reflective surface
  mirrorSurface->SetType(dielectric_metal);
  mirrorSurface->SetFinish(ground);
  mirrorSurface->SetModel(unified);

  G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();

  mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity,2);

  //adding material properties defined before to the mirror surface
  mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}


//this function constructs the radiator and the matrix of detectors
void MyDetectorConstruction::ConstructCherenkov()
{
  //defining the radiator (we decide to make it as a box, smaller than the solid volume): it's the material which let the production of cherenkov light to be possible

  //the solid volume 
  solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

  //the logic volume
  logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");

 //we want to use the radiator as scoring volume
  fScoringVolume = logicRadiator;


  //the physical volume: after the name ".." we write logicWorld, insted of 0, because this volume isn't a mother-volume, but it's contained in the volume defined before (logicWorld)
  physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.25*m), logicRadiator, "physRadiator",logicWorld, false, 0, true);

  //defining sensitive volume (matrix of hundreds of photosensors) necessary for detect the position .. of the photons. A volume is sensitive if we want the info coming from the interaction of particle with that volume
  
  //defining each detector
  solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols, 0.01*m);

  //creating logical volume of the detector: logical volume has to be accessible from outside the function, so we define the variable G4LogicalVolume* as a private variable of the class MyDetectorConstruction
  logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");


  //creating the physical instance of our detector -> creating a 100x100 matrix of photosensors (the j+i*100 is necessary in order to create for every value of i, 100 photosensors
  for (G4int i = 0; i < nRows; i++)
  {
    for (G4int j = 0; j < nCols; j++)
    {
      physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m + (i+0.5)*m/nRows, -0.5*m + (j+0.5)*m/nCols, (0.5-0.01)*m), logicDetector, "physDetector", logicWorld, false,j+i*nCols, true);  
     }
   
   }

}


//this function creates the scintillator and the photodetector attached to the scintillator
void MyDetectorConstruction::ConstructScintillator()
{
  // class G4Tubs: in brackets we have: name, inner radius, external radius, lenght, starting angle, ending angle
  
  solidScintillator = new G4Box("solidScintillator",5*cm, 5*cm,6*cm);

  logicScintillator = new G4LogicalVolume(solidScintillator, NaI, "logicalScintillator");

  //appling mirror surface to scintillator. in order to make sure that photons stay inside scintillators we write logicWorld -> this let the world be reflective, so that photons stay inside scintillators
  G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

  //defining photosensors
  solidDetector = new G4Box("solidDetector", 1.*cm, 5.*cm, 6*cm);

  logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

  //we want to use the scintillator  as scoring volume, the volume for which we calculate the deposition of energy
  fScoringVolume = logicScintillator;
  

  //defining an array of 16  scintillators
  for (G4int i=0; i< 6; i++)
    {

      for (G4int j=0; j < 16; j++)
	{
	  //rotazione di un angolo j*22.5 gradi (22.5 = 360/16) nella direzione data dal vettore (0,0,1)
	  G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0,0,1));

	  //traslazione degli scintillatori
	  G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm + 5.*cm, 0.*cm, -40.*cm + i*15*cm));


	  //translation of photosensors
	  G4Translate3D transXDet (G4ThreeVector(5./tan(22.5/2*deg)*cm + 6.*cm + 5.*cm, 0.*cm, -40.*cm + i*15*cm));

	  //la trasformazione che applico è data dall'applicazione, prima della traslazione e poi dalla rotazione
	  G4Transform3D transformScint = (rotZ)*(transXScint);

	  G4Transform3D transformDet = (rotZ)*(transXDet); 
 
	  //we can define the rotation and the traslation inside physScintillator or we can define them outside and then put them into the brackets of physscintillator 
	  //remember that the mother volume is always logicWorld
	  physScintillator = new G4PVPlacement(transformScint, logicScintillator, "physScintillator",logicWorld,false, 0, true);

	  physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector",logicWorld,false, 0, true);


	}

    }

  

}



//this function creates the physWorld
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

  //we will simulate our world, which is a box full of air, in which there will be a radiator made with aerogel and a matrix of sensitive detectors
  
  //every volume in Geant4 has to contain 3 paths:
  //3 paths: solid defines the size, logical includes the material, physical places the volume in a defined position


  //creating the solid volume - solidWorld (use the class G4Box to create a box)
  solidWorld = new G4Box("solidWorld",xWorld, yWorld, zWorld);
  //the last three parameters are half the dimensions (x,y,z) in m (so the width will be 1 m..)


  //inserting the material (worldMat) into the solid volume (solidWorld) ("logicWorld is the name of the logical volume obtained)
  logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");


  //creating physical volume

  //the first parameter is the rotation, but in this case we don't want any rotation, so we write 0. We also want the box to be in center of our system of coordinates, so we set G4ThreeVector to (0,0,0)."logicWorld" is the parameter which says that we are going to insert the logical volume defined before. The 0 after the name ".." tells us that the volume is a "mother-volume", so it isn't contained in an other volume. The false is necessary because we don't want to implement any boolean operation. The 0 after "false" says that we don't want another copy of the volume. The last parameter is set to "true" in order to check if there is some overlap with other volumes
  physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.), logicWorld, "physWorld",0, false, 0,true);  

  //if cherenkov setup is avaiable, we construct it thanks to the function constructchenkov
  if(isCherenkov)
    ConstructCherenkov();

//if scintillator  setup is avaiable, we construct it thanks to the function constructscintillator
  if(isScintillator)
    ConstructScintillator();

  //now we have our physical volume, called "physWorld"
  //the function will return the "mother-volume"
   
  return physWorld;
  
}

void MyDetectorConstruction:: ConstructSDandField()
{

  //definition of sensitive volume: we want the info coming from the interaction of the particles with this volume
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

  //telling our logic detector that this is our sensitive detector

  //if there isn't cherenkov setup avaiable  we dont' want to have sensitive detector
  //if(isCherenkov)

  //now we want our photosensors to be our sensitive detector, so if logicDetector is not a null pointer, we define it as sensitive detector 

  //logicdetector is the one of cherenkov set up if ischerenkov is true, whereas it's the one of scintillator setup if isScintillator is true, because we have imposed if(isCherenkov) ConstructCherenkov(), if(isScintillator) ConstructScintillator() in the construction of the world

  if(logicDetector != NULL)
    logicDetector->SetSensitiveDetector(sensDet);

  
}
