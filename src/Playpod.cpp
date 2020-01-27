/*
	Project			 : play.pod.SDK. Copyright(c) play.pod.land (https://play.pod.land). All rights reserved.
	Source			 : Please direct any bug to https://github.com/FanapSoft/play.pod.SDK/issues
	Name			 : playpod.hpp
	Description		 : implementation of PlayPod services
*/

//+++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++
//comment following line for your project
#include "pch.h"
//+++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++

#include "Playpod.h"

using namespace playpod::sdk;

std::function<void(void)> playpod::sdk::on_services_ready_callback = nullptr;

#pragma region config

const char* config::ssoiau = (std::string(SERVICE_URL) + "/pages/iap/buy/default.aspx").c_str();
//use http instead of tcp or web socket
bool        config::harfs = false;
//use encryption
bool        config::ure = false;
//use tcp or websocket connection
bool        config::utc = true;
//peer name

#ifdef TEST_SERVER
const char* config::ahrrn = "bp.gc.sandbox";
#else
const char* config::ahrrn = "playpod.service";
#endif

//business id
int	config::business_id = 692;
//pc dl link
std::string config::palvdl;
//pc change log
std::string config::palvcl;
//pc version
std::string config::palv;
//pc min version
std::string config::pamv;
//force update
bool config::palvfu;

#pragma endregion

#pragma region network

uint64_t										Network::_peer_id = 0;
bool											Network::_is_released = false;
std::thread * Network::_thread = nullptr;
wolf::system::w_url * Network::_url = nullptr;
asio::ip::tcp::socket * Network::_socket = nullptr;
bool											Network::_is_ready = false;

// User Data
std::string										Network::_image;
int												Network::_customer_id;
std::string										Network::_name;
int												Network::_user_id;
std::string										Network::_profile_image;
std::string										Network::_token;
JSONObject                                     Network::_user_data;

#include "pch.h"
