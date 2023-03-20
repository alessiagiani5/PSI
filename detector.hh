//in order to detect the photons we need to create a new class

#ifndef DETECTOR_HH
#define DETECTOR_HH


#include "G4VSensitiveDetector.hh" 
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh" //in order to include the class G4AnalysisManager
#include "run.hh"
class G4Step;


class MySensitiveDetector : public G4VSensitiveDetector
{

public:
  MySensitiveDetector(G4String);
  ~MySensitiveDetector();

//in order to detect something and process the hits
private:
  virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};



#endif