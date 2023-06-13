#include <gpiod.h>
#include <nan.h>
#include <stdio.h>
#include <unistd.h>

namespace libgpiod {
using v8::Context;
using v8::Exception;
using v8::External;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

Local<Context> context;

void chip_open_by_name(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value chipname(isolate, args[0]);
  struct gpiod_chip *chip;

  chip = gpiod_chip_open_by_name(*chipname);

  args.GetReturnValue().Set(External::New(isolate, chip));
}

void chip_close(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsExternal()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  gpiod_chip_close((gpiod_chip *)External::Cast(*args[0])->Value());
}

void chip_get_line(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 2 || !args[0]->IsExternal() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  uint32_t offset = args[1]->Uint32Value(context).FromMaybe(0xffffffff);

  if (offset == 0xffffffff) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong line number").ToLocalChecked()));
    return;
  }

  struct gpiod_line *line = gpiod_chip_get_line(
      (gpiod_chip *)External::Cast(*args[0])->Value(),
      offset);

  args.GetReturnValue().Set(External::New(isolate, line));
}

void line_release(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsExternal()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  gpiod_line_release((gpiod_line *)External::Cast(*args[0])->Value());
}

void line_request_output(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 3 || !args[0]->IsExternal() || !args[1]->IsString() || !args [2]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value consumer(isolate, args[1]);
  uint32_t defaultVal = args[2]->Int32Value(context).FromMaybe(0xffffffff);
  if (defaultVal == 0xffffffff) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong default value").ToLocalChecked()));
    return;
  }

  int status = gpiod_line_request_output((gpiod_line *)External::Cast(*args[0])->Value(), *consumer, defaultVal);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_request_input(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 2 || !args[0]->IsExternal() || !args[1]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value consumer(isolate, args[1]);

  int status = gpiod_line_request_input((gpiod_line *)External::Cast(*args[0])->Value(), *consumer);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_request_rising_edge_events(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 2 || !args[0]->IsExternal() || !args[1]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value consumer(isolate, args[1]);

  int status = gpiod_line_request_rising_edge_events((gpiod_line *)External::Cast(*args[0])->Value(), *consumer);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_request_falling_edge_events(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 2 || !args[0]->IsExternal() || !args[1]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value consumer(isolate, args[1]);

  int status = gpiod_line_request_falling_edge_events((gpiod_line *)External::Cast(*args[0])->Value(), *consumer);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_request_both_edges_events(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 2 || !args[0]->IsExternal() || !args[1]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value consumer(isolate, args[1]);

  int status = gpiod_line_request_both_edges_events((gpiod_line *)External::Cast(*args[0])->Value(), *consumer);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_set_value(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 2 || !args[0]->IsExternal() || !args [1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  uint32_t val = args[1]->Int32Value(context).FromMaybe(0xffffffff);
  if (val == 0xffffffff) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong value").ToLocalChecked()));
    return;
  }

  int status = gpiod_line_set_value((gpiod_line *)External::Cast(*args[0])->Value(), val);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_get_value(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsExternal()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  int val = gpiod_line_get_value((gpiod_line *)External::Cast(*args[0])->Value());
  args.GetReturnValue().Set(Number::New(isolate, val));
}

void initialize(Local<Object> exports, Local<Value> module, Local<Context> ctx) {
  NODE_SET_METHOD(exports, "chip_open_by_name", chip_open_by_name);
  NODE_SET_METHOD(exports, "chip_get_line", chip_get_line);
  NODE_SET_METHOD(exports, "line_request_output", line_request_output);
  NODE_SET_METHOD(exports, "line_request_input", line_request_input);
  NODE_SET_METHOD(exports, "line_request_rising_edge_events", line_request_rising_edge_events);
  NODE_SET_METHOD(exports, "line_request_falling_edge_events", line_request_falling_edge_events);
  NODE_SET_METHOD(exports, "line_request_both_edges_events", line_request_both_edges_events);
  NODE_SET_METHOD(exports, "line_get_value", line_get_value);
  NODE_SET_METHOD(exports, "line_set_value", line_set_value);
  NODE_SET_METHOD(exports, "line_release", line_release);
  NODE_SET_METHOD(exports, "chip_close", chip_close);

  context = ctx;
}

NODE_MODULE(NODE_GYP_MODULE_NAME, initialize)

} // namespace libgpiod
