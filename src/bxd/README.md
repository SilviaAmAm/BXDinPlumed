### How to use collective variables in BXD

In the function “registerKeywords” add:

```c++
ActionWithArguments::registerKeywords(keys);
keys.use("ARG");
```
(I think that one has to use the registerKeywords function to register key from one of the classes from which you inherit that implements it. For example the umbrella sampling has Bias::registerKeywords(keys). )

This enables to use the keyword ‘ARG’ in the input file and thus to specify the label of a collective variable of interest. 
Then, in the “calculate” function one can use the function ‘getArgument’ which returns the value of the collective variable.

In order to be able to do this you need to include the ActionRegister.h file. 




### How to obtain the number of atoms in the system from the BXD file:

One needs to include the header core/PlumedMain.h.
Then, one can use the main plumed object and do this:

```c++
int natoms;
natoms = plumed.getAtoms().getNatoms();
```
One is able to call the main PlumedMain object 'plumed' because it is a public member in the class Action.

### How to obtain the positions in the BXD file

Then if one wanted to get the positions of all the atoms in the system, first one needs to create an array with the indices of all the atoms.

```c++
std::vector<AtomNumber> index(natoms);
for(int i = 0; i < natoms; i++)
{
    index[i].setIndex(i);
}
requestAtoms(index);
```

The function 'requestAtoms' doesn't return anything, I think it just makes the atoms requested available. The coordinates can then be obtained with the function 'getPosition' which returns a 'Vector', an alias for size 3 vectors in plumed. Here it is shown how to obtain the coordinates for atom 1.

```c++
Vector aPosition;   
aPosition = getPosition(0);
```
### How to obtain the step number

One can obtain the number of time steps performed as follows:

```c++
long int step;
step = plumed.getStep();
```

### How to obtain the velocities from the BXD file




### How to change the positions from the BXD file

It seems that the command to set the new positions is found in the PlumedMain.cpp file. PlumedMain is the main plumed object. It defines the interface with the MD code. It is wrapped around by PLMD::Plumed. 

The commands that can be passed to the main plumed object are stored in /src/core/PlumedMainMap.inc.

However, it looks that the positions are not being modified when the setPosition command is called... :(

The pointers to the MD objects are found in the class MDAtomsBase, located in the core/MDAtoms.h file. However, this is an abstract class and it is implemented in the MDAtomsTyped class (in core/MDAtoms.cpp).
An MDAtomsBase object is created inside the class Atoms, so one can access these pointers.

### How to change the velocities from the BXD file

