#include "include/easypr/network/networkConfig.hpp"


/*struct senddata {
	char PROTOCOL_HEAD;
	char DATA_LENGTH;
	char DATA_OFFSET;
	char DATA_TYPE;
	char NETWORK_TYPE;
	char SENSOR_ADDR[2];
	char SENSOR_TYPE;
	char VALID_DATA[16];
	char CHECK_SUM;
}sdata;*/

struct senddata sdata;

void dataInit(void)
{
	sdata.PROTOCOL_HEAD = 0x21;
	sdata.DATA_LENGTH = 16;
	sdata.DATA_OFFSET = 7;
	sdata.DATA_TYPE = 0;
	sdata.NETWORK_TYPE = 0x5a;
	sdata.SENSOR_ADDR[0] = 0x40;
	sdata.SENSOR_ADDR[1] = 0x23;
	sdata.SENSOR_TYPE = 0x8c;
}

uint8_t crc8(uint8_t *data, uint8_t length)
{
	uint8_t i;
	uint8_t crc = 0;        // Initial value
	while (length--)
	{
		crc ^= *data++;        // crc ^= *data; data++;
		for (i = 0; i < 8; i++)
		{
			if (crc & 0x80)
				crc = (crc << 1) ^ 0x07;
			else
				crc <<= 1;
		}
	}
	return crc;

}

