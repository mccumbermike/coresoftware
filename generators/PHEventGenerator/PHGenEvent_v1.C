#include "PHGenEvent_v1.h"

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

ClassImp(PHGenEvent_v1)

using namespace std;

PHGenEvent_v1::PHGenEvent_v1(const int momentum_unit, const int length_unit)
    : PHGenEvent(),
      _id(0xFFFFFFFF),
      _momentum_unit(momentum_unit),
      _length_unit(length_unit) {}

PHGenEvent_v1::PHGenEvent_v1(const HepMC::GenEvent& event,
			     const int momentum_unit, const int length_unit)
  : PHGenEvent(event),
    _id(0xFFFFFFFF),
    _momentum_unit(momentum_unit),
    _length_unit(length_unit) {}

PHGenEvent_v1::PHGenEvent_v1(const PHGenEvent_v1& event) {
  *this = event;
  return;
}

PHGenEvent_v1& PHGenEvent_v1::operator=(const PHGenEvent_v1& event) {

  PHGenEvent::operator=(event);
  
  _id = event.get_id();
  _momentum_unit = event.get_momentum_unit();
  _length_unit = event.get_length_unit();

  return *this;
}

PHGenEvent_v1::~PHGenEvent_v1() {
}

void PHGenEvent_v1::identify(std::ostream& os) const {
  os << "PHGenEvent_v1 Object ";
  os << "id: " << get_id() << endl;
  os << "momentum unit: " << get_momentum_unit() << endl;
  os << "length unit: " << get_length_unit() << endl;
  os << "HepMC record: " << endl;
  HepMC::GenEvent::print(os);
  os << endl;    
 
  return;
}

int PHGenEvent_v1::isValid() const {
  return 1;
}
