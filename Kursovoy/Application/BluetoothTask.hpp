#pragma once
//For OsWrapper::Thread
//#include "thread.hpp" //For definition of class Thread
//#include <array> //For std::array
//#include "BluetoothFormat.hpp"
//#include "VariableTask.hpp"
#include "BluetoothFormats.hpp"
//#include "susudefs.hpp" // for SusuString
//#include "Filter.hpp"
//#include "USART.hpp"
//#include <iostream>
//#include <cstring> //For strlen

using namespace::OsWrapper ;

//pointer to MailBox in spase OsWrapper
//using tMailBox = OsWrapper::MailBox<uint32_t, 1> ;

template <typename myUSART, auto& myVariableTask>

class BluetoothTask : public OsWrapper::Thread<512>
{
  private:

  BluetoothFormats bluetoothformat;  
  float filtervlaznost = 0.0f;
  char* rezault;  
  
  public:
    
  void Execute() override
  {

    UsartConfig USART2Config ;
    USART2Config.speed = Speed::Speed9600 ;
    USART2Config.stopbits = StopBits::OneBit ;
    USART2Config.bitssize = BitsSize::Bits8 ;
    USART2Config.parity = Parity::None ;
    USART2Config.samplingmode = SamplingMode::Mode8 ;
    myUSART::Config(USART2Config);
    myUSART::On();

    for( ; ;)
    {
      filtervlaznost = myVariableTask.GetFilterValue();
      Sleep(1000ms);
      std::cout << "FilterVlaznost: " <<  myVariableTask.GetFilterValue() << std::endl;
      char* rezault = bluetoothformat.Getbluetoothformat(filtervlaznost);
      myUSART::SendData(rezault, strlen(rezault));
    }
  }
};