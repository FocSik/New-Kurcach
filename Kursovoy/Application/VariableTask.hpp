#ifndef VARIABLETASK_HPP
#define VARIABLETASK_HPP 

//For OsWrapper::Thread
//#include "thread.hpp" //For definition of class Thread
//#include <array> //For std::array
//#include "mailbox.hpp" //For definition of class MailBox
//#include "event.hpp" //For definition of class event
//#include "ADC.hpp" //For definition of class Adc
#include "Vlaznost.hpp" //For definition of class Variale
#include "Filter.hpp"//For definition of class Filter
#include <iostream>

using namespace::OsWrapper ;


template <typename myADC>

class VariableTask : public OsWrapper::Thread<512>
{
private:
  
 // inline static float value;
  Filter filter;
  Vlaznost myVlaznost; 
  
public:
  void Execute() override
  {
    myADC::SetChannel(0); //podkluchaem kanali
    myADC::dmaConfig(); //podkluchaem DMA 
    myADC::adcConfig(Resolution::Bits12, tSampleRate::Cycles480, tSampleRate::Cycles480);
  
    for( ; ;)
    {
        myADC::On(); //vkluchaen adc
        //myADC::Start();
        //myADC::GetCode();
        std::cout << "Code: " << myADC::GetCode() << std::endl; 
        myVlaznost.Calculation(myADC::GetCode());
        filter.Update(myVlaznost.GetValue());
        std::cout << "CodeVlaznost: " <<  filter.GetOldFilterValue() << std::endl;
        Sleep(100ms);
    } 
  }
  float GetFilterValue ()
  {
    return filter.GetOldFilterValue();
  }
};

#endif 