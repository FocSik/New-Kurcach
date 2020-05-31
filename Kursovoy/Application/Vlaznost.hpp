#pragma once

#include "ADC.hpp"
//#include <cmath>

class Vlaznost
{
  private:

  const float c0 = 0.0f;
  const float c1 = 0.0675633781f;
  const float c2 = -0.0000398299f;
  const float c3 = 0.0000000099f;
  float value = 0.0F;

  public:

  void Calculation(uint16_t code)
  {
    value = c0*pow(code, 0)+c1*pow(code, 1)+c2*pow(code, 2)+c3*pow(code, 3);
  }

  float GetValue()
  {
    return value;
  }
} ;