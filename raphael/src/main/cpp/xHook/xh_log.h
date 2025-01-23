// Copyright (c) 2018-present, iQIYI, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Created by caikelun on 2018-04-11.

#ifndef XH_LOG_H
#define XH_LOG_H 1

#include "Logger.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XH_LOG_TAG "xhook"
#define XH_LOG_DEBUG(fmt, ...) OH_LOG_Print(LOG_APP, LOG_DEBUG, 0xFF00, "xHook", fmt, ##__VA_ARGS__)
#define XH_LOG_INFO(fmt, ...)  OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "xHook", fmt, ##__VA_ARGS__)
#define XH_LOG_WARN(fmt, ...)  OH_LOG_Print(LOG_APP, LOG_WARN, 0xFF00, "xHook", fmt, ##__VA_ARGS__)
#define XH_LOG_ERROR(fmt, ...) OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "xHook", fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
