/*
** Copyright 2011 Merethis
** This file is part of Centreon Broker.
**
** Centreon Broker is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Broker is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Broker. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include "com/centreon/broker/io/protocols.hh"
#include "com/centreon/broker/storage/factory.hh"

using namespace com::centreon::broker;

// Load count.
static unsigned int instances(0);

extern "C" {
  /**
   *  Module deinitialization routine.
   *
   *  @param[in] force true if module unloading is forced (no need to
   *                   cleanup.
   */
  void broker_module_deinit(bool force) {
    // Decrement instance number.
    if (!--instances && !force)
      // Deregister storage layer.
      io::protocols::instance().unreg("storage");
    return ;
  }

  /**
   *  Module initialization routine.
   */
  void broker_module_init() {
    // Increment instance number.
    if (!instances++)
      // Register storage layer.
      io::protocols::instance().reg("storage",
        storage::factory(),
        1,
        7);
    return ;
  }
}