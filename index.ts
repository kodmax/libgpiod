import bind from 'bindings'
const libgpiod = bind('gpiod.node')

const chip: unknown = libgpiod.chip_open_by_name('gpiochip0')

libgpiod.blink(chip)

libgpiod.chip_close(chip)
