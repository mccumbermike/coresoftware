#ifndef __PHGENEVENT_H__
#define __PHGENEVENT_H__

#include <limits.h>

#include <phool/phool.h>
#include <phool/PHObject.h>

#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <HepMC/GenParticle.h>

namespace HepMC {
  class GenEvent;
};

class PHGenEvent : public PHObject, public HepMC::GenEvent {
  
 public:
  
  virtual ~PHGenEvent() {}
  
  // The "standard PHObject response" functions...
  virtual void identify(std::ostream &os=std::cout) const {
    os << "PHGenEvent base class" << std::endl;
  }
  virtual void Reset() {}
  virtual int  isValid() const {return 0;}
  virtual PHGenEvent* Clone() const {return NULL;}

  // extended attributes
  
  virtual unsigned int get_id() const          {return UINT_MAX;}
  virtual void         set_id(unsigned int id) {}

  virtual void set_momentum_unit(int unit) {}
  virtual int  get_momentum_unit() const {return -1;}

  virtual void set_length_unit(int unit) {}
  virtual int  get_length_unit() const {return -1;}

  // old interface from MattS...

  virtual HepMC::GenEvent* getEvent() {return NULL;}

  virtual bool addEvent(HepMC::GenEvent *evt) {return true;}
  virtual bool addEvent(HepMC::GenEvent &evt) {return true;}
  virtual bool swapEvent(HepMC::GenEvent *evt) {return true;}
  virtual void clearEvent() {return;}

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

protected:
  
  PHGenEvent(const int momentum_unit = HepMC::Units::GEV,
	     const int distance_unit = HepMC::Units::CM);
  PHGenEvent(const HepMC::GenEvent& event,
	     const int momentum_unit = HepMC::Units::GEV,
	     const int distance_unit = HepMC::Units::CM);
  PHGenEvent(const PHGenEvent& event);
  PHGenEvent& operator=(const PHGenEvent& event);
  
private:

  ClassDef(PHGenEvent,1)  
};

#endif	// __PHGENEVENT_H__
