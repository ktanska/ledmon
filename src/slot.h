/*
 * Intel(R) Enclosure LED Utilities
 * Copyright (C) 2023-2023 Intel Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef SLOT_H_
#define SLOT_H_

#include <stdio.h>

#include "block.h"
#include "cntrl.h"
#include "ibpi.h"
#include "utils.h"

/**
 * @brief slot property parameters
 *
 * This structure contains slot parameters.
 */
struct slot_property {
	/**
	 * Block device (if exists for slot).
	 */
	struct block_device *bl_device;

	/**
	 * Unique slot.
	 */
	void *slot;

	/**
	 * Controller type which is being represented by slot.
	 */
	enum cntrl_type cntrl_type;

	/**
	 * IBPI state.
	 */
	enum ibpi_pattern state;

	/**
	 * Pointer to the set slot function.
	 */
	status_t (*set_slot_fn)(void *slot, enum ibpi_pattern state);

	/**
	 * Pointer to the get slot function.
	 */
	status_t (*get_slot_fn)(void *slot, struct slot_property *res);
};

/**
 * @brief Init slot and fill its parameters.
 *
 * @param[in]        cntrl        Device for controller.
 *
 * @return This function does not return a value.
 */
struct slot_property *slot_init(void *cntrl, enum cntrl_type cntrl_type);

/**
 * @brief Free slot.
 *
 * @param[in]        cntrl        Slot parameters.
 *
 * @return This function does not return a value.
 */
void slot_fini(struct slot_property *slot);

/**
 * @brief Print address, slot identifier and led state.
 *
 * @param[in]        res        Structure with slot.
 *
 * @return This function does not return a value.
 */
void print_slot_state(struct slot_property *res);

/**
 * @brief Find slot device by path to slot.
 *
 * @param[in]        slot_path        Path to slot.
 * @param[in]        cntrl_type       Type of controller.
 *
 * @return This function returns related slot property.
 */
struct slot_property *find_slot_by_slot_path(char *slot_path, enum cntrl_type cntrl_type);

/**
 * @brief Find slot device by device name.
 *
 * @param[in]        device_name       Device name.
 * @param[in]        cntrl_type       Type of controller.
 *
 * @return This function returns related slot property.
 */
struct slot_property *find_slot_by_device_name(char *device_name, enum cntrl_type cntrl_type);

#endif // SLOT_H_INCLUDED_
