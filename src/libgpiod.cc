#include <gpiod.h>
#include <nan.h>
#include <stdio.h>
#include <unistd.h>

namespace libgpiod {
using v8::Exception;
using v8::External;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
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

void blink(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() != 1 || !args[0]->IsExternal()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }


  // const char *chipname = "gpiochip0";

  struct gpiod_chip *chip = (gpiod_chip *)External::Cast(*args[0])->Value();
  struct gpiod_line *lineRed;    // Red LED
  struct gpiod_line *lineGreen;  // Green LED
  struct gpiod_line *lineYellow; // Yellow LED
  struct gpiod_line *lineButton; // Pushbutton
  int i, val;

  // Open GPIO chip
  // chip = gpiod_chip_open_by_name(chipname);

  //   // Open GPIO lines
  lineGreen = gpiod_chip_get_line(chip, 17);
  lineButton = gpiod_chip_get_line(chip, 27);

  //   // Open LED lines for output
  gpiod_line_request_output(lineGreen, "example1", 0);

  //   // Open switch line for input
  gpiod_line_request_input(lineButton, "example1");

  // Blink LEDs in a binary pattern
  i = 0;
  while (true) {
    gpiod_line_set_value(lineGreen, (i & 2) != 0);
    // Read button status and exit if pressed
    val = gpiod_line_get_value(lineButton);
    if (val == 1) {
      break;
    }

    usleep(10000);
    i++;
  }

  // Release lines and chip
  gpiod_line_release(lineGreen);
  gpiod_line_release(lineButton);
  // gpiod_chip_close(chip);

  args.GetReturnValue().Set(String::NewFromUtf8(
                                isolate, "world")
                                .ToLocalChecked());
}

void initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "chip_open_by_name", chip_open_by_name);
  NODE_SET_METHOD(exports, "chip_close", chip_close);

  NODE_SET_METHOD(exports, "blink", blink);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, initialize)

} // namespace libgpiod
