/*
 * ReturnInfo.cpp
 *
 *  Created on: 2020年7月9日
 *      Author: 59488
 */

#include <ReturnInfo.h>

#include "ClassUartTest.h"
#include "string.h"
#include "main.h"

ReturnInfo::ReturnInfo()
{

}

bool ReturnInfo::showBattery()
{
	ClassUartTest uartTest(huart2);
	if (uartTest.receiveMessage(myRxData, sizeof(myRxData), 100) == true) {
		if (myRxData[0] == 'b') {	//'b' means "Battery life info"
			HAL_Delay(100);
			if (uartTest.sendMessage(myTxData_Battery, sizeof(myTxData_Battery), 100) == true) {
				return true;
			}else
				return false;

		}else
			return false;

	}else
		return false;
}

bool ReturnInfo::showDistance()
{
	ClassUartTest uartTest(huart2);
	if (uartTest.receiveMessage(myRxData, sizeof(myRxData), 100) == true) {
		if (myRxData[0] == 'd') {//'d' means "Distance of the nearest obstacle info"
			HAL_Delay(100);
			if (uartTest.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100) == true) {
				return true;
			}else
				return false;

		}else
			return false;

	}else
		return false;
}
