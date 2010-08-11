/* 
 * File:   AccelerometerData.h
 * Author: Oliver Welter
 *
 * Created on 2. März 2009, 00:47
 */

#ifndef _ACCELEROMETERDATA_H
#define	_ACCELEROMETERDATA_H

#include <string>
#include "naorunner/Tools/DataStructures/Printable.h"
#include "naorunner/PlatformInterface/PlatformInterchangeable.h"
#include "naorunner/Tools/Math/Vector3.h"

using namespace std;

namespace naorunner
{

  class AccelerometerData : public Printable, public PlatformInterchangeable
  {
  public:
    enum AccelerometerID
    {
      X,
      Y,
      Z,
      numOfAccelerometer
    };
    double data[numOfAccelerometer];
    double rawData[numOfAccelerometer];

    AccelerometerData();
    ~AccelerometerData();

    Vector3<double> getAcceleration() const;

    static string getAccelerometerName(AccelerometerID acc);

    virtual void print(ostream& stream) const;
  };
}
#endif	/* _ACCELEROMETERDATA_H */

