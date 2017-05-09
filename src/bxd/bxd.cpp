#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/ActionAtomistic.h"
#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/ActionWithArguments.h"
#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/ActionPilot.h"
#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/ActionRegister.h"
#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/PlumedMain.h"
#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/ActionWithValue.h"
#include "/Users/walfits/OpenMM-from-src/Source/plumed/src/core/Atoms.h"

#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <stdlib.h>



namespace PLMD{

class BXD :
    public ActionAtomistic,
    public ActionPilot,
    public ActionWithArguments
{
    private:
      double boxSeparation;
      int numBoxes;
      int natoms;

      // Resolving the diamond inheritance from ActionAtomistic and ActionWithArguments
      virtual void lockRequests();
      virtual void unlockRequests();
      virtual void calculateNumericalDerivatives( ActionWithValue* a=NULL ){};
    
    
    public:
      explicit BXD(const ActionOptions&);
      static void registerKeywords(Keywords& keys);
      virtual void calculate();  // pure virutal function that appears in Action.h and has to be defined in the most derived class
      virtual void apply(){};    // also a pure virtual function
 
};
    
/* This function registers the main keyword for the new BXD class */
    
PLUMED_REGISTER_ACTION(BXD,"BXD")
    
/* This function is used to register any keywords that are needed for BXD to work */
    
void BXD::registerKeywords(Keywords& keys)
{
    Action::registerKeywords( keys );
    ActionAtomistic::registerKeywords(keys);
    ActionPilot::registerKeywords(keys);
    ActionWithArguments::registerKeywords(keys);
    keys.add("hidden","STRIDE","The stride for ActionPilot");
    keys.use("ARG");                // This enables to use collective variables
    keys.add("compulsory","BOXSEP","10.0","Defines the separation between the boxes");
    keys.add("compulsory","NUMBOXES","10","Defines the number of boxes to use");
}

    
/* This reads the values of the keywords that are specified in the input file (it is the constructor) */
    
BXD::BXD(const ActionOptions& ao):
    Action(ao),
    ActionAtomistic(ao),
    ActionPilot(ao),
    ActionWithArguments(ao)
{
    parse("BOXSEP", boxSeparation);
    parse("NUMBOXES", numBoxes);
    checkRead();

    // This requests all the atoms in the system, so that their position and velocity are available
    natoms = getTotAtoms();
    std::vector<AtomNumber> index(natoms);
    for(int i = 0; i < natoms; i++)
    {
        index[i].setIndex(i);
    }

    // The dependencies have to be copied because in requestAtoms() all the dependencies are cleared. 
    Dependencies copy(getDependencies());
    requestAtoms(index);

    for (auto action : copy)
    //for (std::vector<int>::iterator it = copy.begin(); it != copy.end(); ++it)
    {
        addDependency(action);
    }
    // This is to activate the arguments (collective variable)


}

    
/* This is the function that calculates the values of the variables that will be changed by BXD */
    
void BXD::calculate()
{
    double colvar;

    colvar = getArgument(0);
    std::vector<Vector> vel = getVelocities();

  
    
    // if(isFirstStep)
    // {
    //     isFirstStep = false;
    // }
    // else
    // {
    //     //
    // }
}
    
/* This is the function that applies the changes calculated in the function 'calculate'. Both 'apply' and 'calculate' are virtual functions that are first introduced in Action.h and then have to be defined in the derived classes. */
    
// void BXD::apply()
// {
    
// }
    
    
/* This function uses the first value of the collective variable to set an array of barriers that define the boxes. */
    
//void BXD::setBoxes(const double firstColVar)
//{
//    boxes[0] = firstColVar - 0.5 * boxSeparation;
//    
//    for(int i = 1; i < numBoxes; i++)
//    {
//        boxes[i] = i*boxSeparation;
//    }
//}
    
    
/* Resolving the diamond inheritance problem. The virtual functions 'lockRequest' and 'unlockRequest' appear in the base class Action 
and in the two child classes ActionWithArguments and ActionAtomistic. BXD is the only class so far in PLUMED that inherits 
from both ActionWithArguments and ActionAtomistic, so a final overrider has to be present. 
For now, I just joined the two functions that were in ActionWithArguments and ActionAtomistic into one. */
    
void BXD::lockRequests()
{
    ActionWithArguments::lockRequests();
}

void BXD::unlockRequests()
{
    ActionWithArguments::unlockRequests();
}


    
// Brackets from the namespaces!
}
