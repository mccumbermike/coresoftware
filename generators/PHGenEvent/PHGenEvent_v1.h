#ifndef __PHGENEVENT_V1_H__
#define __PHGENEVENT_V1_H__

#include "PHGenEvent.h"

namespace HepMC {
  class GenEvent;
};

class PHGenEvent_v1 : public PHGenEvent {
  
 public:
  
  PHGenEvent_v1(const int momentum_unit = HepMC::Units::GEV,
		const int distance_unit = HepMC::Units::CM);
  PHGenEvent_v1(const HepMC::GenEvent& event,
		const int momentum_unit = HepMC::Units::GEV,
		const int distance_unit = HepMC::Units::CM);
  PHGenEvent_v1(const PHGenEvent_v1& event);
  PHGenEvent_v1& operator=(const PHGenEvent_v1& event);
  virtual ~PHGenEvent_v1();
  
  // The "standard PHObject response" functions...
  void identify(std::ostream &os=std::cout) const;
  void Reset() {*this = PHGenEvent_v1();}
  int  isValid() const;
  PHGenEvent* Clone() const {return new PHGenEvent_v1(*this);}

  // extended attributes
  
  unsigned int get_id() const {return _id;}
  void         set_id(unsigned int id) {_id = id;}

  void set_momentum_unit(int unit) {_momentum_unit = unit;}
  int  get_momentum_unit() const {return _momentum_unit;}

  void set_length_unit(int unit) {_length_unit = unit;}
  int  get_length_unit() const {return _length_unit;}

  // old interface from MattS...

  virtual HepMC::GenEvent* getEvent() {return this;}

  bool addEvent(HepMC::GenEvent *evt) {return true;}
  bool addEvent(HepMC::GenEvent &evt) {return true;}
  bool swapEvent(HepMC::GenEvent *evt) {return true;}
  void clearEvent() {return;}

  virtual void moveVertex(double x, double y, double z, double t = 0) {return;}

  // the number of entries in the array of particles
  virtual int size(void) const {return 1;}
  virtual int vertexSize(void) const {return 1;}

  //virtual int isValid() const {return 1;}

  //virtual void Reset() {return;}

  //virtual void identify(std::ostream& os=std::cout) const {return;}

  virtual void print(std::ostream& os=std::cout) const {return;}

  /*
  void PrintEvent();
  */

private:

  unsigned int _id;
  int _momentum_unit;
  int _length_unit;
  
  ClassDef(PHGenEvent_v1,1)  
};

#endif	// __PHGENEVENT_H__
