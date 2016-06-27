#ifndef __PHEVENTGENTRIGGER_H__
#define __PHEVENTGENTRIGGER_H__

#include "PHGenEvent.h"

#include <string>

#include <phool/PHObject.h>

class PHEventGenTrigger : public PHObject {
  
public:

  PHEventGenTrigger(const std::string &name = "PHEVENTGENTRIGGER");
  virtual ~PHEventGenTrigger();

  virtual bool trigger_event(const PHGenEvent* eventdata) {return true;}
  
 protected:
 private:
};

#endif	/* __PHEVENTGENTRIGGER_H__ */

