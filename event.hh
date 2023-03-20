#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

//in order to get access to our manager to store the information we want
#include "G4AnalysisManager.hh"
#include "run.hh"

class MyEventAction : public G4UserEventAction
{
public:
  MyEventAction(MyRunAction*);
  ~MyEventAction();

  //everything that has to be done at the beginning of an event should be write in this function 
  virtual void BeginOfEventAction(const G4Event*);

  //everything that has to be done at the beginning of an event should be write in this function
  virtual void EndOfEventAction(const G4Event*);
  
  //it's a public function because we have to transfer the information from the stepping function.
  // edep is the deposited energy of each step
  //we accumulate a certain number, equals to the number of steps done, of edep and than we obtain fedep
  void AddEdep(G4double edep) {fEdep += edep;}
  void AddStepLenght(G4double steplenght) {path += steplenght;}

  /*
  void AddEdep2(G4double edep) {fEdep2 += edep;}
  void AddStepLenght2(G4double steplenght) {path2 += steplenght;}
  void SetIsPassed1(){isPassed1 = true;}

  */
  void SetIsPassed1(){isPassed1 = true;}
  void SetIsPassed2(){isPassed2 = true;}
  void SetIsPassed3(){isPassed3 = true;}
  //void SetIsPassed4(){isPassed4 = true;}
  void SetIsPassed5(){isPassed5 = true;}
  
private:
  //in order to accumulate energy
  G4double fEdep, path; //fEdep2, path1, path2;
  bool isPassed1, isPassed2, isPassed3, isPassed5;
  //bool isPassed1 = false;
  
};

#endif
