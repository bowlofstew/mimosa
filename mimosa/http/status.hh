#ifndef MIMOSA_HTTP_STATUS_HH
# define MIMOSA_HTTP_STATUS_HH

namespace mimosa
{
  namespace http
  {
    enum Status
    {
      kStatusContinue                     = 100,
      kStatusSwitchingProtocols           = 101,

      kStatusOK                           = 200,
      kStatusCreated                      = 201,
      kStatusAccepted                     = 202,
      kStatusNonAuthoritativeInfo         = 203,
      kStatusNoContent                    = 204,
      kStatusResetContent                 = 205,
      kStatusPartialContent               = 206,

      kStatusMultipleChoices              = 300,
      kStatusMovedPermanently             = 301,
      kStatusFound                        = 302,
      kStatusSeeOther                     = 303,
      kStatusNotModified                  = 304,
      kStatusUseProxy                     = 305,
      kStatusTemporaryRedirect            = 307,

      kStatusBadRequest                   = 400,
      kStatusUnauthorized                 = 401,
      kStatusPaymentRequired              = 402,
      kStatusForbidden                    = 403,
      kStatusNotFound                     = 404,
      kStatusMethodNotAllowed             = 405,
      kStatusNotAcceptable                = 406,
      kStatusProxyAuthRequired            = 407,
      kStatusRequestTimeout               = 408,
      kStatusConflict                     = 409,
      kStatusGone                         = 410,
      kStatusLengthRequired               = 411,
      kStatusPreconditionFailed           = 412,
      kStatusRequestEntityTooLarge        = 413,
      kStatusRequestURITooLong            = 414,
      kStatusUnsupportedMediaType         = 415,
      kStatusRequestedRangeNotSatisfiable = 416,
      kStatusExpectationFailed            = 417,

      kStatusInternalServerError          = 500,
      kStatusNotImplemented               = 501,
      kStatusBadGateway                   = 502,
      kStatusServiceUnavailable           = 503,
      kStatusGatewayTimeout               = 504,
      kStatusHTTPVersionNotSupported      = 505,
    };

    const char * statusToString(Status status);
  }
}

#endif /* !MIMOSA_HTTP_STATUS_HH */