#ifndef NETWORK_CONFIG_HPP
#define NETWORK_CONFIG_HPP
#include <iostream>

struct senddata {
	char PROTOCOL_HEAD;
	char DATA_LENGTH;
	char DATA_OFFSET;
	char DATA_TYPE;
	char NETWORK_TYPE;
	char SENSOR_ADDR[2];
	char SENSOR_TYPE;
	char VALID_DATA[16];
	char CHECK_SUM;
};
void dataInit(void);

uint8_t crc8(uint8_t *data, uint8_t length);

#endif
