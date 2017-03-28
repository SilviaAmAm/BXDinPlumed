#include "/Users/walfits/Repositories/plumed2/src/core/ActionAtomistic.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionWithArguments.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionPilot.h"
#include "/Users/walfits/Repositories/plumed2/src/core/ActionRegister.h"
#include "/Users/walfits/Repositories/plumed2/src/core/PlumedMain.h"
#include "/Users/walfits/Repositories/plumed2/src/bias/Bias.h"

#include "/Users/walfits/Repositories/plumed2/src/tools/AtomNumber.h"


#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>

namespace PLMD{
namespace bias{
    
    class BXDTEST :
      public Bias,
      public ActionAtomistic
//    public ActionPilot
    {
    private:
              bool lockRequestArguments;
              bool lockRequestAtoms;
              virtual void lockRequests();
              virtual void unlockRequests();
        virtual void calculateNumericalDerivatives( ActionWithValue* a=NULL ){};
    
        
        
    public:
        explicit BXDTEST(const ActionOptions&);
        static void registerKeywords(Keywords& keys);
        virtual void calculate();  // pure virutal function that appears in Action.h and has to be defined in the most derived class
        virtual void apply(){};    // also a pure virtual function
        
    };
    
    /* This function registers the main keyword for the new BXD class */
    
    PLUMED_REGISTER_ACTION(BXDTEST,"BXDTEST")
    
    /* This function is used to register any keywords that are needed for BXD to work */
    
    void BXDTEST::registerKeywords(Keywords& keys)
    {
//        Action::registerKeywords(keys);
//        ActionWithArguments::registerKeywords(keys);
//        ActionPilot::registerKeywords(keys);
//        ActionAtomistic::registerKeywords(keys);
        Bias::registerKeywords(keys);
        ActionAtomistic::registerKeywords(keys);
    }
    
    
    /* This reads the values of the keywords that are specified in the input file (it is the constructor) */
    
    BXDTEST::BXDTEST(const ActionOptions& ao):
    Action(ao),
    Bias(ao),
    ActionAtomistic(ao)
    {
        checkRead();
        std::cout << "HELLO from constructor \n";
    }
    
    
    /* This is the function that calculates the values of the variables that will be changed by BXD */
    
    void BXDTEST::calculate()
    {
        std::cout << "HELLO from calculate \n";
    }
    
    void BXDTEST::lockRequests()
    {
        lockRequestArguments=true;
        lockRequestAtoms=true;
    }
    
    void BXDTEST::unlockRequests()
    {
        lockRequestArguments=false;
        lockRequestAtoms=false;
    }

    
    
    // Brackets from the namespaces!
}
}
