#include "action.hh"

MyActionInitialization:: MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization:: Build() const
{
  MyPrimaryGenerator *generator = new MyPrimaryGenerator();
  SetUserAction(generator);

  //we use our personal run action and not geant4 default run action. geant4 knows our run action thanks to the class G4RunAction
  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);

  //now Geant4 knows that it has to take our user defined class into account
  MyEventAction *eventAction = new MyEventAction(runAction);
  SetUserAction(eventAction);

  MySteppingAction *steppingAction = new MySteppingAction(eventAction);
  SetUserAction(steppingAction);

}
