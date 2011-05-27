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

#ifndef CCB_IO_CONNECTOR_HH_
# define CCB_IO_CONNECTOR_HH_

# include <QSharedPointer>
# include "io/endpoint.hh"
# include "io/stream.hh"

namespace                           com {
  namespace                         centreon {
    namespace                       broker {
      namespace                     io {
        /**
         *  @class connector connector.hh "io/connector.hh"
         *  @brief Connector class.
         *
         *  Connect to some remote endpoint.
         */
        class                       connector : public endpoint {
         protected:
          QSharedPointer<connector> _down;

         public:
                                    connector();
                                    connector(connector const& c);
          virtual                   ~connector();
          connector&                operator=(connector const& c);
          virtual void              connect(QSharedPointer<stream> ptr
                                      = QSharedPointer<stream>()) = 0;
          void                      on(QSharedPointer<connector> down);
        };
      }
    }
  }
}

#endif /* !CCB_IO_CONNECTOR_HH_ */