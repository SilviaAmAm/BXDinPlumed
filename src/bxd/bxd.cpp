#include "/Users/walfits/Repositories/plumed2/src/core/ActionAtomistic.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionWithArguments.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionPilot.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionRegister.h"
#include "/Users/walfits/Repositories/plumed2/src/core/PlumedMain.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionWithValue.h"

#include "/Users/walfits/Repositories/plumed2/src/bias/Bias.h"

#include "/Users/walfits/Repositories/plumed2/src/tools/AtomNumber.h"


#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <stdlib.h>



namespace PLMD{
namespace bias{

class BXD :
    public Bias,
    public ActionAtomistic
{
    private:
      double boxSeparation;
      int numBoxes;
      std::vector<double> boxes;
      std::vector<Vector> pos;

      // Resolving the diamond inheritance from ActionAtomistic and ActionWithArguments
      bool lockRequestArguments;
      bool lockRequestAtoms;
      virtual void lockRequests();
      virtual void unlockRequests();
      virtual void calculateNumericalDerivatives( ActionWithValue* a=NULL ){};
    
    
    public:
      explicit BXD(const ActionOptions&);
      static void registerKeywords(Keywords& keys);
      virtual void calculate();  // pure virutal function that appears in Action.h and has to be defined in the most derived class
      virtual void apply();    // also a pure virtual function
 
};
    
/* This function registers the main keyword for the new BXD class */
    
PLUMED_REGISTER_ACTION(BXD,"BXD")
    
/* This function is used to register any keywords that are needed for BXD to work */
    
void BXD::registerKeywords(Keywords& keys)
{
    Bias::registerKeywords(keys);
    ActionAtomistic::registerKeywords(keys);
    keys.use("ARG");                // This enables to use collective variables
    keys.add("compulsory","BOXSEP","10.0","Defines the separation between the boxes");
    keys.add("compulsory","NUMBOXES","10","Defines the number of boxes to use");
//    keys.addOutputComponent("bxdbias","default","the instantaneous value of the bias potential");
}

    
/* This reads the values of the keywords that are specified in the input file (it is the constructor) */
    
BXD::BXD(const ActionOptions& ao):
    Action(ao),
    Bias(ao),
    ActionAtomistic(ao)
    //isFirstStep(true)
{
    parse("BOXSEP", boxSeparation);
    parse("NUMBOXES", numBoxes);
    boxes.resize(numBoxes);
    checkRead();
    
//    addComponentWithDerivatives("bxdbias");
//    componentIsNotPeriodic("bxdbias");
//    valueBxd=getPntrToComponent("bxdbias");
}

    
/* This is the function that calculates the values of the variables that will be changed by BXD */
    
void BXD::calculate()
{
    int fint;
    double f;
    fint = rand() % 100 - 50;
    f = (double)fint;
    setOutputForce(0,f);
    std::cout << f << "\n";
    
//    //This puts the value of the first collective variable specified in ARG in the variable colVar
//    double colVar;
//    colVar = getArgument(0);
//    std::cout << colVar << "\n";
//    std::cout << "test \n";
//
//    // This obtains the number of atoms in the system
//    unsigned natoms;
//    natoms = getTotAtoms();
//
//    // This creates a list of the indexes of the atoms of interests. In BXD that means all the atoms.
//    std::vector<AtomNumber> index(natoms);
//    
//    for(int i = 0; i < natoms; i++)
//    {
//        index[i].setIndex(i);
//    }
//    requestAtoms(index);
//
    
}
    
    
    
    
    
    
    
    
/* This is the function that applies the changes calculated in the function 'calculate'. Both 'apply' and 'calculate' are virtual functions that are first introduced in Action.h and then have to be defined in the derived classes. */
    
void BXD::apply()
{
    
}
    
    
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
    
    
/* Resolving the diamond inheritance problem. The virtual functions 'lockRequest' and 'unlockRequest' appear in the base class Action and in the two child classes ActionWithArguments and ActionAtomistic. BXD is the only class so far in PLUMED that inherits from both ActionWithArguments and ActionAtomistic, so a final overrider has to be present. For now, I just joined the two functions that were in ActionWithArguments and ActionAtomistic into one. */
    
void BXD::lockRequests()
{
    lockRequestArguments=true;
    lockRequestAtoms=true;
}

void BXD::unlockRequests()
{
    lockRequestArguments=false;
    lockRequestAtoms=false;
}
    
/* This is again a problem of diamond inheritance.  */
    
//void BXD::calculateNumericalDerivatives( ActionWithValue* a )
//{
//    
//}
//    
    
// Brackets from the namespaces!
}
}
