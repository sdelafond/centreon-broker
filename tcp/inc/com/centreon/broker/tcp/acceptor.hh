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

#ifndef CCB_TCP_ACCEPTOR_HH_
# define CCB_TCP_ACCEPTOR_HH_

# include <QTcpServer>
# include "com/centreon/broker/io/endpoint.hh"

namespace                com {
  namespace              centreon {
    namespace            broker {
      namespace          tcp {
        /**
         *  @class acceptor acceptor.hh "com/centreon/broker/tcp/acceptor.hh"
         *  @brief TCP acceptor.
         *
         *  Accept TCP connections.
         */
        class            acceptor : public io::endpoint {
         private:
          unsigned short _port;
	  QScopedPointer<QTcpServer>
                         _socket;
                         acceptor(acceptor const& a);
          acceptor&      operator=(acceptor const& a);

         public:
                         acceptor();
                         ~acceptor();
          void           close();
          void           listen_on(unsigned short port);
          QSharedPointer<io::stream>
                         open();
        };
      }
    }
  }
}

#endif /* !CCB_TCP_ACCEPTOR_HH_ */