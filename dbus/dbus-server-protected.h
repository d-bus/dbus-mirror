/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-server-protected.h Used by subclasses of DBusServer object (internal to D-BUS implementation)
 *
 * Copyright (C) 2002  Red Hat Inc.
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
#ifndef DBUS_SERVER_PROTECTED_H
#define DBUS_SERVER_PROTECTED_H

#include <dbus/dbus-internals.h>
#include <dbus/dbus-server.h>
#include <dbus/dbus-timeout.h>
#include <dbus/dbus-watch.h>
#include <dbus/dbus-resources.h>
#include <dbus/dbus-dataslot.h>

DBUS_BEGIN_DECLS

typedef struct DBusServerVTable DBusServerVTable;

/**
 * Virtual table to be implemented by all server "subclasses"
 */
struct DBusServerVTable
{
  void        (* finalize)      (DBusServer *server);
  /**< The finalize method must free the server. */
  
  void        (* disconnect)    (DBusServer *server);
  /**< Disconnect this server. */
};

/**
 * Internals of DBusServer object
 */
struct DBusServer
{
  int refcount;                               /**< Reference count. */
  const DBusServerVTable *vtable;             /**< Virtual methods for this instance. */
  DBusWatchList *watches;                     /**< Our watches */
  DBusTimeoutList *timeouts;                  /**< Our timeouts */  

  char *address;                              /**< Address this server is listening on. */
  
  int max_connections;                        /**< Max number of connections allowed at once. */

  DBusDataSlotList slot_list;   /**< Data stored by allocated integer ID */
  
  DBusNewConnectionFunction  new_connection_function;
  /**< Callback to invoke when a new connection is created. */
  void *new_connection_data;
  /**< Data for new connection callback */
  DBusFreeFunction new_connection_free_data_function;
  /**< Callback to invoke to free new_connection_data
   * when server is finalized or data is replaced.
   */

  char **auth_mechanisms; /**< Array of allowed authentication mechanisms */
  
  unsigned int disconnected : 1;              /**< TRUE if we are disconnected. */
};

dbus_bool_t _dbus_server_init_base      (DBusServer             *server,
                                         const DBusServerVTable *vtable,
                                         const DBusString       *address);
void        _dbus_server_finalize_base  (DBusServer             *server);
dbus_bool_t _dbus_server_add_watch      (DBusServer             *server,
                                         DBusWatch              *watch);
void        _dbus_server_remove_watch   (DBusServer             *server,
                                         DBusWatch              *watch);
void        _dbus_server_toggle_watch   (DBusServer             *server,
                                         DBusWatch              *watch,
                                         dbus_bool_t             enabled);
dbus_bool_t _dbus_server_add_timeout    (DBusServer             *server,
                                         DBusTimeout            *timeout);
void        _dbus_server_remove_timeout (DBusServer             *server,
                                         DBusTimeout            *timeout);
void        _dbus_server_toggle_timeout (DBusServer             *server,
                                         DBusTimeout            *timeout,
                                         dbus_bool_t             enabled);



DBUS_END_DECLS

#endif /* DBUS_SERVER_PROTECTED_H */
