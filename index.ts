import bind from 'bindings'
const {
    blink,
    chip_open_by_name,
    chip_close,
    chip_get_line,
    line_release
} = bind('gpiod.node')

const chip: unknown = chip_open_by_name('gpiochip0')

const button: unknown = chip_get_line(chip, 27)
const led: unknown = chip_get_line(chip, 17)

blink(led, button)

line_release(button)
line_release(led)

chip_close(chip)
