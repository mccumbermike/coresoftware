/*!
 *  \file		SpacepointMeasurement.h
 *  \brief		Handles the palnar type of measurements.
 *  \author		Haiwang Yu <yuhw@nmsu.edu>
 */


#ifndef __PHGenFit_SpacepointMeasurement__
#define __PHGenFit_SpacepointMeasurement__

#include "Measurement.h"

class TVector3;

namespace PHGenFit {

class SpacepointMeasurement : public Measurement
{
public:
	/*!
	 * Ctor
	 * \param pos measurement position
	 * \param resolution standard dev for diagnal elements of the cov, other elements are zero
	 */
	SpacepointMeasurement(const TVector3& pos, const double resolution);

	/*!
	 * Ctor
	 * \param pos measurement position
	 * \param covariance matrix
	 */
	SpacepointMeasurement(const TVector3& pos, const TMatrixDSym& cov);


	void init(const TVector3& pos, const TMatrixDSym& cov);

	//!dtor
	~SpacepointMeasurement();

protected:

	};
} //End of PHGenFit namespace

#endif //__PHGenFit_SpacepointMeasurement__
