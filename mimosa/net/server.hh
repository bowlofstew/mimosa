#ifndef MIMOSA_NET_SERVER_HH
# define MIMOSA_NET_SERVER_HH

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include <string>

# include "../function.hh"
# include "../runtime/fiber.hh"

namespace mimosa
{
  namespace net
  {
    class Server
    {
    public:
      Server();
      ~Server();

      typedef Function<void (int fd)> AcceptHandler;

      bool listenUnix(const std::string & path);
      bool listenInet4(uint16_t port, const struct ::in_addr * interface = 0);
      bool listenInet6(uint16_t port, const struct ::in6_addr * interface = 0);
      void onAccept(AcceptHandler::Ptr handler);
      void stop();

    private:
      void acceptLoop();

      AcceptHandler::Ptr handler_;
      int                fd_;
      bool               stop_;
      runtime::Fiber *   accept_loop_;
    };
  }
}

#endif /* !MIMOSA_NET_SERVER_HH */