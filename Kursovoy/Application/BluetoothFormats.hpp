#pragma once
//#include "thread.hpp" //For definition of class Thread
//#include <array> //For std::array
//#include "susudefs.hpp" // for SusuString

//#include <iostream>
//#include <cstring> //For strlen


class BluetoothFormats 
{
public:

char* Getbluetoothformat (float filtervlaznost)
  {
    char str[40];
    sprintf(str, "%s%.3f %s\n", "Vlaznost: ", filtervlaznost, " %");
    return (str);
  }
};