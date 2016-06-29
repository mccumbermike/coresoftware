#include "PHEventGeneratorMethod.h"

#include <Geant4/G4ParticleTable.hh>
#include <Geant4/G4ParticleDefinition.hh>

#include <phool/PHRandomSeed.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

PHEventGeneratorMethod::PHEventGeneratorMethod(const std::string& name) :
  PHObject(),
  _name(name),
  _seed(0),
  _verbosity(0),
  _rand(NULL) {

  _rand = gsl_rng_alloc(gsl_rng_mt19937);
  _seed = PHRandomSeed(); // fixed seed is handled in this funtcion
  gsl_rng_set(_rand,_seed);
}

PHEventGeneratorMethod::~PHEventGeneratorMethod() {
  if (_rand) gsl_rng_free (_rand);
}

void PHEventGeneratorMethod::set_seed(const unsigned int seed) {
  _seed = seed;
  gsl_rng_set(_rand,_seed);
}

int PHEventGeneratorMethod::get_pdgcode(const std::string& name) const {
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = name;
  G4ParticleDefinition* particledef = particleTable->FindParticle(particleName);
  if (particledef) {
    return particledef->GetPDGEncoding();
  }
  return 0;
}

std::string PHEventGeneratorMethod::get_pdgname(const int pdgcode) const {
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particledef = particleTable->FindParticle(pdgcode);
  if (particledef) {
    return particledef->GetParticleName();
  }
  return 0;
}

double PHEventGeneratorMethod::get_mass(const int pdgcode) const {
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particledef =
      particleTable->FindParticle(get_pdgname(pdgcode));
  if (particledef) {
    return particledef->GetPDGMass();
  }
  return 0;
}
