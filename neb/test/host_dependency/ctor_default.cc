/*
** Copyright 2012 Merethis
**
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

#include "com/centreon/broker/neb/host_dependency.hh"

using namespace com::centreon::broker;

/**
 *  Check host_dependency's default constructor.
 *
 *  @return 0 on success.
 */
int main() {
  // Object.
  neb::host_dependency hdep;

  // Check.
  return ((hdep.dependency_period != "")
          || (hdep.dependent_host_id != 0)
          || (hdep.enabled != true)
          || (hdep.execution_failure_options != "")
          || (hdep.host_id != 0)
          || (hdep.inherits_parent != false)
          || (hdep.notification_failure_options != "")
          || (hdep.type()
              != "com::centreon::broker::neb::host_dependency"));
}