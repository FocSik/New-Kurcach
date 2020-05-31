#include "rtos.hpp" // for Rtos
//#include "event.hpp" // for Event
#include "rccregisters.hpp" // for RCC
//#include "thread.hpp"
#include "ADC.hpp"
#include "adc1registers.hpp"
#include "VariableTask.hpp"
#include "Vlaznost.hpp"
#include "USART.hpp"
//#include "susudefs.hpp"
#include "Filter.hpp"
//#include <iostream>
//#include "usart2registers.hpp"
//#include <cmath>
#include "gpioaregisters.hpp"
#include "BluetoothTask.hpp"
#include "BluetoothFormats.hpp"



std::uint32_t SystemCoreClock = 16'000'000U;

extern "C" {
int __low_level_init(void)
{
//Switch on external 16 MHz oscillator
RCC::CR::HSION::On::Set();
while (RCC::CR::HSIRDY::NotReady::IsSet())
{

}
//Switch system clock on external oscillator
RCC::CFGR::SW::Hsi::Set();
while (!RCC::CFGR::SWS::Hsi::IsSet())
{

}

RCC::APB2ENR::SYSCFGEN::Enable::Set();
RCC::APB2ENR::ADC1EN::Enable::Set();
RCC::AHB1ENR::DMA2EN::Enable::Set();
RCC::AHB1ENR::GPIOAEN::Enable::Set();// takt na port a
GPIOA::MODER::MODER0::Analog::Set();

RCC::APB1ENR::USART2EN::Enable::Set() ;
GPIOA::MODER::MODER2::Alternate::Set(); //Alternate moder 2
GPIOA::MODER::MODER3::Alternate::Set(); //Alternate moder 3
GPIOA::AFRL::AFRL2::Af7::Set(); //A2
GPIOA::AFRL::AFRL3::Af7::Set(); //A3
return 1;
}
}

//OsWrapper::Event event{500ms, 1}; //FIXME Чисто для примера
//MyTask myTask(event, UserButton::GetInstance()); //FIXME Чисто для примера

//MyTask myTask(event, UserButton::GetInstance()); //FIXME ????? ??? ???????
using myADC = ADC<ADC1>;
using myUSART = USART<USART2, 16000000U>;

VariableTask<myADC> myVariableTask;
BluetoothTask<myUSART, myVariableTask> myBluetoothTask;



int main() {

using namespace OsWrapper;
Rtos::CreateThread(myVariableTask, "Execute", ThreadPriority::normal);
Rtos::CreateThread(myBluetoothTask, "Execute", ThreadPriority::normal);
Rtos::Start();


return 0;

};
