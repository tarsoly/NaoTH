#ifndef IMUDATA_H
#define IMUDATA_H

#include <string>

#include "Tools/DataStructures/Printable.h"
#include "Tools/DataStructures/Serializer.h"

#include "Tools/Math/Common.h"
#include "Tools/Math/Vector2.h"
#include "Tools/Math/Vector3.h"

namespace naoth
{
class IMUData: public naoth::Printable
{
public:
  //Vector2d<double> orientation;

  Vector3d location;
  Vector3d velocity;
  Vector3d acceleration; /* gravity adjusted */
  Vector3d gravity;
  Vector3d bias_acceleration;

  Vector3d rotation;
  Vector3d rotational_velocity;
  Vector3d bias_rotational_velocity;

  virtual void print(std::ostream& stream) const {

      stream << "all values in the local robot coordinate frame" << std::endl;
      stream << "----location------------" << std::endl;
      stream << "x   : " << location.x << " m"<< std::endl;
      stream << "y   : " << location.y << " m"<< std::endl;
      stream << "z   : " << location.z << " m"<< std::endl;
      stream << "----velocity------------" << std::endl;
      stream << "x   : " << velocity.x << " m/s"<< std::endl;
      stream << "y   : " << velocity.y << " m/s"<< std::endl;
      stream << "z   : " << velocity.z << " m/s"<< std::endl;
      stream << "|v| : " << velocity.abs() << " m/s" << std::endl;
      stream << "----acceleration--------" << std::endl;
      stream << "x   : " << acceleration.x << " m/s^2"<< std::endl;
      stream << "y   : " << acceleration.y << " m/s^2"<< std::endl;
      stream << "z   : " << acceleration.z << " m/s^2"<< std::endl;
      stream << "|a| : " << acceleration.abs() << " m/s^2" << std::endl;
      stream << "----gravity-------------" << std::endl;
      stream << "x   : " << gravity.x << " m/s^2"<< std::endl;
      stream << "y   : " << gravity.y << " m/s^2"<< std::endl;
      stream << "z   : " << gravity.z << " m/s^2"<< std::endl;
      stream << "|g| : " << gravity.abs() << " m/s^2" << std::endl;
      stream << "----acceleration bias---" << std::endl;
      stream << "x : " << bias_acceleration.x << " m/s^2"<< std::endl;
      stream << "y : " << bias_acceleration.y << " m/s^2"<< std::endl;
      stream << "z : " << bias_acceleration.z << " m/s^2"<< std::endl;
  }
};

  /*template<>
  class Serializer<IMUData>
  {
  public:
    static void serialize(const IMUData& representation, std::ostream& stream);
    static void deserialize(std::istream& stream, IMUData& representation);
  };*/
}

#endif // IMUDATA_H
