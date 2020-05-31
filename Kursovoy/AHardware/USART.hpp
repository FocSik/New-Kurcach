#pragma once

#include "USARTConfig.hpp" // for UsartConfig, tParity, tBitsSize
// #include <cmath> //for USARTDIV
#include "usart2registers.hpp"

template <typename USARTModule, uint32_t ClockSpeed>

class USART 
{
  public:  
    
  static void On() 
  {
    USARTModule::CR1::UE::Enable::Set() ; 
    USARTModule::CR1::TE::Enable::Set() ;   
  }

  static void Config(UsartConfig config) 
  {
    SetSamplingMode (config.samplingmode) ;
    SetSpeed (config.speed) ;  
    SetStopBits (config.stopbits) ;
    SetBitsSize (config.bitssize) ;
    SetParity (config.parity) ;
  }
  
  static void SendData (char* ptr, uint16_t size) 
  {
    assert(size > 0);
    for (size_t i = 0; i < size; i++) 
    {
      SendByte(*ptr);
      ptr++ ;
    }
  }

private:

    static void SendByte(uint8_t Byte) 
    {
      while (!USARTModule::SR::TXE::DataRegisterEmpty::IsSet()) {
      };
    USARTModule::DR::Write(Byte) ;
    }
  
    static void SetStopBits(StopBits stopbits) 
    {
      switch (stopbits) 
    {
    case StopBits::OneBit:
    USARTModule::CR2::STOP::OneStopBit::Set() ;
    break ; 

    case StopBits::TwoBits:
    USARTModule::CR2::STOP::TwoStopBits::Set() ;
    break ;

    default:
    assert(false) ;
    break ;
    }
  } 

  static void SetBitsSize(BitsSize bitssize) 
  {   
    switch (bitssize) 
    {
      case BitsSize::Bits8:
      USARTModule::CR1::M::Data8bits::Set() ;
      break ;

      case BitsSize::Bits9:
      USARTModule::CR1::M::Data9bits::Set() ;
      break ;

      default:
      assert(false) ;
      break ;
    }
  }

  inline static uint32_t over8 = 0 ;

  static void SetSamplingMode(SamplingMode samplingmode) 
    {
      switch (samplingmode) 
      {
        case SamplingMode::Mode16:
        USARTModule::CR1::OVER8::OversamplingBy16::Set() ;
        over8 = 0 ;
        break ;

        case SamplingMode::Mode8:
        USARTModule::CR1::OVER8::OversamplingBy8::Set() ;
        over8 = 1 ;
        break ;

        default:
        assert(false) ;
        break ;
      }
    }

    static void SetParity(Parity parity) 
    {  
      switch (parity) 
      {
        case Parity::Even:
        USARTModule::CR1::PCE::ParityControlEnable::Set() ;
        USARTModule::CR1::PS::ParityEven::Set() ;
        break ;

        case Parity::Odd:
        USARTModule::CR1::PCE::ParityControlEnable::Set() ;
        USARTModule::CR1::PS::ParityOdd::Set() ;
        break ;

        case Parity::None:
        USARTModule::CR1::PCE::ParityControlDisable::Set() ;
        break ;

        default:
        assert(false) ;
        break ;
      }
    }
    
    static void SetSpeed(Speed speed) 
    {
      uint32_t speednum ;
      switch (speed) 
      {
        case Speed::Speed2400:
        speednum = 2400 ;
        break ;

        case Speed::Speed4800:
        speednum = 4800 ;
        break ;

        case Speed::Speed9600:
        speednum = 9600 ;
        break ;

        case Speed::Speed19200:
        speednum = 19200 ;
        break ;

        case Speed::Speed38400:
        speednum = 38400 ;
        break ;

        default:
        assert(false) ;
        break ;

      }      

      // 208 = 16000000/ (9600*8*(2-1)) ;
      uint32_t USARTDIVMANT = ClockSpeed/(speednum*8*(2-over8)) ;
      uint32_t USARTDIVFRACT = 16 * (ClockSpeed % (speednum*8*(2-over8)))/(speednum*8*(2-over8));
      USARTModule::BRR::Write((USARTDIVMANT<<4) | USARTDIVFRACT) ;  
  }
};