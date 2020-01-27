//
// Created by forogh on 22.01.20.
//
/*
	Project			 : Wolf Engine. Copyright(c) Pooya Eimandar (http://PooyaEimandar.com) . All rights reserved.
	Source			 : Please direct any bug to https://github.com/PooyaEimandar/Wolf.Engine/issues
	Website			 : http://WolfSource.io
	Name			 : pch.h
	Description		 : Pre-Compiled header
	Comment          : Read more information about this sample on http://wolfsource.io/gpunotes/wolfengine/
*/

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __PCH_H__
#define __PCH_H__

#include <wolf.h>
#include <w_task.h>
#include <w_thread.h>
#include<w_thread_pool.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>

typedef enum TEST_SDK_RESULT
{
    TSR_FAILED,
    TSR_PASSED,
    TSR_CONTENT_ERROR,
    TSR_PARSING_JSON_HAS_PROBLEM,
    TSR_CONTENT_NOT_AVAILABLE
};
#endif



