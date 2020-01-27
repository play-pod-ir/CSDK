
/*
/*
	Project			 : play.pod.SDK. Copyright(c) play.pod.land (https://play.pod.land). All rights reserved.
	Project			 : play.pod.SDK. Copyright(c) play.pod.land (https://play.pod.land). All rights reserved.
	Source			 : Please direct any bug to https://github.com/FanapSoft/play.pod.SDK/issues
	Name			 : playpod.hpp
	Description		 : declaration of PlayPod services
*/

#ifndef __PLAYPOD_H__
#define __PLAYPOD_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <w_url.h>
#include <mutex>
#include <condition_variable>
#include <stdio.h>
#include <codecvt>
#include <string>
#include <list>
#include <functional>
#include "json-c/json.h"

//asio
#define ASIO_STANDALONE
#include <asio.hpp>

//rapid json
#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <w_logger.h>

#define APP_ID					"GAME_CENTER_PC"
#define SERVER_NAME             "bg.game.msg"

#ifdef TEST_SERVER
#define SERVER_URL				"https://176.221.69.209:1036"
#define SERVICE_URL				"http://176.221.69.209:1036/srv/serviceApi"
#define ASYNC_SERVER_ADDRESS	"http://sandbox.pod.ir:8003"
#define ASYNC_SERVER_PORT		"8002"

#define PANEL_URL				"http://test.playpod.ir/panel"
#define EDIT_PROFILE_URL		"http://sandbox.pod.ir:1031/users/info/edit"
#define OUATH_URL				"https://accounts.pod.ir/oauth2/authorize/index.html?client_id=39105edd466f819c057b3c937374&response_type=code&redirect_uri=http://176.221.69.209:1036/Pages/Auth/SSOCallback/Default.aspx&scope=phone%20profile"
#else
#define SERVER_URL				"https://service-play.pod.ir/"
#define SERVICE_URL				"https://service-play.pod.ir/srv/serviceApi"
#define ASYNC_SERVER_ADDRESS    "https://playpod-bus.pod.ir"
#define ASYNC_SERVER_PORT		"80"

#define PANEL_URL				"https://play.pod.ir/panel/"
#define EDIT_PROFILE_URL		"https://panel.pod.ir/Users/Info"
#define OUATH_URL				"https://accounts.pod.ir/oauth2/authorize/index.html?client_id=16807y864b4ab6a05a80d602f5b6d7&response_type=code&redirect_uri=https://service-play.pod.ir:443/Pages/Auth/SSOCallback/Default.aspx&scope=phone%20profile"
#endif

#define MAX_MESSAGE_SIZE        2048

//services
#define PING									"user/ping"

#define URL_PING								"/srv/user/ping"
#define URL_GET_LIVE                            "/srv/match/getlive"
#define URL_GAME_INFO							"/srv/game/get"
#define URL_GET_LOBBIES							"/srv/lobby/get"
#define URL_GET_TOP_GAME						"/srv/game/top"
#define URL_GET_LOBBY_GAMES						"/srv/game/getbylobby"
#define URL_GET_GALLERY							"/srv/product/gallery"
#define URL_GET_RELATED_GAME					"/srv/game/related"
#define URL_GET_TOP_PLAYERS						"/srv/user/gettopplayers"
#define URL_REQUEST_STREAM_MATCH_ID				"/srv/stream/addmatch"
#define URL_DEFAULT_LEAGUE_SUBSCRIBE			"/srv/league/enrollDefault"
#define URL_FOLLOW_GAME							"/srv/game/follow"
#define URL_GAME_RATE							"/srv/game/rate"
#define URL_LOGOUT								"/srv/user/logout"
#define URL_GET_NEWS							"/srv/news/get"
#define URL_GET_GAME_FOLLOWING					"/srv/game/following"
#define URL_GET_USER_PROFILE					"/srv/user/getProfile"
#define URL_FOLLOW_POST							"/srv/user/follow"
#define URL_LIKE_POST							"/srv/user/like"
#define URL_GET_ONLINE_INFO						"/srv/game/onlineinfo"
#define URL_FILE_INFO							"/srv/game/fileinfo"
#define URL_MATCH_REQUEST_RESPONSE				"/srv/match/requestresult"
#define URL_USER_ACHIEVEMENTS					"/srv/user/achievements"
#define URL_USER_ACHIEVEMENT_DETAIL				"/srv/user/achievementdetails"
#define URL_USER_GAME_POINTS					"/srv/user/gamepoints"
#define URL_GET_COMMENT_LIST					"/srv/commentList/"
#define URL_ADD_GAME_COMMENT					"/srv/game/addcomment"
#define URL_RECEIVED_FRIENDSHIP_REQUEST			"/srv/user/receivedfriendshiprequestlist"
#define URL_SENT_FRIENDSHIP_REQUEST				"/srv/user/sentfriendshiprequestlist"
#define URL_FRIENDSHIP_REQUEST					"/srv/user/friendshiprequest"
#define URL_REPLY_FRIENDSHIP_REQUEST			"/srv/user/replyfriendshiprequest"
#define URL_CANCEL_FRIENDSHIP_REQUEST			"/srv/user/cancelfriendshiprequest"
#define URL_USER_FRIENDS						"/srv/user/friends"
#define URL_REMOVE_FRIEND_REQUEST				"/srv/user/cancelfriendship"
#define URL_ONLINE_USER							"/srv/user/getOnlineUsers"
#define URL_TOP_SCORE							"/srv/user/getTopScore"
#define URL_GET_LATEST_GAME						"/srv/game/latest"
#define URL_SEARCH_USER							"/srv/user/search"
#define URL_INVISIBLE							"/srv/user/invisible"
#define URL_OFFLINE_MATCH_REQUEST				"/srv/match/offlinerequest"
#define URL_REQUEST_MATCH						"/srv/match/matchrequest"
#define URL_CANCEL_MATCH_REQUEST				"/srv/match/cancelrequest"
#define URL_REQUEST_MATCH_ID					"/srv/match/add"
#define URL_GET_RELATED_LEAGUE					"/srv/league/related"
#define URL_GET_TOP_LEAGUE						"/srv/league/top"
#define	URL_GET_LATEST_LEAGUE					"/srv/league/latest"
#define URL_LEAGUE_MEMBERS						"/srv/league/members"
#define URL_GET_LEAGUE							"/srv/league/get"
#define URL_TABLE								"/srv/league/table"
#define URL_REQUEST_QUICK_MATCH					"/srv/match/addquick"
#define URL_CANCEL_QUICK_MATCH					"/srv/match/removequick"
#define URL_LEAGUE_AWARDS						"/srv/league/awards"
#define URL_GET_IN_APP_PURCHASE_PACK			"/srv/iap/getgamepacks"
#define URL_GET_GLOBAL_IN_APP_PURCHASE_PACK		"/srv/iap/getgcpacks"
#define URL_GET_GAME_ITEMS						"/srv/iap/searchgameitems"
#define URL_GET_USER_GC_ITEMS					"/srv/iap/getgcitems"
#define URL_GET_USER_ITEMS						"/srv/iap/getgameitems"
#define URL_CONSUME_ITEM						"/srv/iap/consume"
#define URL_FOLLOW_LEAGUE						"/srv/league/follow"
#define URL_GET_LEAGUE_TOP_PLAYERS				"/srv/user/topplayers"
#define URL_GET_TIME_LINE						"/srv/timeline"
#define URL_GET_LEAGUE_FOLLOWING				"/srv/league/following"
#define URL_GET_ENROLLED_LEAGUES				"/srv/user/enrolledleagues"
#define URL_CUSTOM_POST							"/srv/custompost/get"
#define URL_GET_LEAGUE_ENROLL_ACCESS			"/srv/league/enrollaccess"
#define URL_LEAGUE_RATE							"/srv/league/rate"
#define URL_GET_CREDIT_PACK_LIST				"/srv/getcreditpacklist"
#define URL_LEAGUE_MATCHES_RESULT				"/srv/user/matchresult"
#define URL_LEAGUE_LATEST_MATCHES_RESULT		"/srv/league/latestmatchresult"
#define URL_LEAGUE_LATEST_MATCHES_RESULT		"/srv/league/latestmatchresult"
#define URL_LEAGUE_MATCHES						"/srv/user/matches"
#define URL_ADD_LEAGUE_COMMENT					"/srv/league/addcomment"
#define URL_GAME_CENTER_STATUS					"/srv/manage/gcstatus"
#define URL_GET_LOBBY_LEAGUES					"/srv/league/getbylobby"

static std::once_flag s_once_init;
static char           s_last_error_code[MAX_MESSAGE_SIZE];
static std::mutex _mutex1;
namespace playpod
{
    namespace sdk
    {
        extern std::function<void(void)> on_services_ready_callback;

        static const char* get_last_error_code()
        {
            return s_last_error_code;
        }

        //convert c++ int to java int
        static int to_int(char pA, char pB, char pC, char pD)
        {
            return ((pA & 0xFF) << 24) | ((pB & 0xFF) << 16) | ((pC & 0xFF) << 8) | (pD & 0xFF);
        }

        struct config
        {
            //in app purchase url
            static const char* ssoiau;
            //use http for requests
            static bool harfs;
            //use encryption in requests
            static bool ure;
            //use tcp or websocket for connection
            static bool utc;
            //peer name
            static const char* ahrrn;
            //business id
            static int business_id;
            //pc dl link
            static std::string palvdl;
            //pc change log
            static std::string palvcl;
            //pc version
            static std::string palv;
            //pc min version
            static std::string pamv;
            //force update
            static bool palvfu;
        };

        struct JSONObject
        {
            JSONObject()
            {
                //use rapid json to make json
                this->_writer = new rapidjson::Writer<rapidjson::StringBuffer>(this->_write_buffer);
            }

            int from_object(const rapidjson::Value& pValue)
            {
                _document.CopyFrom(pValue, _document.GetAllocator());
                return 0;
            }

