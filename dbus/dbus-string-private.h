/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-string-private.h String utility class (internal to D-BUS implementation)
 * 
 * Copyright (C) 2002, 2003  Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef DBUS_STRING_PRIVATE_H
#define DBUS_STRING_PRIVATE_H

#include <config.h>

#include <dbus/dbus-memory.h>
#include <dbus/dbus-types.h>

#ifndef DBUS_CAN_USE_DBUS_STRING_PRIVATE
#error "Don't go including dbus-string-private.h for no good reason"
#endif

DBUS_BEGIN_DECLS

/**
 * @brief Internals of DBusString.
 * 
 * DBusString internals. DBusString is an opaque objects, it must be
 * used via accessor functions.
 */
typedef struct
{
  unsigned char *str;            /**< String data, plus nul termination */
  int            len;            /**< Length without nul */
  int            allocated;      /**< Allocated size of data */
  int            max_length;     /**< Max length of this string, without nul byte */
  unsigned int   constant : 1;   /**< String data is not owned by DBusString */
  unsigned int   locked : 1;     /**< DBusString has been locked and can't be changed */
  unsigned int   invalid : 1;    /**< DBusString is invalid (e.g. already freed) */
  unsigned int   align_offset : 3; /**< str - align_offset is the actual malloc block */
} DBusRealString;

DBUS_END_DECLS

#endif /* DBUS_STRING_PRIVATE_H */
