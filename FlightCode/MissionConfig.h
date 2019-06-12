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
#define CS_DEPLOY_ALT 460
#define CS_GROUND_ALT_THRESH 50
#define CS_DESCENT_VEL_THRESH -3
#define CS_ASCENT_VEL_THRESH 3

// ********** Hardware Pinout
#define CS_RADIO_MISO_PIN 0
#define CS_RADIO_MOSI_PIN 1
#define CS_GPS_MISO_PIN 7
#define CS_GPS_MOSI_PIN 8
#define CS_LED_PIN 13
#define CS_BME_CHIPSELECT 10

#define CS_VOLT1_PIN 15
#define CS_VOLT2_PIN 16
#define CS_NICHROME_PIN 2
#define CS_HALL_PIN 20
#define CS_BUZZER_PIN 17

// ********* States 
#define STATE_LAUNCHPAD 0
#define STATE_ASCENT 1
#define STATE_DESCENT 2
#define STATE_RELEASE 3
#define STATE_LANDED 4

// ********** Core Data Keys
#define CDKEY_GROUND_ALT "ALT_G"

#endif