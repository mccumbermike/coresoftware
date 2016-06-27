#ifndef __PHGENEVENTMAP_H__
#define __PHGENEVENTMAP_H__

#include "PHGenEvent.h"

#include <phool/PHObject.h>
#include <map>

class PHGenEventMap : public PHObject {
  
public:

  typedef std::map<unsigned int, PHGenEvent*> GenEventMap;
  typedef std::map<unsigned int, PHGenEvent*>::const_iterator ConstIter;
  typedef std::map<unsigned int, PHGenEvent*>::iterator            Iter;  
  
  virtual ~PHGenEventMap() {}

  virtual void identify(std::ostream& os = std::cout) const {
    os << "PHGenEventMap base class" << std::endl;
  }
  virtual void Reset() {}
  virtual int  isValid() const {return 0;}
  virtual PHGenEventMap* Clone() const {return NULL;}
  
  virtual bool   empty()                   const {return true;}
  virtual size_t  size()                   const {return 0;}
  virtual size_t count(unsigned int idkey) const {return 0;}
  virtual void   clear()                         {}
  
  virtual const PHGenEvent* get(unsigned int idkey) const {return NULL;}
  virtual       PHGenEvent* get(unsigned int idkey) {return NULL;}
  virtual       PHGenEvent* insert(const PHGenEvent *event) {return NULL;}
  virtual       size_t      erase(unsigned int idkey) {return 0;}

  virtual ConstIter begin()                   const {return GenEventMap().end();}
  virtual ConstIter  find(unsigned int idkey) const {return GenEventMap().end();}
  virtual ConstIter   end()                   const {return GenEventMap().end();}

  virtual Iter begin()                   {return GenEventMap().end();}
  virtual Iter  find(unsigned int idkey) {return GenEventMap().end();}
  virtual Iter   end()                   {return GenEventMap().end();}

protected:

  PHGenEventMap() {}
  
private:

  ClassDef(PHGenEventMap, 1);
};

#endif
