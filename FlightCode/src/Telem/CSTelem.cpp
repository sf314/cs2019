

#include "CSTelem.h"


CSTelem::CSTelem() {
    // Init
}

String CSTelem::toString() {
    return String(teamId) + "," +
        String(met) + "," +
        String(packetCount) + "," +
        String(altitude) + "," +
        String(pressure) +  "," +
        String(temp) + "," +
        String(voltage) + "," +
        String(gpsTime) + "," +
        String(gpsLat) + "," +
        String(gpsLon) + "," +
        String(gpsAlt) + "," +
        String(gpsSats) + "," +
        String(pitch) + "," +
        String(roll) + "," +
        String(bladeSpinRate) + "," +
        String(state);
}