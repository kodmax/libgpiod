import bind from 'bindings'

const {
    chip_open_by_name,
    chip_get_line,
    line_request_output,
    line_set_value,
    line_request_both_edges_events,
    line_event_wait,
    line_event_read,
    version_string
} = bind('gpiod.node')

console.log(version_string())

const chip: unknown = chip_open_by_name('gpiochip0')

const button: unknown = chip_get_line(chip, 27)
const led: unknown = chip_get_line(chip, 17)

line_request_both_edges_events(button, "button")
line_request_output(led, "button", 0)

while (true) {
    const status = line_event_wait(button, 1, 0)
    if (status === 1) {
        const event = line_event_read(button)
        line_set_value(led, event[1]-1)
        console.log(event)
    }
}
