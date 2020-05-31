#pragma once

#include "dma2registers.hpp"


template<class D>
class DMA
{
  public:
  static void ChannelSet() //vibor canala, c kotoromu podkluchaemsya (S0 - stream 0, CHSEL::Value0 - chanell 0)
  {
    D::S0CR::CHSEL::Value0::Set(); 
  }

  static void DirectionSet() //Ustanavlivaem napravlemie (periferiya-pamyat')
  {
    D::S0CR::DIR::Value0::Set();
  }
  
  static void DataSizeSet() //Ustanavlivaem ob'emi pamati periferii i pamaty

  {

    D::S0NDTR::NDT::Set(1);
    D::S0CR::MSIZE::Value2::Set();
    D::S0CR::MINC::Value1::Set();
    D::S0CR::PSIZE::Value2::Set();
    D::S0CR::PINC::Value0::Set();
  }

  static void TargetSet(uint32_t PeriAdrr, uint32_t Pcode) //Ustanabvimaem oblast pamati gde budut schitannie znachenia
  {
    D::S0PAR::Set(PeriAdrr);
    D::S0CR::CT::Value0::Set();
    D::S0M0AR::Set(Pcode);
  }

  static void StreamOn()  //Vkluchaen CircularMode, zapuskaem flow
  {
    D::S0CR::CIRC::Value1::Set();
    D::S0CR::EN::Value1::Set();
  }
};