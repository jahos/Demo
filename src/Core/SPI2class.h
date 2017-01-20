/*
 * SPI2class.h
 *
 *  Created on: 19.01.2017
 *      Author: cwiec
 */

#ifndef CORE_SPI2CLASS_H_
#define CORE_SPI2CLASS_H_

#include "Spi.h"

class SPI2_class : public Spi
{
protected:
	SPI2_class();
		/*Instance to SPI object*/
	BufferQueue* m_outBuffer;
	BufferQueue* m_inBuffer;
	volatile CSsetS m_csSet;
public:

	void setBuffers(BufferQueue* inBuf,BufferQueue* outBuf);

	void setCS(CSsetS settings);

	void disableCS();

	bool isBusy();

	int getByte(); 				//pobiera z outBuf

	void storeByte(int byte); 	//zapisuje w inBuf

	void send();

	bool isLastByte();

	static SPI2_class & getInstance();

	virtual ~SPI2_class();
};

#endif /* CORE_SPI2CLASS_H_ */
