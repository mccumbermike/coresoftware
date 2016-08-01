#ifndef __PHHEPMCMETHOD_H__
#define __PHHEPMCMETHOD_H__

#include "PHEventGeneratorMethod.h"
#include "PHEventGeneratorBase.h"

#include <map>
#include <vector>
#include <string>

class PHHepMCMethod : public PHEventGeneratorMethod {

public:

  PHHepMCMethod(const std::string& filename,
		const std::string& name = "PHHepMCMethod");
  virtual ~PHHepMCMethod() {}

  bool init();
  bool generate_event(PHGenEvent *event);

private:

  std::string _filename;
};

#endif
