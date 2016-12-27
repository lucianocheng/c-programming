#include <iostream>
using namespace std;

class IntCell {

public:
  explicit IntCell ( int initialValue = 0 ) { // explicit prevents implicit  
    storedValue = initialValue;               // type conversion ie
  }                                           // casting an int to an IntCell
  
  ~IntCell() {                                // Destructor
    cout << "I'm dying" << endl;
    // Does nothing since IntCell contains only and int data
    // member. If IntCell contained any class objects their 
    // destructors would be called.
    }
    
  IntCell (const IntCell & rhs )              // Copy Constructor
    : storedValue ( rhs.storedValue ) // copies rhs int to this int
    {
    // Additional member variables would be copied here
    }
    
  const IntCell & IntCell::operator=( const IntCell & rhs) { // Copy Assignment Operator
    if (this != &rhs )
      storedValue = rhs.storedValue;
    return *this;
  }

  int getValue() { 
    return storedValue; 
  }

  void setValue ( int val ) { 
    storedValue = val; 
  }


private:
  int storedValue;

};


int main ()
{
  IntCell x(5);
  if (x.getValue() == 5)
    cout << "INTCELL WORKS!!!!!" << endl;
  return 0;
}
