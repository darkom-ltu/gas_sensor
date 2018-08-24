//          Copyright Emil Fresk 2015-2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <ros/ros.h>
#include <gas_sensor/multi_gas_sensor_msg.h>
#include <serialpipe.hpp>
#include <string>
#include <sstream>
#include <algorithm>

ros::Publisher gas_pub;

float valueNH3;
float valueCO;
float valueNO2;
float valueC3H8;
float valueC4H10;
float valueCH4;
float valueH2;
float valueC2H5OH;

void serial_callback(const std::vector< uint8_t > &data)
{
  std::string str(data.begin(), data.end());

  if (str.back() == '\n' && std::count(str.begin(), str.end(), ',') == 1)
  {
    str.pop_back();

    auto comma_pos = str.find_first_of(',');
    if (comma_pos > str.size())
      return;

    auto id = std::stoi(str.substr(0, comma_pos));
    float value = std::stoi(str.substr(comma_pos+1));

    gas_sensor::multi_gas_sensor_msg msg;

    msg.header.stamp = ros::Time::now();
    
    if (id == 0) valueNH3 = value/1000;
    if (id == 1) valueCO = value/1000;
    if (id == 2) valueNO2 = value/1000;
    if (id == 3) valueC3H8 = value/1000;
    if (id == 4) valueC4H10 = value/1000;
    if (id == 5) valueCH4 = value/1000;
    if (id == 6) valueH2 = value/1000;
    if (id == 7) valueC2H5OH = value/1000;


    msg.NH3 = valueNH3;
    msg.CO = valueCO;
    msg.NO2 = valueNO2;
    msg.C3H8 = valueC3H8;
    msg.C4H10 = valueC4H10;
    msg.CH4 = valueCH4;
    msg.H2 = valueH2;
    msg.C2H5OH = valueC2H5OH;

    gas_pub.publish(msg);
  }
}

int main(int argc, char *argv[])
{
  /*
   * Initializing ROS
   */
  ROS_INFO("Initializing Multi Gas Sensor...");
  ros::init(argc, argv, "gas_sensor");

  ros::NodeHandle nh("~");

  std::string port;
  if (!nh.getParam("port", port))
  {
    ROS_WARN("No serial port defined defaulting to /dev/ttyACM0.");
    port = "/dev/ttyACM0";
  }

  int baud;
  if (!nh.getParam("baudrate", baud))
  {
    ROS_INFO("No baudrate defined defaulting to 115200.");
    baud = 115200;
  }

  gas_pub = nh.advertise< gas_sensor::multi_gas_sensor_msg >("gas", 1);

  ROS_INFO_STREAM("Starting Multi Gas Sensor, listening on port " << port << " with baudrate " << baud);

  // Open serial
  serialpipe::bridge sp(port, baud, 50, true);
  sp.registerCallback(serial_callback);
  sp.openPort();

  /* Let ROS run. */
  ros::spin();

  sp.closePort();

  return 0;
}
