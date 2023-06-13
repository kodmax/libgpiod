#include <gpiod.h>
#include <nan.h>
#include <stdio.h>
#include <unistd.h>

namespace libgpiod {
using v8::Array;
using v8::Context;
using v8::Exception;
using v8::External;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Null;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void chip_open_by_name(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value chipname(isolate, args[0]);
  struct gpiod_chip *chip;

  chip = gpiod_chip_open_by_name(*chipname);

  if (chip != NULL) {
    args.GetReturnValue().Set(External::New(isolate, chip));

  } else {
    args.GetReturnValue().Set(Null(isolate));
  }
}

void chip_open_lookup(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value chipname(isolate, args[0]);
  struct gpiod_chip *chip;

  chip = gpiod_chip_open_lookup(*chipname);

  if (chip != NULL) {
    args.GetReturnValue().Set(External::New(isolate, chip));

  } else {
    args.GetReturnValue().Set(Null(isolate));
  }
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

  uint32_t offset = args[1]->Uint32Value(isolate->GetCurrentContext()).FromMaybe(0);

  struct gpiod_line *line = gpiod_chip_get_line(
      (gpiod_chip *)External::Cast(*args[0])->Value(),
      offset);

  if (line != NULL) {
    args.GetReturnValue().Set(External::New(isolate, line));

  } else {
    args.GetReturnValue().Set(Null(isolate));
  }
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

  if (args.Length() != 3 || !args[0]->IsExternal() || !args[1]->IsString() || !args[2]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value consumer(isolate, args[1]);
  uint32_t defaultVal = args[2]->Int32Value(isolate->GetCurrentContext()).FromMaybe(0);

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

void line_event_wait(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 3 || !args[0]->IsExternal() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  timespec ts = {
      .tv_sec = args[1]->IntegerValue(isolate->GetCurrentContext()).FromMaybe(0),
      .tv_nsec = args[2]->IntegerValue(isolate->GetCurrentContext()).FromMaybe(0)};

  int status = gpiod_line_event_wait((gpiod_line *)External::Cast(*args[0])->Value(), &ts);
  args.GetReturnValue().Set(Number::New(isolate, status));
}

void line_event_get_fd(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsExternal()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  int fd = gpiod_line_event_get_fd((gpiod_line *)External::Cast(*args[0])->Value());
  args.GetReturnValue().Set(Number::New(isolate, fd));
}

void line_event_read(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsExternal()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  Local<Array> ret = Array::New(isolate, 4);
  gpiod_line_event event;

  int status = gpiod_line_event_read((gpiod_line *)External::Cast(*args[0])->Value(), &event);
  ret->Set(isolate->GetCurrentContext(), 0, Number::New(isolate, status));
  ret->Set(isolate->GetCurrentContext(), 1, Number::New(isolate, event.event_type));
  ret->Set(isolate->GetCurrentContext(), 2, Number::New(isolate, event.ts.tv_sec));
  ret->Set(isolate->GetCurrentContext(), 3, Number::New(isolate, event.ts.tv_nsec));

  args.GetReturnValue().Set(ret);
}

void line_event_read_fd(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  Local<Array> ret = Array::New(isolate, 4);
  gpiod_line_event event;

  int fd = args[0]->Int32Value(isolate->GetCurrentContext()).FromMaybe(-1);

  int status = gpiod_line_event_read_fd(fd, &event);
  ret->Set(isolate->GetCurrentContext(), 0, Number::New(isolate, status));
  ret->Set(isolate->GetCurrentContext(), 1, Number::New(isolate, event.event_type));
  ret->Set(isolate->GetCurrentContext(), 2, Number::New(isolate, event.ts.tv_sec));
  ret->Set(isolate->GetCurrentContext(), 3, Number::New(isolate, event.ts.tv_nsec));

  args.GetReturnValue().Set(ret);
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

  if (args.Length() != 2 || !args[0]->IsExternal() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  uint32_t val = args[1]->Int32Value(isolate->GetCurrentContext()).FromMaybe(0);

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

void version_string(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 0) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  const char *ver = gpiod_version_string();

  args.GetReturnValue().Set(
      String::NewFromUtf8(isolate, ver).FromMaybe(String::NewFromUtf8(isolate, "unknown").ToLocalChecked()));
}

void initialize(Local<Object> exports, Local<Value> module, Local<Context> ctx) {
  NODE_SET_METHOD(exports, "chip_open_by_name", chip_open_by_name);
  NODE_SET_METHOD(exports, "chip_open_lookup", chip_open_lookup);
  NODE_SET_METHOD(exports, "chip_get_line", chip_get_line);
  NODE_SET_METHOD(exports, "line_release", line_release);
  NODE_SET_METHOD(exports, "chip_close", chip_close);

  NODE_SET_METHOD(exports, "line_request_output", line_request_output);
  NODE_SET_METHOD(exports, "line_set_value", line_set_value);

  NODE_SET_METHOD(exports, "line_request_input", line_request_input);
  NODE_SET_METHOD(exports, "line_get_value", line_get_value);

  NODE_SET_METHOD(exports, "line_request_falling_edge_events", line_request_falling_edge_events);
  NODE_SET_METHOD(exports, "line_request_rising_edge_events", line_request_rising_edge_events);
  NODE_SET_METHOD(exports, "line_request_both_edges_events", line_request_both_edges_events);
  NODE_SET_METHOD(exports, "line_event_read_fd", line_event_read_fd);
  NODE_SET_METHOD(exports, "line_event_get_fd", line_event_get_fd);
  NODE_SET_METHOD(exports, "line_event_wait", line_event_wait);
  NODE_SET_METHOD(exports, "line_event_read", line_event_read);

  NODE_SET_METHOD(exports, "version_string", version_string);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, initialize)

} // namespace libgpiod
