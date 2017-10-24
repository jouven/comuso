#ifndef COMUSO_MACROS_H_
#define COMUSO_MACROS_H_

//use MOVE mechanics, this fails when trying to cast a base obj to a derived obj, even it they have the same properties
//and differ in functions
#define DERIVECAST(OBJ, TYPE) static_cast<TYPE&>(OBJ)
#define MAKETRUEPAIR(OBJ) std::make_pair(OBJ, true)

#endif /* COMUSO_MACROS_H_ */
