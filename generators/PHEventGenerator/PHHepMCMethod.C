#include "PHHepMCMethod.h"

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

PHHepMCMethod::PHHepMCMethod(const string& filename, const string& name): 
  PHEventGeneratorMethod(name),
  _filename(filename) {
  return;
  }

bool PHHepMCMethod::init() {
  return false;
}

bool PHHepMCMethod::generate_event(PHGenEvent* event) {
  return false;
}

