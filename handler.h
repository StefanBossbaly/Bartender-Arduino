/*
 * command_handler.h
 *
 *  Created on: Mar 30, 2014
 *      Author: stefan
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stepper.h"
#include "bartender.h"
#include "inttypes.h"

typedef struct
{
	bartender_t *bartender;
} handler_t;

void handler_init(handler_t *handler, bartender_t *bartender);
void handler_handle(handler_t *handler, uint8_t *cmd, uint8_t *rsp);


#ifdef __cplusplus
}
#endif

#endif /* HANDLER_H_ */
