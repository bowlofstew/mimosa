#ifndef MIMOSA_NET_CONNECT_HH
# define MIMOSA_NET_CONNECT_HH

# include <cstdint>
# include <string>

# include "../runtime/time.hh"

namespace mimosa
{
  namespace net
  {
    int connectToHost(const std::string & host, uint16_t port,
                      runtime::Time timeout = 0);
  }
}

#endif /* !MIMOSA_NET_CONNECT_HH */