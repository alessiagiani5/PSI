#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
  MyActionInitialization();//constructor
  ~MyActionInitialization(); 

  //runs the particle gun, compute the step..
  virtual void Build() const;

};


#endif
