#ifndef SPITransfer_h
#define SPITransfer_h

//#pragma once

#include "Packet.h"
#include "stm32f4xx_hal.h"
//#include "SlaveBoardConfig.h"
#include "SPITransfer_C.h"
#include "../LKIOCtrlBox_MSP/MSP_SPI.h"

#define null		-1

class SPITransfer
{
  public: // <<---------------------------------------//public
	Packet  packet;
	uint8_t bytesRead = 0;
	int8_t  status    = 0;
	uint8_t SPI_SLAVE_ACK 			= 0x53;
	uint8_t SPI_MASTERRead_ACK 		= 0xAC;
	uint8_t SPI_MASTERWrite_ACK 	= 0xCA;
	uint8_t SPI_Trans_END 			= 0xED;
#if 1
	SPITransfer(CHIPHandler_t *chipH, SPI_HandleTypeDef *theSPI = &hspi2, bool master = true);
	//SPITransfer(bool _debug) {begin(_debug);}
#endif

	void    begin(const configST configs);
	void    begin(const bool _debug = true);
	//void 	beginTransaction(void);
	//void 	endTransaction(void);
	bool Slave_writeSyncto_Master(uint8_t txData);
	bool Slave_SyncWith_Master(uint8_t rxData);
	uint8_t Master_writeCMDto_Slave_withPacket(const uint16_t& messageLen, const uint8_t boardID = null);		//uint8_t writeWithPacket(const uint16_t& messageLen, const uint8_t packetID = 0);
	uint8_t Slave_writeDATAto_Master_withPacket(const uint16_t& messageLen, const uint8_t boardID = null);		//uint8_t writeWithPacket(const uint16_t& messageLen, const uint8_t packetID = 0);
	void Slave_readDATAfrom_Master_withPacket();
	//void Master_readDATAfrom_Slave_withPacket(uint8_t cs = null);
	void Master_Spi1_Transfer(const uint8_t TxRxFlag = 0, const uint8_t boardID = null);
	void Slave_Spi2_Transfer(const uint8_t TxRxFlag = 0, const uint8_t boardID = null);
	uint8_t currentPacketID();
	void    reset();
	
	/*
	 uint16_t SPITransfer::txObj(const T &val, const uint16_t &index=0, const uint16_t &len=sizeof(T))
	 Description:
	 ------------
	  * Stuffs "len" number of bytes of an arbitrary object (byte, int,
	  float, double, struct, etc...) into the transmit buffer (txBuff)
	  starting at the index as specified by the argument "index"
	 Inputs:
	 -------
	  * const T &val - Pointer to the object to be copied to the
	  transmit buffer (txBuff)
	  * const uint16_t &index - Starting index of the object within the
	  transmit buffer (txBuff)
	  * const uint16_t &len - Number of bytes of the object "val" to transmit
	 Return:
	 -------
	  * uint16_t maxIndex - uint16_t maxIndex - Index of the transmit buffer (txBuff) that directly follows the bytes processed
	  by the calling of this member function
	*/
	template <typename T>
	uint16_t txObj(const T& val, const uint16_t& index = 0, const uint16_t& len = sizeof(T))
	{
		return packet.txObj(val, index, len);
	}


	/*
	 uint16_t SPITransfer::rxObj(const T &val, const uint16_t &index=0, const uint16_t &len=sizeof(T))
	 Description:
	 ------------
	  * Reads "len" number of bytes from the receive buffer (rxBuff)
	  starting at the index as specified by the argument "index"
	  into an arbitrary object (byte, int, float, double, struct, etc...)
	 Inputs:
	 -------
	  * const T &val - Pointer to the object to be copied into from the
	  receive buffer (rxBuff)
	  * const uint16_t &index - Starting index of the object within the
	  receive buffer (rxBuff)
	  * const uint16_t &len - Number of bytes in the object "val" received
	 Return:
	 -------
	  * uint16_t maxIndex - Index of the receive buffer (rxBuff) that directly follows the bytes processed
	  by the calling of this member function
	*/
	template <typename T>
	uint16_t rxObj(const T& val, const uint16_t& index = 0, const uint16_t& len = sizeof(T))
	{
		return packet.rxObj(val, index, len);
	}

	/*
	 uint8_t SPITransfer::sendDatum(const T &val, const uint16_t &len=sizeof(T))
	 Description:
	 ------------
	  * Stuffs "len" number of bytes of an arbitrary object (byte, int,
	  float, double, struct, etc...) into the transmit buffer (txBuff)
	  starting at the index as specified by the argument "index" and
	  automatically transmits the bytes in an individual packet
	 Inputs:
	 -------
	  * const T &val - Pointer to the object to be copied to the
	  transmit buffer (txBuff)
	  * const uint16_t &len - Number of bytes of the object "val" to transmit
	 Return:
	 -------
	  * uint8_t - Number of payload bytes included in packet
	*/
	template <typename T>
	uint8_t writeDatumWithPacket(const T& val, const uint16_t& len = sizeof(T))
	{
		return writeWithPacket(packet.txObj(val, 0, len));
	}


  private: // <<---------------------------------------//private
	SPI_HandleTypeDef *_spi = nullptr;

//	uint8_t spiRxData[spiRxDataLen];		//打印测试信息用

	CHIPHandler_t *_chipH;
	uint8_t _master, _cs;

	uint8_t spiTxRx_reRunTimes = 3;			//spi发送或接收的重复次数

	bool _begun;
};

#endif // SPITransfer_H

