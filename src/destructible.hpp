#ifndef TEST_ADDONS_NAPI_6_OBJECT_WRAP_DESTRUCTIBLE_H_
#define TEST_ADDONS_NAPI_6_OBJECT_WRAP_DESTRUCTIBLE_H_

#include <node_api.h>

class Destructible {
public:
    static 
    napi_value Init(napi_env env, napi_value exports);
    
    static 
    void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

private:
    explicit 
    Destructible(uint32_t id = 0);
    
    ~Destructible();

    static 
    napi_value New(napi_env env, napi_callback_info info);
    
    static 
    napi_value GetId(napi_env env, napi_callback_info info);
   
    static 
    napi_value DoCall(napi_env env, napi_callback_info info);


    static 
    napi_ref constructor;
    
    uint32_t id_;
    napi_env env_;
    napi_ref wrapper_;
    napi_ref func_;

    napi_value jsthis_;
};

#endif  // TEST_ADDONS_NAPI_6_OBJECT_WRAP_DESTRUCTIBLE_H_
