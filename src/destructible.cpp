#include "destructible.hpp"
#include <cassert>
#include <cstdio>

napi_ref Destructible::constructor;

napi_value RunCallback(napi_env env, napi_value cb, uint32_t id) {
    napi_status status;

    napi_value argv[1];
    status = napi_create_uint32(env, id, argv);
    assert(status == napi_ok);

    napi_value global;
    status = napi_get_global(env, &global);
    assert(status == napi_ok);

    napi_value result;
    status = napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);

    return nullptr;
}

Destructible::Destructible(uint32_t id)
    : id_(id), env_(nullptr), wrapper_(nullptr) 
{}

Destructible::~Destructible() { 
    napi_delete_reference(env_, wrapper_);

    napi_value func;
    napi_status status = napi_get_reference_value(env_, func_, &func);
    assert(status == napi_ok);

    RunCallback(env_, func, id_);

    napi_delete_reference(env_, func_);
}

void Destructible::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<Destructible*>(nativeObject)->~Destructible();
}

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Destructible::Init(napi_env env, napi_value exports) {
    napi_property_descriptor properties[] = {
        { "id", 0, 0, GetId, nullptr, 0, napi_default, 0 }
      , DECLARE_NAPI_METHOD("doCall", DoCall)
    };

    napi_value cons;
    napi_status status = napi_define_class(env, "Destructible", NAPI_AUTO_LENGTH, New, nullptr, 3, properties, &cons);
    assert(status == napi_ok);

    status = napi_create_reference(env, cons, 1, &constructor);
    assert(status == napi_ok);

    status = napi_set_named_property(env, exports, "Destructible", cons);
    assert(status == napi_ok);
    return exports;
}

napi_value Destructible::New(napi_env env, napi_callback_info info) {

    napi_value target;
    napi_status status = napi_get_new_target(env, info, &target);
    assert(status == napi_ok);
    bool is_constructor = target != nullptr;

    if (is_constructor) {
        // Invoked as constructor: `new Destructible(...)`
        size_t argc = 2;
        napi_value args[2];
        napi_value jsthis;
        status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);

        assert(status == napi_ok);

        uint32_t id = 0;

        napi_valuetype valuetype;
        status = napi_typeof(env, args[0], &valuetype);
        assert(status == napi_ok);

        if (valuetype != napi_undefined) {
            status = napi_get_value_uint32(env, args[0], &id);
            assert(status == napi_ok);
        }

        napi_value cb = args[1];

        Destructible* obj = new Destructible(id);
        obj->env_ = env;

        status = napi_create_reference(env, cb, 1, &obj->func_);
        assert(status == napi_ok);

        status = napi_wrap(env,
                        jsthis,
                        reinterpret_cast<void*>(obj),
                        Destructible::Destructor,
                        nullptr,  // finalize_hint
                        &obj->wrapper_);
        assert(status == napi_ok);

        return jsthis;
    } else {
        // Invoked as plain function `Destructible(...)`, turn into construct call.
        size_t argc_ = 1;
        napi_value args[1];
        status = napi_get_cb_info(env, info, &argc_, args, nullptr, nullptr);
        assert(status == napi_ok);

        const size_t argc = 1;
        napi_value argv[argc] = {args[0]};

        napi_value cons;
        status = napi_get_reference_value(env, constructor, &cons);
        assert(status == napi_ok);

        napi_value instance;
        status = napi_new_instance(env, cons, argc, argv, &instance);
        assert(status == napi_ok);

        return instance;
    }
}

napi_value Destructible::GetId(napi_env env, napi_callback_info info) {
    napi_status status;

    napi_value jsthis;
    status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Destructible* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    napi_value num;
    status = napi_create_double(env, obj->id_, &num);
    assert(status == napi_ok);

    return num;
}

napi_value Destructible::DoCall(napi_env env, napi_callback_info info) {
    napi_status status;

    napi_value jsthis;
    status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Destructible* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    napi_value func;
    status = napi_get_reference_value(env, obj->func_, &func);
    assert(status == napi_ok);
    RunCallback(env, func, obj->id_);

    return nullptr;
}