            //https://qiita.com/k2ymg/items/eef3b15eaa27a89353ab
            //typedef rapidjson::GenericDocument< rapidjson::UTF8<> > document_utf16;
            //typedef rapidjson::GenericValue< rapidjson::UTF8<> > value_utf16;
            //typedef rapidjson::GenericStringStream< rapidjson::UTF8<> > stringstream_utf16;
            //typedef rapidjson::GenericStringBuffer< rapidjson::UTF8<> > json_stringbuffer_utf16;

            int from_string(std::string& pJSONString)
            {
                using namespace rapidjson;
                //std::wstring_convert<std::codecvt_utf8<wchar_t>> _conv;
                //std::wstring _str = _conv.from_bytes(pJSONString);
                //reset last error code
                std::memset(s_last_error_code, '\0', MAX_MESSAGE_SIZE);
                auto _parser = &_document.Parse<rapidjson::kParseStopWhenDoneFlag>(pJSONString.c_str());
                if (_parser->HasParseError())
                {
                    sprintf(s_last_error_code, "error on parsing json. error code: %d\n", _parser->GetParseError());
                    return 1;
                }
                if (this->_writer)
                {
                    delete this->_writer;
                    this->_writer = nullptr;
                }
                this->_writer = new rapidjson::Writer<rapidjson::StringBuffer>(this->_write_buffer);
                _document.Accept(*this->_writer);

                if (!_document.IsObject()) return 1;

                return 0;
            }

            const std::string to_string()
            {
                if (this->_writer /*&& this->_writer->IsComplete()*/)
                {
                    return this->_write_buffer.GetString();
                }
                return "";
            }

            int begin_write()
            {
                if (!this->_writer) return 1;
                return this->_writer->StartObject() ? 0 : 1;
            }

            int end_write()
            {
                if (!this->_writer) return 1;
                return this->_writer->EndObject() ? 0 : 1;
            }

            int add_key(const char* pKey)
            {
                if (!this->_writer) return 1;
                return this->_writer->Key(pKey) ? 0 : 1;
            }

            int add_string_value(const char* pValue)
            {
                if (!this->_writer) return 1;
                return this->_writer->String(pValue) ? 0 : 1;
            }

            int add_boolean_value(const bool& pValue)
            {
                if (!this->_writer) return 1;
                return this->_writer->Bool(pValue) ? 0 : 1;
            }

            int add_uint_value(const uint32_t& pValue)
            {
                if (!this->_writer) return 1;
                return this->_writer->Uint(pValue) ? 0 : 1;
            }

            int add_uint64_value(const uint64_t& pValue)
            {
                if (!this->_writer) return 1;
                return this->_writer->Uint64(pValue) ? 0 : 1;
            }

            int add_int64_value(const int64_t& pValue)
            {
                if (!this->_writer) return 1;
                return this->_writer->Int64(pValue) ? 0 : 1;
            }

            int add_double_value(const double& pValue)
            {
                if (!this->_writer) return 1;
                return this->_writer->Double(pValue) ? 0 : 1;
            }

            int add_raw_number_value(const char* pValues, const int& pLenght)
            {
                if (!this->_writer) return 1;
                return this->_writer->RawNumber(pValues, pLenght) ? 0 : 1;
            }

            int add_null()
            {
                if (!this->_writer) return 1;
                return this->_writer->Null() ? 0 : 1;
            }

            int begin_object()
            {
                if (!this->_writer) return 1;
                return this->_writer->StartObject() ? 0 : 1;
            }

            int end_object()
            {
                if (!this->_writer) return 1;
                return this->_writer->EndObject() ? 0 : 1;
            }

            int begin_array()
            {
                if (!this->_writer) return -1;
                return this->_writer->StartArray() ? 0 : 1;
            }

            int end_array()
            {
                if (!this->_writer) return -1;
                return this->_writer->EndArray() ? 0 : 1;
            }

