/*
**  Copyright 2009 MERETHIS
**  This file is part of CentreonBroker.
**
**  CentreonBroker is free software: you can redistribute it and/or modify it
**  under the terms of the GNU General Public License as published by the Free
**  Software Foundation, either version 2 of the License, or (at your option)
**  any later version.
**
**  CentreonBroker is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
**  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
**  for more details.
**
**  You should have received a copy of the GNU General Public License along
**  with CentreonBroker.  If not, see <http://www.gnu.org/licenses/>.
**
**  For more information : contact@centreon.com
*/

#include <assert.h>
#include <stdlib.h>                   // for abort
#include "interface/db/destination.h"
#include "logging.h"
#include "nagios/broker.h"

using namespace Interface::DB;

/**************************************
*                                     *
*           Private Methods           *
*                                     *
**************************************/

/**
 *  \brief Destination copy constructor.
 *
 *  As Destination is not copiable, the copy constructor is declared private.
 *  Any attempt to use it will result in a call to abort().
 *
 *  \param[in] destination Unused.
 */
Destination::Destination(const Destination& destination)
  : Interface::Destination()
{
  (void)destination;
  assert(false);
  abort();
}

/**
 *  \brief Overload of the assignment operator.
 *
 *  As Destination is not copiable, the assignment operator is declared
 *  private. Any attempt to use it will result in a call to abort().
 *
 *  \param[in] destination Unused.
 *
 *  \return *this
 */
Destination& Destination::operator=(const Destination& destination)
{
  (void)destination;
  assert(false);
  abort();
  return (*this);
}

/**
 *  \brief Connect to the preconfigured database.
 *
 *  Using parameters provided by Init(), connect to the database server. Upon
 *  successful return, the connection can later be dropped by calling
 *  Disconnect().
 *
 *  \see Disconnect
 *  \see Init
 */
void Destination::Connect()
{
  std::vector<int> ids;
  std::vector<std::string> names;

  // Fetch already existing instances from the database.
  (*this->conn_) << "SELECT instance_id, instance_name FROM program_status",
    soci::into(ids), soci::into(names);

  // Insert instances in the cache.
  {
    std::vector<int>::const_iterator end_id, it_id;
    std::vector<std::string>::const_iterator end_name, it_name;

    end_id = ids.end();
    end_name = names.end();
    for (it_id = ids.begin(), it_name = names.begin();
	 (it_id != end_id) && (it_name != end_name);
	 ++it_id, ++it_name)
      this->instances_[*it_name] = *it_id;
  }

  return ;
}

/**
 *  \brief Disconnect from the database server.
 *
 *  Upon a successful call to Connect(), one can disconnect from the server by
 *  calling this method. All previously allocated ressources are freed.
 *
 *  \see Connect
 */
void Destination::Disconnect()
{
  // XXX
  this->instances_.clear();
  return ;
}

/**
 *  \brief Get the ID of an instance by its name.
 *
 *  The Destination class caches instance IDs as those are used within almost
 *  every table of the schema. This avoids expensive SELECT queries.
 *
 *  \param[in] instance The name of the Nagios instance.
 *
 *  \return The database ID of the Nagios instance.
 */
int Destination::GetInstanceID(const std::string& instance)
{
  int id;
  std::map<std::string, int>::iterator it;

  it = this->instances_.find(instance);
  if (it == this->instances_.end())
    {
    }
  else
    id = it->second;
  return (id);
}

/**
 *  Process an Acknowledgement event.
 */
void Destination::ProcessAcknowledgement(const Events::Acknowledgement& ack)
{
  LOGDEBUG("Processing Acknowledgement event ...");

  return ;
}

/**
 *  Process a Comment event.
 */
void Destination::ProcessComment(const Events::Comment& comment)
{
  LOGDEBUG("Processing Comment event ...");

  if ((comment.type == NEBTYPE_COMMENT_ADD)
      || comment.type == NEBTYPE_COMMENT_LOAD)
    {
    }
  else if (comment.type == NEBTYPE_COMMENT_DELETE)
    {
    }
  return ;
}

/**
 *  Process a Downtime event.
 */
void Destination::ProcessDowntime(const Events::Downtime& downtime)
{
  LOGDEBUG("Processing Downtime event ...");

  if ((downtime.type == NEBTYPE_DOWNTIME_ADD)
      || (downtime.type == NEBTYPE_DOWNTIME_LOAD))
    {
    }
  else if (downtime.type == NEBTYPE_DOWNTIME_START)
    {
    }
  else if ((downtime.type == NEBTYPE_DOWNTIME_STOP)
           || (downtime.type == NEBTYPE_DOWNTIME_DELETE))
    {
    }
  return ;
}

/**
 *  Process an Host event.
 */
void Destination::ProcessHost(const Events::Host& host)
{
  LOGDEBUG("Processing Host event ...");

  return ;
}

/**
 *  Process an HostCheck event.
 */
void Destination::ProcessHostCheck(const Events::HostCheck& host_check)
{
  LOGDEBUG("Processing HostCheck event ...");

  return ;
}

/**
 *  Process a HostDependency event.
 */
void Destination::ProcessHostDependency(const Events::HostDependency& hd)
{
  LOGDEBUG("Processing HostDependency event ...");

  return ;
}

/**
 *  Process a HostGroup event.
 */
void Destination::ProcessHostGroup(const Events::HostGroup& hg)
{
  LOGDEBUG("Processing HostGroup event...");

  return ;
}

/**
 *  Process a HostGroupMember event.
 */
void Destination::ProcessHostGroupMember(const Events::HostGroupMember& hgm)
{
  LOGDEBUG("Processing HostGroupMember event ...");

  return ;
}

/**
 *  Process a HostParent event.
 */
