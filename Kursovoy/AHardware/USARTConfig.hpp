#pragma once



enum class SamplingMode 
{
  Mode16 ,
  Mode8 ,
} ;



enum class Parity 
{
  Odd ,
  Even ,
  None ,
} ;



enum class BitsSize 
{
  Bits8 ,
  Bits9 ,
} ;



enum class Speed 
{
  Speed2400 ,
  Speed4800 ,
  Speed9600 ,
  Speed19200 ,
  Speed38400 ,
} ;



enum class StopBits 
{
  OneBit ,
  TwoBits ,
} ;



struct UsartConfig 
{
  Speed speed ;
  BitsSize bitssize ;
  Parity parity ;
  StopBits stopbits ;
  SamplingMode samplingmode ;
} ;