#include "napi/native_api.h"
#include "HookProxy.h"
#include "MemoryCache.h"
#include "Raphael.h"

#define LOGGER(fmt, ...) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "RAPHAEL", fmt, ##__VA_ARGS__)

// TODO: write to disk
static char  *mSpace = "raphael";
static Cache *mCache;
static bool started = false;

static napi_value Start(napi_env env, napi_callback_info info)
{
    if (!started) {
        mCache = new MemoryCache(mSpace);
        update_configs(mCache, 0);
        
        registerInlineProxy();
        
        mCache->reset();
        pthread_key_create(&guard, nullptr);
        update_configs(mCache, MAP64_MODE | ALLOC_MODE | 0x0F0000 | 10);
        started = true;
        // Leaks for debug purpose
        char* p = (char*)malloc(200*sizeof(char));
        update_configs(nullptr, 0);
        pthread_key_delete(guard);
        mCache->print();
    } else {
        LOGGER("Already started");
    }
    
    return NULL;
}

static napi_value Malloc(napi_env env, napi_callback_info info)
{
    char* p = (char*)malloc(200*sizeof(char));
    return NULL;
}

static napi_value Stop(napi_env env, napi_callback_info info)
{
    update_configs(nullptr, 0);
    pthread_key_delete(guard);
    return NULL;
}

static napi_value Print(napi_env env, napi_callback_info info)
{
    mCache->print();
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
