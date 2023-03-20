#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh" //it includes the file G4AnalysisManager.hh

//defining the class
class MyRunAction : public G4UserRunAction
{
public:
  MyRunAction();
  ~MyRunAction();

  
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
  //static G4int passed;


  //setting the number of positrons that will reach the second scintillator for each run
 // inline static G4int numberOfEvents=0;
};


#endif
