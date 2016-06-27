#ifndef __PHEVENTGENMETHOD_H__
#define __PHEVENTGENMETHOD_H__

#include "PHGenEvent.h"

#include <string>

#include <phool/PHObject.h>

class PHEventGenMethod : public PHObject {
  
public:
  
  virtual ~PHEventGenMethod();

  virtual std::string  get_name() const {return _name;}
  
  virtual void         set_seed(const unsigned int seed) {return;}
  virtual unsigned int get_seed() const {return 0;}
  
  virtual bool generate_event(PHGenEvent* eventdata) const {return false;}
  
 protected:

  PHEventGenMethod(const std::string &name = "PHEVENTGENMETHOD");

 private:

  std::string _name;
};

#endif	/* __PHEVENTGENMETHOD_H__ */