            int get_is_null(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsNull())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool get_is_false(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsFalse())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool get_is_true(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsTrue())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool get_is_bool(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsBool())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool get_is_object(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsObject())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool get_is_array(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsArray())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool get_is_number(const char* pKey) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsNumber())
                    {
                        return true;
                    }
                }
                return false;
            }

            int get_value(const char* pKey, bool& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsBool())
                    {
                        pValue = _document[pKey].GetBool();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, int& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsInt())
                    {
                        pValue = _document[pKey].GetInt();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, uint32_t& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsUint())
                    {
                        pValue = _document[pKey].GetUint();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, int64_t& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsInt64())
                    {
                        pValue = _document[pKey].GetInt64();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, uint64_t& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsUint64())
                    {
                        pValue = _document[pKey].GetUint64();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, double& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsDouble())
                    {
                        pValue = _document[pKey].GetDouble();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, std::string& pValue) const
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsString())
                    {
                        pValue = _document[pKey].GetString();
                        return 0;
                    }
                }
                return 1;
            }

            int get_value(const char* pKey, rapidjson::Value& pValue)
            {
                if (_document.IsNull()) return 1;
                if (_document.HasMember(pKey))
                {
                    if (_document[pKey].IsObject())
                    {
                        pValue = _document[pKey];
                        return 0;
                    }
                }
                return 1;
            }

            int get_object(const char* pKey, JSONObject& pJsonObject) const
            {
                if (_document.IsNull())
                    return 1;
                if (_document.HasMember(pKey))
                {
                    pJsonObject.from_object(_document[pKey]);
                    return 0;
                }
                return 1;
            }

            int get_array_value(const unsigned int& pIndex, JSONObject& pJsonObject) const
            {
                if (_document.IsNull()) return 1;
                if (_document.IsArray())
                {
                    const auto _size = _document.End() - _document.Begin();
                    if (pIndex < _size)
                    {
                        pJsonObject.from_object(_document[pIndex]);
                        return 0;
                    }
                }
                return 1;
            }

            int get_array_size() const
            {
                if (_document.IsNull()) return 0;
                if (!_document.IsArray()) return 0;
                return _document.End() - _document.Begin();
            }

            int release()
            {
                if (this->_is_released) return 1;

                this->_write_buffer.Clear();
                if (this->_writer)
                {
                    delete this->_writer;
                    this->_writer = nullptr;
                }
                this->_is_released = true;

                return 0;
            }

            std::string get_all_keys() const
            {
                if (_document.MemberCount() == 0)
                    return "[]";

                std::string _ret = "[ ";

                for (auto _it = _document.MemberBegin(); _it != _document.MemberEnd(); ++_it)
                {
                    std::string _key = _it->name.GetString();

                    _ret += _key;
                    _ret += ", ";
                }

                _ret.pop_back();
                _ret.pop_back();
                _ret += " ]";

                return _ret;
            }

            std::string get_all_values() const
            {
                if (_document.MemberCount() == 0)
                    return "[]";

                std::string _ret = "[ ";

                for (auto _it = _document.MemberBegin(); _it != _document.MemberEnd(); ++_it)
                {
                    std::string _key = _it->value.GetString();

                    _ret += _key;
                    _ret += ", ";
                }

                _ret.pop_back();
                _ret.pop_back();
                _ret += " ]";

                return _ret;
            }

        private:
            bool                                            _is_released = false;
            rapidjson::Document                             _document;
            rapidjson::StringBuffer                         _write_buffer;
            rapidjson::Writer<rapidjson::StringBuffer>* _writer = nullptr;
        };

        struct Network
        {
            /*
                native socket
                websocket
                http
             */
            static W_RESULT initialize_device_register(asio::io_service& pIO)
            {
                _is_ready = false;

                _url = new (std::nothrow) wolf::system::w_url();
                if (!_url) return W_FAILED;

                auto _abort_nums = w_point{ 100, 10 };

                //get config
                std::string _result;
                if (_url->request_url(
                        std::string(SERVICE_URL) + "/getConfig",
                        _result, _abort_nums) == W_FAILED)
                {
                    return W_FAILED;
                }

                if (!_result.empty())
                {
                    JSONObject _json;
                    _json.from_string(_result);

                    //get following data for config
                    _json.release();

                    JSONObject _result_json;
                    if (!_json.get_object("Result", _result_json))
                    {
                        JSONObject _config_json;

                        if (!_result_json.get_object("config", _config_json))
                        {
                            _config_json.get_value("harfs", config::harfs);
                            _config_json.get_value("ure", config::ure);
                            _config_json.get_value("utc", config::utc);
                            _config_json.get_value("palvdl", config::palvdl);
                            _config_json.get_value("palvcl", config::palvcl);
                            _config_json.get_value("palv", config::palv);
                            _config_json.get_value("pamv", config::pamv);
                            _config_json.get_value("palvfu", config::palvfu);
                        }
                        else
                        {
                            wolf::logger.error("DeviceRegister \"content\" object doesn't exist in json");
                        }
                    }
                    else
                    {
                        wolf::logger.error("DeviceRegister \"result\" object doesn't exist in json");
                    }

                    config::harfs = true;

                    //reset last error code
                    std::memset(s_last_error_code, '\0', MAX_MESSAGE_SIZE);

                    if (config::harfs)
                    {
                        _result.clear();
                        std::string _http_request = (std::string(ASYNC_SERVER_ADDRESS) +
                                                     "/register/?action=register&deviceId=" + "40d1448b-d0dd-41ba-f450-168c4c0bf98d" + "&appId=" + APP_ID);

                        if (_url->request_url(_http_request.c_str(), _result, _abort_nums) == W_FAILED)
                        {
                            return W_FAILED;
                        }

                        if (!_result.empty())
                        {
                            bool _success = false;
                            std::string _content_value;

                            JSONObject _json;
                            if (_json.from_string(_result))
                            {
                                sprintf(s_last_error_code, "could not register device via http request: %s", _http_request.c_str());
                                return W_FAILED;
                            }

                            _json.get_value("success", _success);
                            if (_success)
                            {
                                _json.get_value("content", _content_value);
                                if (!_content_value.empty())
                                {
                                    JSONObject _content_json;
                                    _content_json.from_string(_content_value);
                                    _content_json.get_value("token", _peer_id);
                                    _content_value.clear();

                                    _is_ready = true;
                                    if (on_services_ready_callback)
                                    {
                                        on_services_ready_callback();
                                    }
                                }
                            }
                            _result.clear();
                        }
                    }
                    else
                    {
                        W_RESULT _hr = W_PASSED;

                        //we don't need http request anymore
                        destroy_url();

                        char* _device_register_request = (char*)malloc(MAX_MESSAGE_SIZE);
                        sprintf(
                                _device_register_request,
                                "{\"appId\":\"GAME CENTER PC\",\"deviceId\":\"40d1448a-d0dd-41ba-f450-168c4c0bf98d\",\"renew\":true}\0");

                        if (config::utc)
                        {
                            //we will use tcp for async
                            if (initialize_tcp_socket(pIO))
                            {
                                //some problem was happended
                                _hr = W_FAILED;
                            }
                            else
                            {
                                send_async(_device_register_request, strlen(_device_register_request),
                                           [](JSONObject & pJson)
                                           {
                                               int _type = -1;
                                               pJson.get_value("type", _type);

                                               if (_type != 2)
                                               {
                                                   sprintf(s_last_error_code, "could not register device to server %s", ASYNC_SERVER_ADDRESS);
                                                   return;
                                               }

                                               std::string _content_str;
                                               pJson.get_value("content", _content_str);
                                               JSONObject _content_jo;
                                               if (_content_jo.from_string(_content_str))
                                               {
                                                   sprintf(s_last_error_code, "could not parse content type %s", ASYNC_SERVER_ADDRESS);
                                                   return;
                                               }
                                               _content_jo.get_value("token", _peer_id);

                                               char* _server_name_request = (char*)malloc(MAX_MESSAGE_SIZE);
                                               sprintf(
                                                       _server_name_request,
                                                       "{\"type\":%d,"
                                                       "\"content\":\"{\\\"name\\\":\\\"%s\\\"}\"}", 1, SERVER_NAME);

                                               send_async(_server_name_request, strlen(_server_name_request),
                                                          [](JSONObject & pJson)
                                                          {
                                                              int _type = -1;
                                                              pJson.get_value("type", _type);
                                                              if (_type == 1)
                                                              {
                                                                  _is_ready = true;
                                                                  if (on_services_ready_callback)
                                                                  {
                                                                      on_services_ready_callback();
                                                                  }
                                                              }
                                                          });

                                               free(_server_name_request);

                                           });
                            }
                        }
                        else
                        {
                            //we will use web socket for async
                        }
                        //free allocated memory
                        free(_device_register_request);

                        return _hr;
                    }
                }

                return W_PASSED;
            }

            static int initialize_tcp_socket(asio::io_service& pIO)
            {
                using asio::ip::tcp;
                _socket = new tcp::socket(pIO);
                if (!_socket)
                {
                    sprintf(s_last_error_code, "could not allocate memory for socket");
                    return 1;
                }

                bool _is_socket_avaiable = true;
                try
                {
                    tcp::resolver _resolver(pIO);
                    tcp::resolver::query _query(ASYNC_SERVER_ADDRESS, ASYNC_SERVER_PORT);
                    tcp::resolver::iterator _iter = _resolver.resolve(_query);
                    tcp::endpoint _endpoint = _iter->endpoint();
                    _socket->connect(_endpoint);
                }
                catch (...)
                {
                    _is_socket_avaiable = false;
                    sprintf(s_last_error_code, "could connect to async server %s:%s", ASYNC_SERVER_ADDRESS, ASYNC_SERVER_PORT);
                }

                if (!_is_socket_avaiable)
                {
                    if (_socket)
                    {
                        delete(_socket);
                        _socket = nullptr;
                    }
                    return 1;
                }

                return 0;
            }

            static size_t avaiable_tcp_bytes()
            {
                asio::socket_base::bytes_readable _socket_readabale_bytes(true);
                size_t _avaiable_bytes = 0;
                int _time_out = 2000;
                while (!_avaiable_bytes && _time_out > 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    _socket->io_control(_socket_readabale_bytes);
                    _avaiable_bytes = _socket_readabale_bytes.get();
                    _time_out--;
                }
                return _avaiable_bytes;
            }

            //read async
            template<typename PLAYPOD_CALLBACK>
            static void read_async_tcp(const size_t pSizeInBytes, const PLAYPOD_CALLBACK& pCallBack)
            {
                if (!_socket) return;

                //reset last error code
                std::memset(s_last_error_code, '\0', MAX_MESSAGE_SIZE);

                auto _rcv_buffer = (char*)malloc(pSizeInBytes);
                _socket->async_read_some(asio::buffer(_rcv_buffer, pSizeInBytes),
                                         [_rcv_buffer, &pCallBack](asio::error_code pError, std::size_t pLength)
                                         {
                                             if (pError)
                                             {
                                                 sprintf(s_last_error_code,
                                                         "error on receiving data from socket. error code: %d, error message: %s\n",
                                                         pError.value(), pError.message().c_str());
                                                 return;
                                             }

                                             std::string _json_str;
                                             _json_str.resize(pLength);
                                             memcpy(&_json_str[0], &_rcv_buffer[0], pLength);
                                             if (!_json_str.empty())
                                             {
                                                 JSONObject _json;
                                                 //create json from string
                                                 if (_json.from_string(_json_str))
                                                 {
                                                     sprintf(s_last_error_code,
                                                             "error on parsing json.");
                                                 }
                                                 else
                                                 {
                                                     //call callback
                                                     pCallBack(_json);
                                                 }

                                                 //clear resources
                                                 _json_str.clear();
                                                 _json.release();
                                             }
                                             free(_rcv_buffer);
                                         });
            }

            //send async with tcp
            template<typename PLAYPOD_CALLBACK>
            static void send_async_tcp(
                    const char* pMessage,
                    size_t pLenght,
                    const PLAYPOD_CALLBACK& pCallBack)
            {
                if (!_socket) return;

                //reset last error code
                std::memset(s_last_error_code, '\0', MAX_MESSAGE_SIZE);

                int _len = static_cast<int>(pLenght);
                //convert c++ int to java int structure
                char _msg_size[4];
                _msg_size[3] = (char)_len & 0xFF;
                _msg_size[2] = (char)((_len >> 8) & 0xFF);
                _msg_size[1] = (char)((_len >> 16) & 0xFF);
                _msg_size[0] = (char)((_len >> 24) & 0xFF);
                //write message lenght
                _socket->write_some(asio::buffer(_msg_size));

                _socket->async_write_some(
                        asio::buffer(pMessage, pLenght),
                        [&pCallBack](asio::error_code pError, std::size_t pLength)
                        {
                            if (pError)
                            {
                                sprintf(s_last_error_code,
                                        "error on writing data to socket. error code: %d, error message: %s\n",
                                        pError.value(), pError.message().c_str());
                                return;
                            }

                            char _lenght_buffer[4];
                            auto _bytes = avaiable_tcp_bytes();
                            if (_bytes)
                            {
                                //read lenght
                                auto _len = _socket->read_some(asio::buffer(_lenght_buffer, 4), pError);
                                if ((_len != 4) || pError)
                                {
                                    sprintf(s_last_error_code,
                                            "error on reading lenght of data. error code: %d, error message: %s\n",
                                            pError.value(), pError.message().c_str());
                                }
                                else
                                {
                                    auto _msg_len = to_int(
                                            _lenght_buffer[0],
                                            _lenght_buffer[1],
                                            _lenght_buffer[2],
                                            _lenght_buffer[3]);

                                    //read message
                                    _bytes = avaiable_tcp_bytes();
                                    if (_bytes == _msg_len)
                                    {
                                        read_async_tcp(_bytes, pCallBack);
                                    }
                                    else
                                    {
                                        sprintf(s_last_error_code,
                                                "lenght of message is not equal to lenght of read bytes");
                                    }
                                }
                            }
                            else
                            {
                                sprintf(s_last_error_code,
                                        "read time out");
                            }
                        });
            }

            //send async
            template<typename PLAYPOD_CALLBACK>
            static void send_async(
                    const char* pMessage,
                    size_t pLenght,
                    const PLAYPOD_CALLBACK & pCallBack)
            {
                if (config::harfs)
                {
                    //reset last error code
                    std::memset(s_last_error_code, '\0', MAX_MESSAGE_SIZE);

                    //send using http rest post
                    std::string _result;

                    const std::string _post_url = (std::string(ASYNC_SERVER_ADDRESS) + "/srv/");
                    const std::string _msg = "data=" + std::string(pMessage) + std::string("&peerId=") + std::to_string(Network::_peer_id);
                    auto _abort_nums = w_point{ 100, 10 };

                    W_RESULT _hr;
                    {
                        std::lock_guard<std::mutex> lock(_mutex1);
                        _hr = _url->send_rest_post(
                                _post_url,
                                _msg,
                                _msg.size(),
                                _result,
                                _abort_nums);


                    }

                    if (_hr == W_PASSED && !_result.empty())
                    {
                        JSONObject _json;
                        //create json from string
                        if (_json.from_string(_result))
                        {
                            sprintf(s_last_error_code,
                                    "error on parsing json.");
                        }
                        else
                        {
                            //call callback
                            pCallBack(_json);
                        }

                        //clear resources
                        _json.release();
                    }
                    else
                    {
                        sprintf(s_last_error_code,
                                "request %s with following params %s failed", _post_url.c_str(), _msg.c_str());
                    }
                }
                else
                {
                    if (config::utc)
                    {
                        //send data using native tcp
                        send_async_tcp(pMessage, pLenght, pCallBack);
                    }
                    else
                    {
                        //send data using web socket
                    }
                }
            }

            static W_RESULT request_url(const char* pURL, std::string & pResult)
            {
                auto _abort_nums = w_point{ 100, 10 };
                return _url ? _url->request_url(pURL, pResult, _abort_nums) : W_FAILED;
            }

            static void ping()
            {
                if (!is_ready()) return;

                send_async("{}", 2, [](JSONObject & pJson) {});
            }

            static void destroy_url()
            {
                SAFE_RELEASE(_url);
            }

            static void destroy_tcp()
            {
                if (_socket)
                {
                    _socket->close();
                    //_socket->release();
                }
            }

            static W_RESULT release()
            {
                wolf::logger.error("Release Network");
                if (_is_released) return W_PASSED;

                destroy_url();
                destroy_tcp();

                return W_PASSED;
            }

            static bool is_ready()
            {
                return _is_ready;
            }


            static std::string	_image;
            static int			_customer_id;
            static std::string	_name;
            static int			_user_id;
            static std::string	_token;
            static std::string	_profile_image;
            static uint64_t		_peer_id;
            static JSONObject  _user_data;

        private:
            static bool										_is_released;
            static std::thread* _thread;
            static wolf::system::w_url* _url;
            static asio::ip::tcp::socket* _socket;
            static bool										_is_ready;
        };

        static void initialize_sdk()
        {
            Network net1;
            asio::io_service ios;
            std::thread t{ [&] { ios.run(); } };
            net1.initialize_device_register(ios);
            net1.initialize_tcp_socket(ios);
            t.join();

        }

        struct Services
        {
        public:
            static W_RESULT initialize(asio::io_service& pIO)
            {
                W_RESULT _result = W_PASSED;
                //std::call_once(s_once_init, [&]()
                //{
                _result = Network::initialize_device_register(pIO);
                //});
                return _result;
            }
            static W_RESULT release()
            {
                return Network::release();
            }

            static std::string get_param_str(
                    _In_z_ const char* pKey,
                    _In_ const char* pValue)
            {
                const auto _type = static_cast<char*>(malloc(1024));
                sprintf(_type, R"({\\\"name\\\" : \\\"%s\\\", \\\"value\\\" : %s})", pKey, pValue);
                const auto _ret = std::string(_type);
                free(_type);
                return _ret;
            }

            static std::string cast_vector_to_json_array(
                    _In_	const std::vector<int>& pVec)
            {
                std::string _ret = "[ ";

                for (int i = 0; i < pVec.size(); i++)
                    _ret += "\"" + std::to_string(pVec[i]) + "\"" + (i == int(pVec.size()) - 1 ? "" : ",") + " ";

                _ret += "]";

                return _ret;
            }

            static void add_object_to_params(
                    _In_z_	const char* pKey,
                    _In_	const char* pValue,
                    _In_z_	std::string & pParameters,
                    _In_	bool& pHasPrev)
            {
                if (pHasPrev)
                    pParameters += ",";

                pParameters += get_param_str(pKey, pValue);

                pHasPrev = true;
            }

            static bool is_string_ip_number(_In_z_	std::string pStr)
            {
                if (pStr.size() > 4 || pStr.empty())
                    return false;
                if (pStr.size() > 1 && pStr[0] == '0')
                    return false;

                auto _num = 0, _mul = 1;

                while (!pStr.empty())
                {
                    const auto _c = pStr.back();

                    _num += _mul * int(_c - '0');
                    _mul *= 10;
                    pStr.pop_back();

                }
                std::cout << _num;
                return (_num < 256 && _num >= 0);
            }

            static bool is_string_format_ip(_In_z_	const std::string & pStr)
            {
                auto _cnt = 0;
                std::string _last;

                for (auto _cur : pStr)
                {
                    if (_cur < '0' || _cur > '9')
                    {
                        if (_cur != '.')
                            return false;

                        if (!is_string_ip_number(_last))
                            return false;

                        _last.clear();
                        _cnt++;
                        continue;
                    }
                    _last.push_back(_cur);
                }

                if (!is_string_ip_number(_last))
                    return false;
                if (_cnt != 3)
                    return false;

                return true;
            }

            static std::vector<int> get_version_from_string(_In_z_	const std::string & pStr)
            {
                auto _cnt = 0;
                std::string _last;

                auto _ret = std::vector<int>();

                for (auto _cur : pStr)
                {
                    if (_cur < '0' || _cur > '9')
                    {
                        if (_cur != '.')
                            continue;

                        int _cur;
                        sscanf(_last.c_str(), "%d", &_cur);
                        _ret.push_back(_cur);

                        _last.clear();

                        continue;
                    }
                    _last.push_back(_cur);
                }

                if (!_last.empty())
                {
                    int _cur;
                    sscanf(_last.c_str(), "%d", &_cur);
                    _ret.push_back(_cur);
                }

                return _ret;
            }



            template<typename PLAYPOD_CALLBACK>
            static void ping(const PLAYPOD_CALLBACK & pCallBack)
            {
                std::string _parameters = "[]";

                async_request(URL_PING, _parameters.c_str(), pCallBack);
            }

            //! Get information of games
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pLobbyId a id of lobby
            \param  pOffset
            \param  pSize
            \param  pName The name of the game you want to get information about
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, name, description, creator, physicalUrl, timelineId, packageName, mobileVersion, ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_games_info(const PLAYPOD_CALLBACK & pCallBack, const int& pInfrustructure, const int& pGameId, const int& pLobbyId, const int& pOffset = -1, const int& pSize = -1, const std::string pName = "")
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("infrustructure", std::to_string(pInfrustructure).c_str(), _parameters, _has_prev);
                if (pGameId >= 0)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                if (pLobbyId >= 0)
                    add_object_to_params("lobbyId", std::to_string(pLobbyId).c_str(), _parameters, _has_prev);

                if (pSize >= 0)
                    add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                if (pOffset >= 0)
                    add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);
                std::string _name_str = "\\\\\\\"";
                if (pName.size() > 0)
                    _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("query", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GAME_INFO, _parameters.c_str(), pCallBack);
            }

            //! Get information of top games
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pOffset
            \param  pSize
            \param  pType:1=Top GameCenter, 2=Top games, 4=Top Followers, 8=Game Center offer
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, name, description, creator, physicalUrl, timelineId, packageName, mobileVersion, ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_top_games_info(const PLAYPOD_CALLBACK & pCallBack, const int& pType = -1, const int& pOffset = -1, const int& pSize = -1)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                if (pType >= 0)
                    add_object_to_params("type", std::to_string(pType).c_str(), _parameters, _has_prev);

                if (pSize >= 0)
                    add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                if (pOffset >= 0)
                    add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_TOP_GAME, _parameters.c_str(), pCallBack);
            }

            //! Get game lobby
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, name, id, ,image
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_lobby(const PLAYPOD_CALLBACK & pCallBack)
            {
                //char* _parameters = (char*)malloc(1024);
                //if (!_parameters) return;

                //sprintf(_parameters, "[]");

                async_request(URL_GET_LOBBIES, "[]", pCallBack);
                //free(_parameters);
            }

            //! Get the live list
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, hasNext, nextoffset
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_lives(const PLAYPOD_CALLBACK & pCallBack)
            {

                async_request(URL_GET_LIVE, "[]", pCallBack);

            }
            //! Get  information of user
            /*!
            \param _image
            \param _name name of user
            \param  _profile_image image of profile
            \param _token
            \param _customer_id
            \param _user_id
            */

          static void init_login(const std::string _image,const std::string _name,const std::string _profile_image,const std::string _token ,const int&_customer_id,const int&_user_id)
            {

                Network::_image = _image;
                Network::_customer_id=_customer_id;
                Network::_name=_name;
                Network::_user_id=_user_id;
                Network::_profile_image=_profile_image;
                Network::_token = _token;

                using namespace rapidjson;
                StringBuffer _string_buffer;
                Writer<StringBuffer> _writer(_string_buffer);

                _writer.StartObject();
                {
                    _writer.Key("_image");
                    _writer.String(Network::_image.c_str());
                    _writer.Key("_name");
                    _writer.String(Network::_name.c_str());
                    _writer.Key(" _profile_image");
                    _writer.String(Network::_profile_image.c_str());
                    _writer.Key("_token");
                    _writer.String(Network::_token.c_str());
                    _writer.Key("_customer_id");
                    _writer.Uint(Network::_customer_id);
                    _writer.Key("_user_id");
                    _writer.Uint(Network::_user_id);
                }
                _writer.EndObject();

                //output json
                auto _size = _string_buffer.GetSize();
                auto _str = _string_buffer.GetString();
                auto _buffer = new char[_size];
                memcpy(&_buffer[0], &_str[0], _size);
                std::string temp(_buffer);
                Network::_user_data.from_string(temp);
            }

            //! Get user data
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \returns a jsonobject in  pCallBack that contains: name, customer_id,user_id,token,image, profile_image
            */
            template<typename PLAYPOD_CALLBACK>
            static void get_user_data(const PLAYPOD_CALLBACK & pCallBack)
            {
                pCallBack(Network::_user_data);

            }

            //! Get lobbies games
            /*!
            \tparam  PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pLobbyIds a id of lobby
            \param offset
            \param size
            \param pLobbyIdsSize
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, playerNumbersType, availableCount,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_lobbies_games(const PLAYPOD_CALLBACK & pCallBack, const int* pLobbyIds, const int& pLobbyIdsSize, const int& pOffset = -1, const int& pSize = -1)
            {
                if (pLobbyIdsSize <= 0 || pLobbyIds == nullptr)
                    return;

                std::string _parameters = "[";

                auto _has_prev = false;

                if (pOffset >= 0)
                    add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pSize >= 0)
                    add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                for (auto i = 0; i < pLobbyIdsSize; i++)
                {
                    std::string _lobby_id_string = "\\\\\\\"" + std::to_string(pLobbyIds[i]) + "\\\\\\\"";
                    add_object_to_params("lobbyIds", _lobby_id_string.c_str(), _parameters, _has_prev);
                }

                _parameters += "]";

                async_request(URL_GET_LOBBY_GAMES, _parameters.c_str(), pCallBack);
            }

            //! Get information of related games
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pOffset
            \param  pSize
            \param  pType:1=Games in a lobby, 2=Games that make one
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, name, description, creator, physicalUrl, timelineId, packageName, mobileVersion, ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_related_games_info(const PLAYPOD_CALLBACK & pCallBack, const int pType = -1, const int pGameId = -1, const int pOffset = 0, const int& pSize = 50)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pType >= 0)
                    add_object_to_params("type", std::to_string(pType).c_str(), _parameters, _has_prev);

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_RELATED_GAME, _parameters.c_str(), pCallBack);
            }

            //! Get top players in game center or league
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pOffset
            \param  pSize
            \returns a jsonobject in  pCallBack that contains:  hasError, errorMessage, errorcode,score ,id,name
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_top_players(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId = -1, const int& pOffset = 0, const int& pSize = 50)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pGameId > 0)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);


                _parameters += "]";

                async_request(URL_GET_TOP_PLAYERS, _parameters.c_str(), pCallBack);
            }

            //! Get a gallery of game
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pBusinessId
            \returns a jsonobject in  pCallBack that contains:  hasError, errorMessage, errorcode,imageUrl ,title,description
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_gallery(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const int& pBusinessId)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("productId", std::to_string(pGameId).c_str(), _parameters, _has_prev);
                add_object_to_params("businessId", std::to_string(pBusinessId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_GALLERY, _parameters.c_str(), pCallBack);
            }

            //! stream match id request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pClientType=1:WEB, 2:ANDROID, 3:PC
            \param  pLeagueId
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, matchid, ip, io,..
            */

            template<typename PLAYPOD_CALLBACK>
            static void stream_match_id_request(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const int& pClientType, const int& pLeagueId)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("clientType", std::to_string(3).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                auto _peer_id_str = std::to_string(Network::_peer_id);
                add_object_to_params("peerIds", _peer_id_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_REQUEST_STREAM_MATCH_ID, _parameters.c_str(), pCallBack);
            }

            //! Join a Default Game League
            /*!
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void subscribe_default_league_request(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_DEFAULT_LEAGUE_SUBSCRIBE, _parameters.c_str(), pCallBack);
            }

            //! Follow the game request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pBusinessId a id of business
            \param  pPostId a id of post
            \param  pFollow a state of follow
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void follow_game_request(const PLAYPOD_CALLBACK & pCallBack, const int& pBusinessId, const int& pPostId, const bool& pFollow)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("businessId", std::to_string(pBusinessId).c_str(), _parameters, _has_prev);
                add_object_to_params("postId", std::to_string(pPostId).c_str(), _parameters, _has_prev);

                std::string _unfollow_str = (pFollow) ? "false" : "true";
                add_object_to_params("disfavorite", _unfollow_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_FOLLOW_GAME, _parameters.c_str(), pCallBack);
            }

            //! Send game rate request
            /*!
            \param pCallBack a  CallBack to a function
            \param pGameId a id of game
            \param pRate a user rating
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,myrate,rate,ratecount
            */

            template<typename PLAYPOD_CALLBACK>
            static void send_game_rate_request(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const double& pRate)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("entityId", std::to_string(pGameId).c_str(), _parameters, _has_prev);
                add_object_to_params("rate", std::to_string(pRate).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GAME_RATE, _parameters.c_str(), pCallBack);
            }

            //! Get game following
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param size
            \param offset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,id,name,description,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_game_following(const PLAYPOD_CALLBACK & pCallBack, const int& pOffset = 0, const int& pSize = 50)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                if (pSize > 0)
                    add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                if (pOffset > 0)
                    add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_GAME_FOLLOWING, _parameters.c_str(), pCallBack);
            }


            template<typename PLAYPOD_CALLBACK>
            static void get_news(const PLAYPOD_CALLBACK & pCallBack, const int& pOffset = -1, const int& pSize = -1)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("businessId", std::to_string(config::business_id).c_str(), _parameters, _has_prev);

                if (pSize > 0)
                    add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                if (pOffset > 0)
                    add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_NEWS, _parameters.c_str(), pCallBack);
            }

            //tested
            //!Get user profile information
            /*!
            \param pCallBack a  CallBack to a function
            \param pUserId :If this field is not filled, the user 's own information will be returned
            \param  pRefetch: Get updated information
            \returns a jsonobject in  pCallBack that contains:  hasError, errorMessage, errorcode, name, description, creator, physicalUrl, timelineId, packageName, mobileVersion, ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_profile(const PLAYPOD_CALLBACK & pCallBack, const int& pUserId = -1, const int& pRefetch = -1)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                if (pUserId != -1)
                    add_object_to_params("userId", std::to_string(pUserId).c_str(), _parameters, _has_prev);

                if (pRefetch != -1)
                    add_object_to_params("refetch", std::to_string(pRefetch).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_USER_PROFILE, _parameters.c_str(), pCallBack);

            }

            //tested
            //!Get information of  online users
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pGameId a id of game
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, onlinePlayersCount,playersCount,score
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_online_info(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_ONLINE_INFO, _parameters.c_str(), pCallBack);

            }


            template<typename PLAYPOD_CALLBACK>
            static void get_file_info(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId)
            {
                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_FILE_INFO, _parameters.c_str(), pCallBack);

            }


            struct reject_message_map
            {
                std::string user_not_accept;
                std::string app_not_installed;
                std::string user_version_conflict;
                std::string user_is_busy;
                reject_message_map() :
                        user_not_accept(""), app_not_installed(""), user_version_conflict(""), user_is_busy("") {}
            };

            static std::string get_reject_msg(const int& type, const reject_message_map & rmm)
            {
                switch (type)
                {
                    case 3:
                        return rmm.user_not_accept;
                    case 4:
                        return rmm.app_not_installed;
                    case 5:
                        return rmm.user_version_conflict;
                    case 6:
                        return rmm.user_is_busy;
                    default:
                        return "";
                }

            }

            //! Match_request_response
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pRequestId a id of request
            \param pRejectReasonType
            \param pRejectMessage a Reason for rejecting request if the request is negative
            \param pRejectMessageMap
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, birthdate
            */

            template<typename PLAYPOD_CALLBACK>
            static void match_request_response(
                    const PLAYPOD_CALLBACK & pCallBack,
                    const int& pRequestId,
                    const int& pRejectReasonType = -1,
                    const std::string & pRejectMessage = "",
                    const reject_message_map & pRejectMessageMap = reject_message_map())
            {
                bool state = true;

                std::string _parameters = "[";

                auto _has_prev = false;

                add_object_to_params("requestId", std::to_string(pRequestId).c_str(), _parameters, _has_prev);

                std::string _peer_id = std::to_string(Network::_peer_id);

                add_object_to_params("sessionId", _peer_id.c_str(), _parameters, _has_prev);
                std::string _reject_message;
                if (pRejectReasonType != -1)
                {
                    state = false;

                    add_object_to_params("rejectReasonType", std::to_string(pRejectReasonType).c_str(), _parameters, _has_prev);
                    _reject_message = "\\\\\\\"";
                    _reject_message += pRejectMessage.size() > 0 ? pRejectMessage : get_reject_msg(pRejectReasonType, pRejectMessageMap);
                    _reject_message += "\\\\\\\"";
                    add_object_to_params("rejectMessage", _reject_message.c_str(), _parameters, _has_prev);

                }

                add_object_to_params("result", (state ? "true" : "false"), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_MATCH_REQUEST_RESPONSE, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get user achievements
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pGameId a id of game
            \param pUserId
            \param pType
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, count , name , rank , imgUrl
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_achievements(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId = -1, const int& pType = -1, const int& pUserId = -1)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                if (pGameId != -1)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);
                if (pType != -1)
                    add_object_to_params("type", std::to_string(pType).c_str(), _parameters, _has_prev);
                if (pUserId != -1)
                    add_object_to_params("userId", std::to_string(pUserId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_USER_ACHIEVEMENTS, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get user achievement detail
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pGameId a id of game
            \param size
            \param offset
            \param pRanktype
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, expireTimestamp , fromDateTimestamp,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_achievement_detail(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId = -1, const int& pSize = 50, const int& pOffset = 0, const int& pRanktype = -1)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pGameId != -1)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                if (pRanktype != -1)
                    add_object_to_params("rankType", std::to_string(pRanktype).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_USER_ACHIEVEMENT_DETAIL, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get user game points
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pGameId a id of game
            \param size
            \param offset
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, amount ,creationDate,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_game_points(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId = -1, const int& pSize = 50, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pGameId != -1)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_USER_GAME_POINTS, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get comment list
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pPostId a id of game
            \param size
            \param offset
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, id,text,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_comment_list(const PLAYPOD_CALLBACK & pCallBack, const int& pPostId, const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("postId", std::to_string(pPostId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_COMMENT_LIST, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Add game comment request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pPostId
            \param  pText
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, id
            */

            template<typename PLAYPOD_CALLBACK>
            static void add_game_comment_request(const PLAYPOD_CALLBACK & pCallBack, const int& pPostId, const std::string & pText)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("PostId", std::to_string(pPostId).c_str(), _parameters, _has_prev);

                std::string _text_str = "\\\\\\\"";
                _text_str += pText;
                _text_str += "\\\\\\\"";
                add_object_to_params("comment", _text_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                //_parameters = "[{\\\"name\\\":\\\"postId\\\",\\\"value\\\":\\\"4701\\\"},{\\\"name\\\":\\\"comment\\\",\\\"value\\\":\\\"hey\\\\n\\\"}]";

                async_request(URL_ADD_GAME_COMMENT, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get received friendship request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pStatus=1:posted  ,2:blocked , 4:failed , 8:accepted
            \param pSize
            \param pOffset
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode,  creationDate, requestid ,status,..
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_received_friendship_request(const PLAYPOD_CALLBACK & pCallBack, const int& pStatus = -1, const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pStatus != -1)
                    add_object_to_params("status", std::to_string(pStatus).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_RECEIVED_FRIENDSHIP_REQUEST, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get sent friendship request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pStatus=1:posted  ,2:blocked , 4:failed , 8:accepted
            \param pSize
            \param pOffset
            \param pUserId
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode,  creationDate, requestid ,status,..
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_sent_friendship_request(const PLAYPOD_CALLBACK & pCallBack, const int& pStatus = -1, const int& pSize = 20, const int& pOffset = 0, const int& pUserId = -1)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pStatus != -1)
                    add_object_to_params("status", std::to_string(pStatus).c_str(), _parameters, _has_prev);

                if (pUserId != -1)
                    add_object_to_params("userId", std::to_string(pUserId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_SENT_FRIENDSHIP_REQUEST, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Friendship request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pToUserId
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode,  creationDate, requestid ,status,..
            */

            template<typename PLAYPOD_CALLBACK>
            static void friendship_request(const PLAYPOD_CALLBACK & pCallBack, const int& pToUserId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("toUserId", std::to_string(pToUserId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_FRIENDSHIP_REQUEST, _parameters.c_str(), pCallBack);
            }

            //! Reply friendship request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pRequestId
            \PARAM pReply
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode,  creationDate, requestid ,status,..
            */

            template<typename PLAYPOD_CALLBACK>
            static void reply_friendship_request(const PLAYPOD_CALLBACK & pCallBack, const int& pRequestId, const int& pReply)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("requestId", std::to_string(pRequestId).c_str(), _parameters, _has_prev);

                add_object_to_params("reply", std::to_string(pReply).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_REPLY_FRIENDSHIP_REQUEST, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Cancel friendship request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pRequestId
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void cancel_friendship_request(const PLAYPOD_CALLBACK & pCallBack, const int& pRequestId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("requestId", std::to_string(pRequestId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_CANCEL_FRIENDSHIP_REQUEST, _parameters.c_str(), pCallBack);

            }

            //tested
            //! Get user friends
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pName
            \param pSize
            \param pOffset
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode , friendshipDate , id , status ,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_friends(const PLAYPOD_CALLBACK & pCallBack, const std::string  pName = "", const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pName.size() > 0)
                    _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("name", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";


                async_request(URL_USER_FRIENDS, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Remove friend
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pId
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode , state
            */

            template<typename PLAYPOD_CALLBACK>
            static void remove_friend(const PLAYPOD_CALLBACK & pCallBack, const int& pId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("id", std::to_string(pId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_REMOVE_FRIEND_REQUEST, _parameters.c_str(), pCallBack);
            }

            //tested
            //!Get online users in a league
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId an id of game
            \param  pLeagueId an id of league
            \param  pSize number of online user
            \param  pOffset
            \param  pFilter a username
            \returns a jsonobject in  pCallBack that contains:  hasError, errorMessage, errorcode, id , name ,score
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_online_user(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const int& pLeagueId, const int& pSize = 10, const int& pOffset = 0, const std::string & pFilter = "")
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                add_object_to_params("index", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                add_object_to_params("count", std::to_string(pSize).c_str(), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pFilter.size() > 0)
                    _name_str += pFilter;
                _name_str += "\\\\\\\"";
                add_object_to_params("filter", _name_str.c_str(), _parameters, _has_prev);
                _parameters += "]";

                async_request(URL_ONLINE_USER, _parameters.c_str(), pCallBack);
            }

            //tested
            //!Get top score
            /*!
            \param pCallBack a  CallBack to a function
            \param  pGameId an id of game
            \param  pLeagueId an id of league
            \param  pSize number of online user
            \param  pOffset
            \param  pFilter a username
            \returns a jsonobject in  pCallBack that contains:  hasError, errorMessage, errorcode, id , name
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_top_score(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const int& pLeagueId = -1, const int& pIsGlobal = -1)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                if (pLeagueId != -1)
                    add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                if (pIsGlobal != -1)
                    add_object_to_params("isGlobal", (pIsGlobal ? "true" : "false"), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_TOP_SCORE, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get information of latest games
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pOffset
            \param  pSize
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, name, description, creator, physicalUrl, timelineId, packageName, mobileVersion, ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_latest_games_info(const PLAYPOD_CALLBACK & pCallBack, const int& pSize = 30, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_LATEST_GAME, _parameters.c_str(), pCallBack);
            }

            // tested
            //!  Search among Game Center users
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pName a alias
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, name, id, hasnext,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void search_user_request(const PLAYPOD_CALLBACK & pCallBack, const std::string & pName, const int& pSize = 5, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;
                std::string _name_str = "\\\\\\\"";
                _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("query", _name_str.c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";


                async_request(URL_SEARCH_USER, _parameters.c_str(), pCallBack);
            }

            //tested
            template<typename PLAYPOD_CALLBACK>
            static void change_visibility_request(const PLAYPOD_CALLBACK & pCallBack) {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("peerId", std::to_string(Network::_peer_id).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_INVISIBLE, _parameters.c_str(), pCallBack);
            }

            //! Follow the post request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pPostId a id of post
            \param  pState a state of follow
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void follow_post_request(const PLAYPOD_CALLBACK & pCallBack, const int& pPostId, const bool& pState = true)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("postId", std::to_string(pPostId).c_str(), _parameters, _has_prev);

                add_object_to_params("disfavorite", (!pState ? "true" : "false"), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_FOLLOW_POST, _parameters.c_str(), pCallBack);
            }

            //!  like post request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pPostId a id of post
            \param  pState a state of follow
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void like_post_request(const PLAYPOD_CALLBACK & pCallBack, const int& pPostId, const bool& pState = true)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("postId", std::to_string(pPostId).c_str(), _parameters, _has_prev);

                add_object_to_params("dislike", (!pState ? "true" : "false"), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LIKE_POST, _parameters.c_str(), pCallBack);
            }

            //!match request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId an id of game
            \param  pLeagueId an id of league
            \param  pOpponentId an id of Opponent
            \param  pVersion a version of game
            \param  pIsOffline
            \param pRequestTime a time of request for offline request
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode ,Request id
            */

            template<typename PLAYPOD_CALLBACK>
            static void match_request(
                    const PLAYPOD_CALLBACK & pCallBack,
                    const int& pGameId,
                    const int& pLeagueId,
                    const int& pOpponentId,
                    const std::string & pVersionconst= ""
                    //bool& pIsOffline = false,
                    /*const int& pRequestTime = -1*/)
            {

                std::string _parameters = "[", _request_url;

                bool _has_prev = false;

               add_object_to_params("opponentUserId", std::to_string(pOpponentId).c_str(), _parameters, _has_prev);

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                /*if (pIsOffline)
                {
                    _request_url = URL_OFFLINE_MATCH_REQUEST;

                    if (pRequestTime >= 0)
                        add_object_to_params("timestamp", std::to_string(pRequestTime).c_str(), _parameters, _has_prev);
                }
                else
                {*/
                _request_url = URL_REQUEST_MATCH;

                add_object_to_params("id", "0", _parameters, _has_prev);

                add_object_to_params("sessionId", std::to_string(Network::_peer_id).c_str(), _parameters, _has_prev);

                std::string _name_str= "\\\\\\\"";
                _name_str+=pVersionconst;
                _name_str+="\\\\\\\"";

               add_object_to_params("version", _name_str.c_str(), _parameters, _has_prev);
                //}

                _parameters += "]";

                async_request(_request_url.c_str(), _parameters.c_str(), pCallBack);
            }

            //! cancel match request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pRequestId a id of request
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void cancel_match_request(const PLAYPOD_CALLBACK & pCallBack, const int& pRequestId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("requestId", std::to_string(pRequestId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_CANCEL_MATCH_REQUEST, _parameters.c_str(), pCallBack);

            }

            //tested
            //!  match id request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param pLeagueId a id of league
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, matchid
            */

            template<typename PLAYPOD_CALLBACK>
            static void match_id_request(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const int& pLeagueId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_REQUEST_MATCH_ID, _parameters.c_str(), pCallBack);

            }

            //! Get information of leagues
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pLeaguesId a id of leagues
            \param  pPrize a awards type of league
            \param  pOffset
            \param  pSize
            \param  pLobbyId a id of lobby
            \param  pStatus  a Type of league in terms of status
            \param  pStatusList a League status
            \param  pNewest a Get the latest leagues
            \param  pName a league name
            \param  pShowDefault Whether or not there is a default league
            \param  pFinancialType League type by membership fee
            \param   pUserState League type based on user status
            \returns a jsonobject in  pCallBack that contains:  hasError, errorMessage, errorcode, leagues, gametype, games, rate, maxPlayers,....
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_leagues_info(
                    const PLAYPOD_CALLBACK & pCallBack,
                    const int& pUserState,
                    const int& pFinancialType,
                    const int& pLeagueId,
                    //const bool pMine = false,
                    const bool pShowDefault = false,
                    const std::string pName = "",
                    const bool pNewest = false,
                    const std::vector<int> pStatusList = std::vector<int>(),
                    const int& pGameId = -1,
                    const int& pStatus = -1,
                    const int& pLobbyId = -1,
                    const int& pSize = 5,
                    const int& pOffset = 0,
                    const int& pPrize = 0,
                    const std::vector<int> & pLeaguesId = std::vector<int>())
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                if (pGameId >= 0)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                if (pLobbyId >= 0)
                    add_object_to_params("lobbyId", std::to_string(pLobbyId).c_str(), _parameters, _has_prev);

                std::string _leagues_id_str = "\\\\\\\"[";

                for (auto i = 0; i < pLeaguesId.size(); i++)
                {
                    _leagues_id_str += (i < pLeaguesId.size() - 1) ? std::to_string(pLeaguesId[i]) + "," : std::to_string(pLeaguesId[i]);

                }
                _leagues_id_str += "]\\\\\\\"";
                add_object_to_params("leaguesId", _leagues_id_str.c_str(), _parameters, _has_prev);


                std::string _name_str = "\\\\\\\"";
                if (pName.size() > 0)
                    _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("query", _name_str.c_str(), _parameters, _has_prev);

                if (pStatus != -1)
                    add_object_to_params("status", std::to_string(pStatus).c_str(), _parameters, _has_prev);

                if (pUserState >= 0)
                    add_object_to_params("mine", (pUserState == 1 ? "true" : "false"), _parameters, _has_prev);

                if (pFinancialType >= 0)
                    add_object_to_params("financialType", std::to_string(pFinancialType).c_str(), _parameters, _has_prev);


                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                add_object_to_params("prize", std::to_string(pPrize).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);


                //add_object_to_params("mine", (pMine) ? "true" : "false", _parameters, _has_prev);

                add_object_to_params("showDefault", (pShowDefault) ? "true" : "false", _parameters, _has_prev);

                add_object_to_params("newest", (pNewest) ? "true" : "false", _parameters, _has_prev);

                std::string _status_list_str = "\\\\\\\"[";

                for (auto i = 0; i < pStatusList.size(); i++)
                {
                    _status_list_str  += (i < pStatusList.size() - 1) ?   std::to_string(pStatusList[i]) + "," : std::to_string(pStatusList[i]);

                }
                _status_list_str += "]\\\\\\\"";
                add_object_to_params("statusList", _status_list_str.c_str(), _parameters, _has_prev);

                _parameters += "]";
printf("%s",_parameters);
                async_request(URL_GET_LEAGUE, _parameters.c_str(), pCallBack);

            }

            //tested
            //! Get information of  related leagues
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pOffset
            \param  pSize
            \param  pType a type of league
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, gametype, games, rate, maxPlayers,....
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_related_leagues_info(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId, const int& pType = -1, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string  _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                if (pType >= 0)
                    add_object_to_params("type", std::to_string(pType).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_RELATED_LEAGUE, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get the  information of  top leagues
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pOffset
            \param  pSize
            \param  pType a type of league:1=top gamecenter,8=Game Center offer
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, gametype, games, rate, maxPlayers,....
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_top_leagues_info(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId = -1, const int& pType = -1, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                if (pType >= 0)
                    add_object_to_params("type", std::to_string(pType).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pGameId >= 0)
                    add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_TOP_LEAGUE, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get the  information of  latest leagues
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pOffset
            \param  pSize
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, leagues, gametype,games,rate,maxPlayers,....
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_latest_leagues_info(const PLAYPOD_CALLBACK & pCallBack, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_LATEST_LEAGUE, _parameters.c_str(), pCallBack);

            }

            //tested
            //! Get league members
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pOffset
            \param  pSize
            \param  pName a name of user
            \param  pUserState= 0:All users, 1:online users, 2:offline
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode,name, isonline, name ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_members(
                    const PLAYPOD_CALLBACK & pCallBack,
                    const int& pLeagueId,
                    const int& pSize = 20,
                    const int& pOffset = 0,
                    const int& pUserState = -1,
                    const std::string pName = "")
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pUserState >= 0)
                    add_object_to_params("online", (pUserState == 1 ? "true" : "false"), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pName.size() > 0)
                    _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("filter", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";


                async_request(URL_LEAGUE_MEMBERS, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get information of table
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of League
            \param  pType:1=a month, 2=totally
            \returns a jsonobject in  pCallBack that contains:hasError, errorMessage, errorcode, type, headerData, usersData, rounds
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_table_data(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId, const int& pRangeType = -1)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                if (pRangeType >= 0)
                    add_object_to_params("rangeType", std::to_string(pRangeType).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_TABLE, _parameters.c_str(), pCallBack);
            }

            //tested
            //!  Request to be added to the opponent's list
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of League
            \param  pGameId a id of Game
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void quick_match_request(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId, const int& pGameId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("gameId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                add_object_to_params("peerId", std::to_string(Network::_peer_id).c_str(), _parameters, _has_prev);

                _parameters += "]";
                async_request(URL_REQUEST_QUICK_MATCH, _parameters.c_str(), pCallBack);
            }


            //tested
            //! Request removal from the opponent's list
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of League
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void cancel_quick_match_request(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                add_object_to_params("peerId", std::to_string(Network::_peer_id).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_CANCEL_QUICK_MATCH, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get the amount of league prize
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of League
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,  rank, textValue, value, description
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_awards(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LEAGUE_AWARDS, _parameters.c_str(), pCallBack);
            }

            //! Get game packs
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pGameId a id of game
            \param  pItemId only one of the pGameId or pItemId can be optional
            \param  pPackId a id of pack
            \param  pNameFilter a Filter by name
            \param pSize
            \param pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,  packs, hasNext, nextOffset
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_in_app_purchase_pack(const PLAYPOD_CALLBACK & pCallBack,
                                                 const int& pGameId = -1,
                                                 const int& pItemId = -1,
                                                 const int& pPackId = -1,
                                                 const std::string & pNameFilter = "",
                                                 const int& pSize = 10,
                                                 const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                if (pGameId == -1 && pItemId == -1)
                    return;

                if (pGameId >= 0)
                    add_object_to_params("entityId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pPackId >= 0)
                    add_object_to_params("packId", std::to_string(pPackId).c_str(), _parameters, _has_prev);

                if (pItemId >= 0)
                    add_object_to_params("itemId", std::to_string(pItemId).c_str(), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pNameFilter.size() > 0)
                    _name_str += pNameFilter;
                _name_str += "\\\\\\\"";
                add_object_to_params("query", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_IN_APP_PURCHASE_PACK, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get global in app purchase pack
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pItemId only one of the pGameId or pItemId can be optional
            \param pSize
            \param pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,  packs, hasNext, nextOffset
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_global_in_app_purchase_pack(const PLAYPOD_CALLBACK & pCallback, const int& pItemId, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("itemId", std::to_string(pItemId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_GLOBAL_IN_APP_PURCHASE_PACK, _parameters.c_str(), pCallback);
            }

            //tested
            //! Get a game items
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pItemId If this field is filled, the specified item will be returned, otherwise all items in the game will be returned.
            \param pSize
            \param pOffset
            \param pGameId a id of game
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,  id, name , hasNext, nextOffset,..
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_game_items(const PLAYPOD_CALLBACK & pCallback, const int& pGameId, const int& pItemId = -1, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("entityId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pItemId >= 0)
                    add_object_to_params("itemId", std::to_string(pItemId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_GAME_ITEMS, _parameters.c_str(), pCallback);
            }

            //! Get game center related items
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pItemId a id of item
            \param pSize
            \param pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,  id, name , hasNext, nextOffset,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_game_center_item(const PLAYPOD_CALLBACK & pCallback, const int& pItemId = -1, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pItemId >= 0)
                    add_object_to_params("itemId", std::to_string(pItemId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_USER_GC_ITEMS, _parameters.c_str(), pCallback);
            }

            //tested
            //! Get user items
            /*!
            \tparam PLAYPOD_CALLBACK
            \param pCallBack a  CallBack to a function
            \param pGameId a id of game
            \param pItemId a id of item
            \param pSize
            \param pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode,  id, count, item, hasNext, nextOffset
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_user_items(const PLAYPOD_CALLBACK & pCallBack, const int& pGameId, const int& pItemId = -1, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("entityId", std::to_string(pGameId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pItemId >= 0)
                    add_object_to_params("itemId", std::to_string(pItemId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_USER_ITEMS, _parameters.c_str(), pCallBack);
            }

            //tested
            //! consume item request
            /*!
            \tparam  PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pItemId a id of item
            \param  pCount a number of consumed
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename  PLAYPOD_CALLBACK>
            static void consume_item_request(const PLAYPOD_CALLBACK & pCallBack, const int& pItemId, const int& pCount)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("itemId", std::to_string(pItemId).c_str(), _parameters, _has_prev);

                add_object_to_params("count", std::to_string(pCount).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_CONSUME_ITEM, _parameters.c_str(), pCallBack);
            }

            //! Follow the league request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pBusinessId a id of business
            \param  pPostId a id of post
            \param  pState a state of follow
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename  PLAYPOD_CALLBACK>
            static void follow_league_request(const PLAYPOD_CALLBACK & pCallBack, const int& pBusinessId, const int& pPostId, const bool& pState = true)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("businessId", std::to_string(pBusinessId).c_str(), _parameters, _has_prev);

                add_object_to_params("postId", std::to_string(pPostId).c_str(), _parameters, _has_prev);

                add_object_to_params("disfavorite", (!pState ? "true" : "false"), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_FOLLOW_LEAGUE, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get league top players
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, score, id, name,...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_top_players(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId = -1, const int& pSize = 50, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                if (pLeagueId >= 0)
                    add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_LEAGUE_TOP_PLAYERS, _parameters.c_str(), pCallBack);
            }

            //tested
            template<typename PLAYPOD_CALLBACK>
            static void get_time_line(const PLAYPOD_CALLBACK & pCallBack, const int& pUserId = -1, const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pUserId >= 0)
                    add_object_to_params("userId", std::to_string(pUserId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_TIME_LINE, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get league following
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, league
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_following(const PLAYPOD_CALLBACK & pCallBack, const int& pSize = 10, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_LEAGUE_FOLLOWING, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get enrolled leagues
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pUserId: If this field is filled, the user leagues will be returned, otherwise the current user will
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, league
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_enrolled_leagues(const PLAYPOD_CALLBACK & pCallBack, const int& pUserId = -1, const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pUserId >= 0)
                    add_object_to_params("userId", std::to_string(pUserId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_ENROLLED_LEAGUES, _parameters.c_str(), pCallBack);
            }

            //TODO: test later
            template<typename PLAYPOD_CALLBACK>
            static void get_custom_post(const PLAYPOD_CALLBACK & pCallBack, const int& pBusinessId, const int pId = -1, const JSONObject * pJsonObject = nullptr)
            {
                std::string  _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("businessId", std::to_string(pBusinessId).c_str(), _parameters, _has_prev);


                if (pJsonObject != nullptr)
                {
                    add_object_to_params("keys", pJsonObject->get_all_keys().c_str(), _parameters, _has_prev);

                    add_object_to_params("values", pJsonObject->get_all_values().c_str(), _parameters, _has_prev);
                }

                if (pId >= 0)
                    add_object_to_params("id", std::to_string(pId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_CUSTOM_POST, _parameters.c_str(), pCallBack);

            }

            //tested
            //! Get enroll access
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pBusinessId
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_enroll_access(const PLAYPOD_CALLBACK & pCallBack, const int& pBusinessId)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("leagueId", std::to_string(pBusinessId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_LEAGUE_ENROLL_ACCESS, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Send league rate request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pRate a user rating
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, myrate, rate, ratecount
            */

            template<typename PLAYPOD_CALLBACK>
            static void send_league_rate_request(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId, const int& pRate)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("entityId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                add_object_to_params("rate", std::to_string(pRate).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LEAGUE_RATE, _parameters.c_str(), pCallBack);
            }

            //tested
            template<typename PLAYPOD_CALLBACK>
            static void get_credit_pack_list(const PLAYPOD_CALLBACK & pCallBack, const int& pSize = 20, const int& pOffset = 0, const int64_t & pFromAmount = -1, const std::string & pName = "")
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pFromAmount >= 0)
                    add_object_to_params("fromAmount", std::to_string(pFromAmount).c_str(), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pName.size() > 0)
                    _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("name", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_GET_CREDIT_PACK_LIST, _parameters.c_str(), pCallBack);
            }

            //tested
            //! Get league matches result
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pUserId
            \param  pMatchId
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, starttime, endtime, id ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_matches_result(
                    const PLAYPOD_CALLBACK & pCallBack,
                    const int& pLeagueId,
                    const int& pUserId = -1,
                    const int& pMatchId = -1,
                    const int& pSize = 20,
                    const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                if (pUserId >= 0)
                    add_object_to_params("userId", std::to_string(pUserId).c_str(), _parameters, _has_prev);

                if (pMatchId >= 0)
                    add_object_to_params("matchId", std::to_string(pMatchId).c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LEAGUE_MATCHES_RESULT, _parameters.c_str(), pCallBack);
            }

            //! Get league latest  matches result
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pUsername
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, starttime, endtime, id ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_latest_matches_result(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId, const std::string & pUsername = "", const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pUsername.size() > 0)
                    _name_str += pUsername;
                _name_str += "\\\\\\\"";
                add_object_to_params("username", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LEAGUE_LATEST_MATCHES_RESULT, _parameters.c_str(), pCallBack);
            }

            //! Get league latest  matches
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pName
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, starttime, endtime, id ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_latest_matches(
                    const PLAYPOD_CALLBACK & pCallBack,
                    const int& pLeagueId,
                    const std::string pName = "",
                    const int& pSize = 20,
                    const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                std::string _name_str = "\\\\\\\"";
                if (pName.size() > 0)
                    _name_str += pName;
                _name_str += "\\\\\\\"";
                add_object_to_params("query", _name_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LEAGUE_LATEST_MATCHES_RESULT, _parameters.c_str(), pCallBack);
            }

            //! Get league  matches
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLeagueId a id of league
            \param  pStatus
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, starttime, endtime, id ...
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_league_matches(const PLAYPOD_CALLBACK & pCallBack, const int& pLeagueId = -1, const std::string & pStatus = "", const int& pSize = 20, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                if (pLeagueId >= 0)
                    add_object_to_params("leagueId", std::to_string(pLeagueId).c_str(), _parameters, _has_prev);

                std::string _status_str = "\\\\\\\"";
                if (pStatus.size() > 0)
                    _status_str += pStatus;
                _status_str += "\\\\\\\"";
                add_object_to_params("status", _status_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_LEAGUE_MATCHES, _parameters.c_str(), pCallBack);
            }

            //! Add league comment request
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pId
            \param  pText
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, id
            */

            template<typename PLAYPOD_CALLBACK>
            static void add_league_comment_request(const PLAYPOD_CALLBACK & pCallBack, const int& pId, const std::string & pText)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                add_object_to_params("postId", std::to_string(pId).c_str(), _parameters, _has_prev);

                std::string _text_str = "\\\\\\\"";
                _text_str += pText;
                _text_str += "\\\\\\\"";
                add_object_to_params("comment", _text_str.c_str(), _parameters, _has_prev);

                _parameters += "]";

                async_request(URL_ADD_LEAGUE_COMMENT, _parameters.c_str(), pCallBack);
            }

            //tested

            template<typename PLAYPOD_CALLBACK>
            static void get_game_center_status(const PLAYPOD_CALLBACK & pCallBack)
            {
                async_request(URL_GAME_CENTER_STATUS, "[]", pCallBack);
            }

            //! Get lobbies leagues
            /*!
            \tparam PLAYPOD_CALLBACK
            \param  pCallBack a  CallBack to a function
            \param  pLobbyIds
            \param  pType
            \param  pSize
            \param  pOffset
            \returns a jsonobject in  pCallBack that contains: hasError, errorMessage, errorcode, id, gametype,....
            */

            template<typename PLAYPOD_CALLBACK>
            static void get_lobbies_leagues(const PLAYPOD_CALLBACK & pCallBack, const std::vector<int> & pLobbyIds, const int& pType = -1, const int& pSize = 5, const int& pOffset = 0)
            {
                std::string _parameters = "[";

                bool _has_prev = false;

                if (pType >= 0)
                    add_object_to_params("type", std::to_string(pType).c_str(), _parameters, _has_prev);

                add_object_to_params("size", std::to_string(pSize).c_str(), _parameters, _has_prev);

                add_object_to_params("offset", std::to_string(pOffset).c_str(), _parameters, _has_prev);

                for (auto i = 0; i < pLobbyIds.size(); i++)
                {
                    auto _lobby_id_string = "\\\\\\\"" + std::to_string(pLobbyIds[i]) + "\\\\\\\"";
                    add_object_to_params("lobbyIds", _lobby_id_string.c_str(), _parameters, _has_prev);
                }

                _parameters += "]";

                async_request(URL_GET_LOBBY_LEAGUES, _parameters.c_str(), pCallBack);
            }

            template<typename PLAYPOD_CALLBACK>
            static void async_request(
                    const char* pUrlData,
                    const char* pParamsData,
                    const PLAYPOD_CALLBACK & pCallBack)
            {
                //TODO: function returns string -> prepare string request.

                //auto _token_str = Network::_token.empty() ? "null" : Network::_token;
                auto _token_str = Network::_token.empty() ? "null" : Network::_token;
                //TODO: get time for client_meesage_id

#ifdef TEST_SERVER
                auto _gc_param_data = (char*)malloc(MAX_MESSAGE_SIZE);
				sprintf(_gc_param_data,
					"{\\\\\\\"remoteAddr\\\\\\\": null,"
					"\\\\\\\"clientMessageId\\\\\\\":\\\\\\\"%s\\\\\\\","
					"\\\\\\\"serverKey\\\\\\\": %d,"
					"\\\\\\\"oneTimeToken\\\\\\\": null,"
					"\\\\\\\"token\\\\\\\": \\\\\\\"%s\\\\\\\","
					"\\\\\\\"tokenIssuer\\\\\\\": %d,"
					"\\\\\\\"parameters\\\\\\\": %s,"
					"\\\\\\\"msgType\\\\\\\": %d,"
					"\\\\\\\"uri\\\\\\\": \\\\\\\"%s\\\\\\\","
					"\\\\\\\"messageId\\\\\\\": %d,"
					"\\\\\\\"expireTime\\\\\\\": %d}",
					"123e4567-e89b-12d3-b486-426655440000_GC_PC", 0, _token_str.c_str(), 0, pParamsData, 3, pUrlData, 1001, 0);

				auto _message_vo = (char*)malloc(MAX_MESSAGE_SIZE);
				sprintf(_message_vo,
					"{\\\"content\\\": \\\"%s\\\","
					"\\\"messageId\\\":%d,"
					"\\\"priority\\\": \\\"%s\\\","
					"\\\"peerName\\\": \\\"%s\\\","
					"\\\"ttl\\\": %d}",
					_gc_param_data, 1001, "1", config::ahrrn, 0);

				auto _async_data = (char*)malloc(MAX_MESSAGE_SIZE);
				sprintf(_async_data,
					"{\"content\": \"%s\","
					"\"trackerId\":%d,"
					"\"type\": %d}",
					_message_vo, 1001, 3);
#else
                auto _gc_param_data = (char*)malloc(MAX_MESSAGE_SIZE);
                sprintf(_gc_param_data,
                        "{\\\\\\\"remoteAddr\\\\\\\": null,"
                        "\\\\\\\"clientMessageId\\\\\\\":\\\\\\\"%s\\\\\\\","
                        "\\\\\\\"serverKey\\\\\\\": %d,"
                        "\\\\\\\"oneTimeToken\\\\\\\": null,"
                        "\\\\\\\"token\\\\\\\": \\\\\\\"%s\\\\\\\","
                        "\\\\\\\"tokenIssuer\\\\\\\": %d,"
                        "\\\\\\\"parameters\\\\\\\": %s,"
                        "\\\\\\\"msgType\\\\\\\": %d,"
                        "\\\\\\\"uri\\\\\\\": \\\\\\\"%s\\\\\\\","
                        "\\\\\\\"messageId\\\\\\\": %d,"
                        "\\\\\\\"expireTime\\\\\\\": %d}",
                        "123e4567-e89b-12d3-b486-426655440000_GC_PC", 0, _token_str.c_str(), 0, pParamsData, 3, pUrlData, 1001, 0);

                auto _message_vo = (char*)malloc(MAX_MESSAGE_SIZE);
                sprintf(_message_vo,
                        "{\\\"content\\\": \\\"%s\\\","
                        "\\\"priority\\\": \\\"%s\\\","
                        "\\\"peerName\\\": \\\"%s\\\","
                        "\\\"ttl\\\": %d}",
                        _gc_param_data, "1", config::ahrrn, 20000);

                auto _async_data = (char*)malloc(MAX_MESSAGE_SIZE);
                sprintf(_async_data,
                        "{\"content\": \"%s\","
                        "\"type\": %d}",
                        _message_vo, 3);
#endif

                Network::send_async(_async_data, strlen(_async_data), pCallBack);

                free(_gc_param_data);
                free(_message_vo);
                free(_async_data);
            }
        };


    }
}

#endif
