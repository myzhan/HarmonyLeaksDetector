#include "napi/native_api.h"
#include "HookProxy.h"
#include "PltGotHookProxy.h"
#include "MemoryCache.h"
#include "Raphael.h"
#include "Logger.h"

// TODO: write to disk
static Cache *mCache;
static bool started = false;
static bool hooked = false;

static napi_value Start(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value args[3] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    int configs;
    status = napi_get_value_int32(env, args[0], &configs);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to get configs parameter");
        return NULL;
    }
    
    char space[256];
    size_t space_length;
    status = napi_get_value_string_utf8(env, args[1], space, sizeof(space), &space_length);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to get space parameter");
        return NULL;
    }
    
    char regex[256];
    size_t regex_length = 0;
    status = napi_get_value_string_utf8(env, args[2], regex, sizeof(regex), &regex_length);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to get regex parameter");
    } else {
        if (regcomp(&focused_regex, regex, REG_EXTENDED|REG_NOSUB) != 0) {
            napi_throw_error(env, NULL, "Invalid regex parameter");
            return NULL;
        }
    }
    
//     LOGGER("configs: %{public}d, space: %{public}s, regex: %{public}s", configs, space, regex);
    
    if (!started) {
        mCache = new MemoryCache(space);
        update_configs(mCache, 0);
        
        if (!hooked) {
            if (regex_length == 0) {
                registerInlineProxy();
            } else {
                registerSoLoadProxy(regex);
            }
            hooked = true;
        }
        
        mCache->reset();
        pthread_key_create(&guard, nullptr);
        update_configs(mCache, configs);
        started = true;
        // Leaks for debug purpose
//         char* p = (char*)malloc(200*sizeof(char));
//         update_configs(nullptr, 0);
//         pthread_key_delete(guard);
//         mCache->print();
    } else {
        RAPHAEL_INFO("Already started");
    }
    
    return NULL;
}

static napi_value Malloc(napi_env env, napi_callback_info info)
{
    char* p = (char*)malloc(200*sizeof(char));
    RAPHAEL_DEBUG("Test Malloc: %{public}d bytes", 200*sizeof(char));
    return NULL;
}

static napi_value Stop(napi_env env, napi_callback_info info)
{
    if (started) {
        update_configs(nullptr, 0);
        mCache->print();
        
        delete mCache;
        mCache = nullptr;
        
        pthread_key_delete(guard);
        started = false;
    } else {
        RAPHAEL_INFO("Already stopped");
    }
    return NULL;
}

static napi_value Print(napi_env env, napi_callback_info info)
{
    if (mCache) {
        pthread_setspecific(guard, (void *) 1);
    
        mCache->print();
        
        pthread_setspecific(guard, (void *) 0);
    }
    return NULL;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "Start", nullptr, Start, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "Malloc", nullptr, Malloc, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "Print", nullptr, Print, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "Stop", nullptr, Stop, nullptr, nullptr, nullptr, napi_default, nullptr },
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "raphael",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterRaphaelModule(void)
{
    napi_module_register(&demoModule);
}
