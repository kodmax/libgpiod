#include <nan.h>
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

namespace libgpiod {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {

   const char *chipname = "gpiochip0";
   struct gpiod_chip *chip;
   struct gpiod_line *lineRed;    // Red LED
   struct gpiod_line *lineGreen;  // Green LED
   struct gpiod_line *lineYellow; // Yellow LED
   struct gpiod_line *lineButton; // Pushbutton
   int i, val;

   // Open GPIO chip
   chip = gpiod_chip_open_by_name(chipname);

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
   gpiod_chip_close(chip);


  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(
      isolate, "world").ToLocalChecked());
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo 
