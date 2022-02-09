#ifndef GNSS_H
#define GNSS_H

#include <stdint.h>
#include <stddef.h>

namespace GNSS {
    struct Coordinates {
        double latitude;
        double longitude;
        double altitude;
    };

    void Setup();

    void Message(uint8_t packet_id, uint8_t* payload, size_t payload_length);
}

#endif