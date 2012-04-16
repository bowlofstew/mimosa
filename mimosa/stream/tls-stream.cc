#include <limits>
#include <cstring>

#include "tls-stream.hh"

namespace mimosa
{
  namespace stream
  {
    ssize_t
    TlsStream::readWrapper(TlsStream * stream, char * data, size_t nbytes)
    {
      return stream->stream_->read(data, nbytes, stream->read_timeout_);
    }

    ssize_t
    TlsStream::writeWrapper(TlsStream * stream, const char * data, size_t nbytes)
    {
      return stream->stream_->write(data, nbytes, stream->write_timeout_);
    }

    ssize_t
    TlsStream::writevWrapper(TlsStream * stream, const giovec_t * iov, int iovcnt)
    {
      return stream->stream_->writev((struct iovec*)iov, iovcnt, stream->write_timeout_);
    }

    TlsStream::TlsStream(Stream::Ptr stream, bool is_server)
      : Filter(stream),
        session_(),
        read_timeout_(0),
        write_timeout_(0)
    {
      gnutls_init(&session_, is_server ? GNUTLS_SERVER : GNUTLS_CLIENT);
      gnutls_transport_set_ptr(session_, this);
      gnutls_transport_set_pull_function(session_, (gnutls_pull_func)readWrapper);
      gnutls_transport_set_push_function(session_, (gnutls_push_func)writeWrapper);
      gnutls_transport_set_vec_push_function(session_, (gnutls_vec_push_func)writevWrapper);
      // TODO: set vec push
    }

    TlsStream::~TlsStream()
    {
      gnutls_deinit(session_);
      session_ = nullptr;
    }

    int64_t
    TlsStream::write(const char * data, uint64_t nbytes, runtime::Time timeout)
    {
      write_timeout_ = timeout;
      nbytes = std::min(nbytes, (uint64_t)std::numeric_limits<ssize_t>::max());
      return gnutls_record_send(session_, data, nbytes);
    }

    int64_t
    TlsStream::read(char * data, uint64_t nbytes, runtime::Time timeout)
    {
      read_timeout_ = timeout;
      nbytes = std::min(nbytes, (uint64_t)std::numeric_limits<ssize_t>::max());
      return gnutls_record_recv(session_, data, nbytes);
    }

    void
    TlsStream::close()
    {
      ::gnutls_bye(session_, GNUTLS_SHUT_WR);
      stream_->close();
    }
  }
}
