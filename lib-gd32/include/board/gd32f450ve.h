/**
 * @file gd32f450ve.h
 *
 */
/* Copyright (C) 2024 by Arjan van Vught mailto:info@gd32-dmx.org */

#ifndef BOARD_GD32F450VE_H_
#define BOARD_GD32F450VE_H_

#if defined (NODE_ARTNET)
# include "custom/gd32f450ve-node.h"
#else
# include "custom/gd32f450ve-wing.h"
#endif

#endif /* BOARD_GD32F450VE_H_ */
