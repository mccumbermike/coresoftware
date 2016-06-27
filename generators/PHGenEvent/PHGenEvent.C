#include "PHGenEvent.h"
#include <HepMC/GenEvent.h>

#include <TBuffer.h>
#include <TClass.h>

#include <RVersion.h> // root version 

#include <boost/foreach.hpp>

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

ClassImp(PHGenEvent)

using namespace std;

PHGenEvent::PHGenEvent(const int momentum_unit, const int length_unit)
    : PHObject(),
      HepMC::GenEvent() {}

PHGenEvent::PHGenEvent(const HepMC::GenEvent& event,
		       const int momentum_unit, const int length_unit)
    : PHObject(),
      HepMC::GenEvent(event) {}

PHGenEvent::PHGenEvent(const PHGenEvent& event) {
  *this = event;
  return;
}

PHGenEvent& PHGenEvent::operator=(const PHGenEvent& event) {
  HepMC::GenEvent::operator=(event);
  return *this;
}
