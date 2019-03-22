/**
 * Mission Configuration File
 * Stephen Flores
 * 
 * Provide definitions that determine flight software behaviour or configuration
 * All definitions specific to CanSat will have the `CS_` prefix
 */
#ifndef MISSION_CONFIG_H
#define MISSION_CONFIG_H

// ********** Mission Parameters
#define CS_DEPLOY_ALT 450
#define CS_GROUND_ALT_THRESH 50

// ********** Hardware Pinout
#define CS_RADIO_MISO_PIN 0
#define CS_RADIO_MOSI_PIN 1
#define CS_GPS_MISO_PIN 7
#define CS_GPS_MOSI_PIN 8
#define CS_LED_PIN 13
#define CS_BME_CHIPSELECT 10

#endif