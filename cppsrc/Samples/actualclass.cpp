#include "actualclass.h"

ActualClass::ActualClass(double value)
{
  _value = value;
}

double ActualClass::getValue()
{
  return _value;
} // getter for the value

double ActualClass::add(double toAdd)
{
  _value += toAdd;
  return _value;
} // adds the toAdd value to the value.
