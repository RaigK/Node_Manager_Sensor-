/*
    Name:       Node_Manager_Sensor.ino
    Created:	11.05.2019 19:31:01
    Author:     TERRAIG2018\Raig
*/



/*
* The MySensors Arduino library handles the wireless radio link and protocol
* between your home built sensors/actuators and HA controller of choice.
* The sensors forms a self healing radio network with optional repeaters. Each
* repeater and gateway builds a routing tables in EEPROM which keeps track of the
* network topology allowing messages to be routed to nodes.
*
* Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
* Copyright (C) 2013-2017 Sensnology AB
* Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
*
* Documentation: http://www.mysensors.org
* Support Forum: http://forum.mysensors.org
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation.
*/

/**************************
Template
This sketch can be used as a template since containing the most relevant MySensors library configuration settings,
NodeManager's settings, all its the supported sensors commented out and a sketch structure fully functional to operate with
NodeManager. Just uncomment the settings you need and the sensors you want to add and configure the sensors in before()
*/

/**********************************
 * MySensors node configuration
 */

 // General settings

#define SKETCH_NAME "Temperature Sensor"
#define SKETCH_VERSION "1.0"
#define MY_DEBUG
#define MY_NODE_ID 120


// RFM69 radio settings
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER
//#define MY_RFM69_ENABLE_ENCRYPTION
//#define MY_RFM69_NETWORKID 100
//#define MY_DEBUG_VERBOSE_RFM69
//#define MY_RF69_IRQ_PIN D1
//#define MY_RF69_IRQ_NUM MY_RF69_IRQ_PIN
//#define MY_RF69_SPI_CS D2
//#define MY_RFM69_ATC_MODE_DISABLED


// Message signing settings
//#define MY_SIGNING_SOFT
//#define MY_SIGNING_SOFT_RANDOMSEED_PIN 7
//#define MY_SIGNING_REQUEST_SIGNATURES
//#define MY_SIGNING_ATSHA204
//#define MY_SIGNING_ATSHA204_PIN 4
//#define MY_SIGNING_REQUEST_SIGNATURES

// OTA Firmware update settings
//#define MY_OTA_FIRMWARE_FEATURE
//#define OTA_WAIT_PERIOD 300
//#define FIRMWARE_MAX_REQUESTS 2
//#define MY_OTA_RETRY 2

// OTA debug output
//#define MY_DEBUG_OTA (0)
//#define MY_OTA_LOG_SENDER_FEATURE
//#define MY_OTA_LOG_RECEIVER_FEATURE
//#define MY_DEBUG_OTA_DISABLE_ACK

// Advanced settings
#define MY_BAUD_RATE 115200
//#define MY_SMART_SLEEP_WAIT_DURATION_MS 500
#define MY_SPLASH_SCREEN_DISABLED
//#define MY_DISABLE_RAM_ROUTING_TABLE_FEATURE
#define MY_SIGNAL_REPORT_ENABLED

// Optimizations when running on 2032 Coin Cell. Also set nodeManager.setSleepBetweenSend(500) and run the board at 1Mhz
//#define MY_TRANSPORT_UPLINK_CHECK_DISABLED
//#define MY_TRANSPORT_WAIT_READY_MS  5000
//#define MY_SLEEP_TRANSPORT_RECONNECT_TIMEOUT_MS 2000
//#define MY_PARENT_NODE_ID 0
//#define MY_PARENT_NODE_IS_STATIC

//#define USE_BATTERY
//#define USE_SIGNAL
//#define USE_CONFIGURATION
//#define USE_SHT21
//#define USE_INTERRUPT
 /***********************************
  * NodeManager configuration
  */

#define NODEMANAGER_DEBUG ON
#define NODEMANAGER_INTERRUPTS OFF
#define NODEMANAGER_SLEEP ON
#define NODEMANAGER_RECEIVE OFF
#define NODEMANAGER_DEBUG_VERBOSE ON
#define NODEMANAGER_POWER_MANAGER OFF
#define NODEMANAGER_CONDITIONAL_REPORT ON
#define NODEMANAGER_EEPROM ON
#define NODEMANAGER_TIME OFF
#define NODEMANAGER_RTC OFF
#define NODEMANAGER_SD OFF
#define NODEMANAGER_HOOKING OFF
#define NODEMANAGER_OTA_CONFIGURATION OFF
#define NODEMANAGER_SERIAL_INPUT OFF

// import NodeManager library (a nodeManager object will be then made available)
#include <MySensors_NodeManager.h>
NodeManager node;


/***********************************
 * Add your sensors
 */

//PowerManager power(5,6);

 #include <sensors/SensorBattery.h>
 SensorBattery battery;


 #include <sensors/SensorSignal.h>
 SensorSignal signal;

 //#include <sensors/SensorAnalogInput.h>
 //SensorAnalogInput analog(A0);

 
//#include <sensors/SensorDs18b20.h>
//SensorDs18b20 ds18b20(3,1);

#include <sensors/SensorSHT21.h>
SensorSHT21 sht21;


 /***********************************
  * Main Sketch
  */

  // before
void before() {

	/***********************************
	 * Configure your sensors
	 */

	 // EXAMPLES:
	 // report measures of every attached sensors every 10 seconds
	 nodeManager.setReportIntervalSeconds(30);
	 // report measures of every attached sensors every 10 minutes
	 //nodeManager.setReportIntervalMinutes(10);
	 // set the node to sleep in 30 seconds cycles
	 nodeManager.setSleepSeconds(30);
	 // set the node to sleep in 5 minutes cycles
	 //nodeManager.setSleepMinutes(5);
	 // report battery level every 10 minutes
	 battery.setReportIntervalMinutes(1);
	 // set an offset to -1 to a thermistor sensor
	 //thermistor.setOffset(-1);
	 // change the id of a the first child of a sht21 sensor
	 //sht21.children.get(1)->setChildId(5);
	 // report only when the analog value is above 40%
	 //analog.children.get(1)->setMinThreshold(40);
	 // power all the nodes through dedicated pins
	 //nodeManager.setPowerManager(power);
 // battery sensor
	 battery.setMinVoltage(2.0);
	 battery.setMaxVoltage(3.2);

	 //battery.children.get(1)->setDescription("Alkaline");
	 
	 // call NodeManager before rutine
	 nodeManager.before();
}

// presentation
void presentation() {
	// call NodeManager presentation routine
	nodeManager.presentation();
}

// setup
void setup() {

	// call NodeManager setup routine
	nodeManager.setup();
	nodeManager.setIsMetric(true); //use metric units

}

// loop
void loop() {
	// call NodeManager loop routine
	nodeManager.loop();
}

#if NODEMANAGER_RECEIVE == ON
// receive
void receive(const MyMessage& message) {
	// call NodeManager receive routine
	nodeManager.receive(message);
}
#endif

#if NODEMANAGER_TIME == ON
// receiveTime
void receiveTime(unsigned long ts) {
	// call NodeManager receiveTime routine
	nodeManager.receiveTime(ts);
}
#endif