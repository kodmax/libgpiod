import bind from 'bindings'
const {
    blink,
    chip_open_by_name,
    chip_close,
    chip_get_line,
    line_release,
    line_request_output,
    line_request_input,
    line_get_value,
    line_set_value
} = bind('gpiod.node')

const chip: unknown = chip_open_by_name('gpiochip0')

const button: unknown = chip_get_line(chip, 27)
const led: unknown = chip_get_line(chip, 17)

line_request_output(led, "nodeee", 1)
line_request_input(button, "nodeee")

let i = 0
setInterval(() => {
    i++
    console.log(line_set_value(led, i % 2), i % 2, new Date().getTime())
}, 50)


// line_release(button)
// line_release(led)

// chip_close(chip)
