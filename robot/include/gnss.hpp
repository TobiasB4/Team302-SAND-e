#ifndef GNSS_H
#define GNSS_H

#include <stdint.h>
#include <stddef.h>
#include <pigpio.h>

#define defaultMaxWait 1100

char buf[20];

// enum borrowed from Sparkfun library
typedef enum {
    SFE_UBLOX_PACKET_VALIDITY_NOT_VALID,
    SFE_UBLOX_PACKET_VALIDITY_VALID,
    SFE_UBLOX_PACKET_VALIDITY_NOT_DEFINED,
    SFE_UBLOX_PACKET_NOTACKNOWLEDGED 
} sfe_ublox_packet_validity_e;

// enum borrowed from Sparkfun library
typedef enum {
    SFE_UBLOX_STATUS_SUCCESS,
    SFE_UBLOX_STATUS_FAIL,
    SFE_UBLOX_STATUS_CRC_FAIL,
    SFE_UBLOX_STATUS_TIMEOUT,
    SFE_UBLOX_STATUS_COMMAND_NACK, // not acknowledged
    SFE_UBLOX_STATUS_OUT_OF_RANGE,
    SFE_UBLOX_STATUS_INVALID_ARG,
    SFE_UBLOX_STATUS_INVALID_OPERATION,
    SFE_UBLOX_STATUS_MEM_ERR,
    SFE_UBLOX_STATUS_HW_ERR,
    SFE_UBLOX_STATUS_DATA_SENT, // set successful
    SFE_UBLOX_STATUS_DATA_RECEIVED, // get successful
    SFE_UBLOX_STATUS_I2C_COMM_FAILURE,
    SFE_UBLOX_STATUS_DATA_OVERWRITTEN
} sfe_ublox_status_e;

// ubxPacket borrowed from Sparkfun library
struct ubxPacket {
    uint8_t cls;
    uint8_t id;
    uint16_t len; // length of payload, not including cls/id/checksum bytes
    uint16_t counter; // number of overall bytes received
    uint16_t startingSpot; // spot (value after) at which payload should begin
    uint8_t *payload; 
    uint8_t checksumA; 
    uint8_t checksumB;
    sfe_ublox_packet_validity_e valid; // NOT_DEFINED to VALID or NOT_VALID when checksum checked
    sfe_ublox_packet_validity_e classAndIDmatch; // NOT_DEFINED to VALID or NOT_VALID when Class and ID match requestedClass and requestedID
};

class UbloxGnss {
    public: 
        int UbloxGNSS(void);

        // Begin I2C, w/ default I2C bus, address, and flag setting
        int i2cOpen(unsigned i2cBus = 0, unsigned i2cAddr = PI_I2C_ADDR, unsigned i2cFlags = 0);

        // Check for device connection [new]
        int CheckConnection(int handle);

        // Check for new I2C data, borrowed from Sparkfun library
        bool CheckData(ubxPacket *incomingUBX, uint8_t requestedClass, uint8_t requestedID);

        sfe_ublox_status_e SendCommand(ubxPacket *outgoingUBX, uint16_t maxWait = defaultMaxWait);
        
    private:

};

#endif