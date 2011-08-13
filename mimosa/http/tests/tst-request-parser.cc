#include <gtest/gtest.h>

#include "../request.hh"

namespace mimosa
{
  namespace http
  {
    namespace
    {
#define METHOD_TEST(Meth)                               \
      TEST(RequestParser, Meth##Simple)                 \
      {                                                 \
        char str[] = #Meth " / HTTP/1.0\r\n\r\n";       \
        Request rq;                                     \
        EXPECT_EQ(1, rq.parse(str, sizeof (str)));      \
      }

      METHOD_TEST(GET)
      METHOD_TEST(HEAD)
      METHOD_TEST(PUT)
      METHOD_TEST(DELETE)
      METHOD_TEST(TRACE)
      METHOD_TEST(OPTIONS)
      METHOD_TEST(CONNECT)
      METHOD_TEST(PATCH)

      TEST(RequestParser, CheckFields)
      {
        char str[] = "GET / HTTP/1.0\r\n"
          "Host: www.toto.com\r\n"
          "Connection: keep-alive\r\n"
          "Content-Length: 854\r\n"
          "Content-Type: text/*\r\n"
          "Referer: http://tutu.com/hoho%34/?tutu=tata;#anchor\r\n"
          "User-Agent: TomBoy (esapce compatible)\r\n"
          "SomeKey:  SomeValue\r\n"
          "Cookie: attr0; attr01; attr02; attr1=value1; attr2=value2;"
          "        attr3; attr4=value4; attr5=\"xvalue\\o\\\"\"\r\n"
          "Cookie: attr6 = value6 ; attr7 ; attr8 = \" value 8 \" \r\n"
          "\r\n";
        Request rq;
        EXPECT_EQ(true, rq.parse(str, sizeof (str)));
        EXPECT_EQ(rq.host(), "www.toto.com");
        EXPECT_EQ(rq.keepAlive(), true);
        EXPECT_EQ(rq.contentLength(), 854);
        EXPECT_EQ(rq.contentType(), "text/*");
        EXPECT_EQ(rq.referrer(), "http://tutu.com/hoho%34/?tutu=tata;#anchor");
        EXPECT_EQ(rq.userAgent(), "TomBoy (esapce compatible)");

        auto it = rq.cookies().find("attr1");
        EXPECT_NE(it, rq.cookies().end());
        if (it != rq.cookies().end())
          EXPECT_EQ(it->second, "value1");
        it = rq.cookies().find("attr5");
        EXPECT_NE(it, rq.cookies().end());
        if (it != rq.cookies().end())
          EXPECT_EQ(it->second, std::string("xvalueo\""));

        it = rq.unparsedHeaders().find("SomeKey");
        EXPECT_NE(it, rq.unparsedHeaders().end());
        if (it != rq.unparsedHeaders().end())
          EXPECT_EQ(it->second, "SomeValue");
      }
    }
  }
}