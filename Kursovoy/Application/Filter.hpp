#pragma once

#include <cmath> //For exp
#include "Vlaznost.hpp"


class Filter
{
  private:
  static constexpr float RC = 1000.0f; //postoiannaia vremeni
  static constexpr float dt = 100.0f; //chag discretizasii
  inline static const float tau = 1.0f - exp(-dt/RC); //peremennaia, zavisachaa ot RC i dt
  float OldFilterValue = 0.0f; //staroe otfiltrovanoe znachenie

  public:
  float Update(float value) //filtracia vlaznosti
  {
    float FilterValue = OldFilterValue+(value-OldFilterValue); //vicheclenie poluchennogo znachenia
    OldFilterValue = FilterValue; //zapisivaet tecuchee znachenie dla dalneichei raboti
    return FilterValue; //konets
  }

  float GetOldFilterValue ()
  {
    return OldFilterValue;
  }
} ;