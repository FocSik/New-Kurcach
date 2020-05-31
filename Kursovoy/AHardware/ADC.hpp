#pragma once
#include <array>
#include "DMA.hpp"


enum class Resolution

{
  Bits12,
  Bits10,
  Bits8,
  Bits6
};

enum class tSampleRate
{
  Cycles3,
  Cycles15,
  Cycles28,
  Cycles56,
  Cycles84,
  Cycles112,
  Cycles144,
  Cycles480
};

using myDMA = DMA<DMA2>;
using ChannelNum = uint32_t;


template<class T>
class ADC
{
  private:
  static inline std::uint16_t code;
  public:
  static void Start()
  {
    T::CR2::SWSTART::On::Set(); //Start conversion
  }
  static void On()
  {
    T::CR2::ADON::Enable::Set(); // Enable ADC1
  }

  static void dmaConfig()

  {
    T::CR2::DMA::Enable::Set();
    myDMA::ChannelSet();
    myDMA::DataSizeSet();
    myDMA::DirectionSet();
    myDMA::TargetSet(T::DR::Address, code);
    myDMA::StreamOn();
  }

  static void adcConfig(Resolution resolution, tSampleRate tsamplerate, tSampleRate vsamplerate)

  {
    switch(resolution)
    {
      case Resolution::Bits12:
      T::CR1::RES::Bits12::Set();
      break;

      case Resolution::Bits10:
      T::CR1::RES::Bits10::Set();
      break;

      case Resolution::Bits8:
      T::CR1::RES::Bits8::Set();
      break;

      case Resolution::Bits6:
      T::CR1::RES::Bits6::Set();
      break;

      default:
      T::CR1::RES::Bits12::Set();
      break;
    }

    switch(tsamplerate)
    {
      case tSampleRate::Cycles3:
      T::SMPR1::SMP18::Cycles3::Set();
      break;

      case tSampleRate::Cycles15:
      T::SMPR1::SMP18::Cycles15::Set();
      break;

      case tSampleRate::Cycles28:
      T::SMPR1::SMP18::Cycles28::Set();
      break;

      case tSampleRate::Cycles56:
      T::SMPR1::SMP18::Cycles56::Set();
      break;

      case tSampleRate::Cycles84:
      T::SMPR1::SMP18::Cycles84::Set();
      break;

      case tSampleRate::Cycles112:
      T::SMPR1::SMP18::Cycles112::Set();
      break;

      case tSampleRate::Cycles480:
      T::SMPR1::SMP18::Cycles480::Set();
      break;

      default:
      T::SMPR1::SMP18::Cycles480::Set();
      break;
    }
  }

  static void SetChannel (std::uint16_t channelNum)
  {
    T::SQR1::L::Conversions1::Set();
    T::CR1::SCAN::Enable::Set();
    assert(channelNum <19);
    T::SQR3::SQ1::Set(channelNum);
  }
  
  static std::uint16_t& GetCode()

  {
    code= T::DR::Get();
    return code;
  }
};

