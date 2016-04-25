/*
 * buttons.c
 *
 *  Created on: Apr 25, 2016
 *      Author: Lukas
 */

#include <stdio.h>					/* Standard input and output			*/
#include <stm32f4xx.h>				/* Processor STM32F407IG				*/
#include <carme.h>					/* CARME Module							*/

#include <FreeRTOS.h>				/* FreeRTOS								*/
#include <task.h>					/* FreeRTOS tasks						*/
#include <queue.h>					/* FreeRTOS queues						*/
#include <semphr.h>					/* FreeRTOS semaphores					*/
#include <memPoolService.h>			/* Memory pool manager service			*/

#include <carme_io1.h>
#include <carme_io2.h>
#include <buttons.h>

static QueueHandle_t *pvButtonQueue;



void ButtonTask(void *pvargs)
{
	uint8_t ButtonValue=0;
	Msg_Buttons_t ButtonMsg;
	if(pvargs!=NULL)
	{
		pvButtonQueue=(QueueHandle_t *)pvargs;

		for (;;)
		{
			CARME_IO1_SWITCH_Get(&ButtonValue);
			ButtonMsg.ButtonStatus=ButtonValue;
			xQueueSendToBack(*pvButtonQueue, &ButtonMsg, 1);
			vTaskDelay(100);
		}
	}
}