void Destination::ProcessHostParent(const Events::HostParent& hp)
{
  LOGDEBUG("Processing HostParent event ...");

  return ;
}

/**
 *  Process a HostStatus event.
 */
void Destination::ProcessHostStatus(const Events::HostStatus& hs)
{
  LOGDEBUG("Processing HostStatus event ...");

  return ;
}

/**
 *  Process a Log event.
 */
void Destination::ProcessLog(const Events::Log& log)
{
  LOGDEBUG("Processing Log event ...");

  return ;
}

/**
 *  Process a ProgramStatus event.
 */
void Destination::ProcessProgramStatus(const Events::ProgramStatus& ps)
{
  LOGDEBUG("Processing ProgramStatus event ...");

  return ;
}

/**
 *  Process a Service event.
 */
void Destination::ProcessService(const Events::Service& service)
{
  LOGDEBUG("Processing Service event ...");

  return ;
}

/**
 *  Process a ServiceCheck event.
 */
void Destination::ProcessServiceCheck(const Events::ServiceCheck& service_check)
{
  LOGDEBUG("Processing ServiceCheck event ...");

  return ;
}

/**
 *  Process a ServiceDependency event.
 */
void Destination::ProcessServiceDependency(const Events::ServiceDependency& sd)
{
  LOGDEBUG("Processing ServiceDependency event ...");

  return ;
}

/**
 *  Process a ServiceGroup event.
 */
void Destination::ProcessServiceGroup(const Events::ServiceGroup& sg)
{
  LOGDEBUG("Processing ServiceGroup event ...");

  return ;
}

/**
 *  Process a ServiceGroupMember event.
 */
void Destination::ProcessServiceGroupMember(const Events::ServiceGroupMember& sgm)
{
  LOGDEBUG("Processing ServiceGroupMember event ...");

  return ;
}

/**
 *  Process a ServiceStatus event.
 */
void Destination::ProcessServiceStatus(const Events::ServiceStatus& ss)
{
  LOGDEBUG("Processing ServiceStatus event ...");

  return ;
}

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  \brief Destination default constructor.
 *
 *  Initialize the Destination with default parameters.
 *
 *  \param[in] dbms Type of the database to use.
 */
Destination::Destination() {}

/**
 *  \brief Destination destructor.
 *
 *  Release all previously allocated ressources.
 */
Destination::~Destination()
{
  this->Disconnect();
}

/**
 *  Close the event destination.
 */
void Destination::Close()
{
  return ;
}

/**
 *  \brief Process an event.
 *
 *  When an event is poped from the list, it will be processed by this method.
 *  We will determine the true event type and process it accordingly.
 *
 *  \param[in] event Event that should be stored in the database.
 */
void Destination::Event(Events::Event* event)
{
  try
    {
      switch (event->GetType())
        {
         case Events::Event::ACKNOWLEDGEMENT:
          ProcessAcknowledgement(*static_cast<Events::Acknowledgement*>(event));
          break ;
         case Events::Event::COMMENT:
          ProcessComment(*static_cast<Events::Comment*>(event));
          break ;
         case Events::Event::DOWNTIME:
          ProcessDowntime(*static_cast<Events::Downtime*>(event));
          break ;
         case Events::Event::HOST:
          ProcessHost(*static_cast<Events::Host*>(event));
          break ;
         case Events::Event::HOSTCHECK:
          ProcessHostCheck(*static_cast<Events::HostCheck*>(event));
          break ;
         case Events::Event::HOSTDEPENDENCY:
          ProcessHostDependency(*static_cast<Events::HostDependency*>(event));
          break ;
         case Events::Event::HOSTGROUP:
          ProcessHostGroup(*static_cast<Events::HostGroup*>(event));
          break ;
         case Events::Event::HOSTGROUPMEMBER:
          ProcessHostGroupMember(*static_cast<Events::HostGroupMember*>(event));
          break ;
         case Events::Event::HOSTPARENT:
          ProcessHostParent(*static_cast<Events::HostParent*>(event));
          break ;
         case Events::Event::HOSTSTATUS:
          ProcessHostStatus(*static_cast<Events::HostStatus*>(event));
          break ;
         case Events::Event::LOG:
          ProcessLog(*static_cast<Events::Log*>(event));
          break ;
         case Events::Event::PROGRAMSTATUS:
          ProcessProgramStatus(*static_cast<Events::ProgramStatus*>(event));
          break ;
         case Events::Event::SERVICE:
          ProcessService(*static_cast<Events::Service*>(event));
          break ;
         case Events::Event::SERVICECHECK:
          ProcessServiceCheck(*static_cast<Events::ServiceCheck*>(event));
          break ;
         case Events::Event::SERVICEDEPENDENCY:
          ProcessServiceDependency(*static_cast<Events::ServiceDependency*>(event));
          break ;
         case Events::Event::SERVICEGROUP:
          ProcessServiceGroup(*static_cast<Events::ServiceGroup*>(event));
          break ;
         case Events::Event::SERVICEGROUPMEMBER:
          ProcessServiceGroupMember(*static_cast<Events::ServiceGroupMember*>(event));
          break ;
         case Events::Event::SERVICESTATUS:
          ProcessServiceStatus(*static_cast<Events::ServiceStatus*>(event));
          break ;
         default: // Discard event.
          LOGINFO("Invalid event type encountered.");
        }
    }
  catch (...)
    {
      // Event self deregistration.
      event->RemoveReader();

      // Rethrow the exception
      throw ;
    }

  // Event self deregistration.
  event->RemoveReader();

  return ;
}

/**
 *  \brief Initialize the object.
 *
 *  Set connection parameters and launch the processing thread.
 *
 *  \param[in] conn Already opened DB connection.
 */
void Destination::Init()
{
  this->Connect();
  return ;
}
