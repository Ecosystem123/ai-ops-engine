#pragma once
#include <boost/asio.hpp>
#include<string>
using namespace boost::asio;
using namespace boost::asio::local;
using namespace std;
inline io_context io;
inline stream_protocol::socket endpoint3(io);
string request;
