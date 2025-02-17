/*
 * Copyright (C) 2021 ByteDance Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <hilog/log.h>
#define RAPHAEL_DEBUG(fmt, ...) OH_LOG_Print(LOG_APP, LOG_DEBUG, 0xFF00, "RAPHAEL", fmt, ##__VA_ARGS__)
#define RAPHAEL_INFO(fmt, ...) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "RAPHAEL", fmt, ##__VA_ARGS__)
#define RAPHAEL_WARN(fmt, ...) OH_LOG_Print(LOG_APP, LOG_WARN, 0xFF00, "RAPHAEL", fmt, ##__VA_ARGS__)
#define RAPHAEL_ERROR(fmt, ...) OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "RAPHAEL", fmt, ##__VA_ARGS__)
#endif