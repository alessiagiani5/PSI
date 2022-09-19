#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

//in order to get access to our manager to store the information we want
#include "g4root.hh"
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

  //it's a public function because we have to transfer the information from the stepping function (?)
  void AddEdep(G4double edep) {fEdep += edep;}

private:
  //in order to accumulate energy
  G4double fEdep;
  
};

#endif
