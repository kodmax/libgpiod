import bind from 'bindings'
const {
    chip_open_by_name,
    chip_get_line,
    line_request_output,
    line_set_value
} = bind('gpiod.node')

const chip: unknown = chip_open_by_name('gpiochip0')
const line17: unknown = chip_get_line(chip, 17)
line_request_output(line17, "blink17", 1)

let i = 0
setInterval(() => {
    line_set_value(line17, ++i % 2)
}, 50)
