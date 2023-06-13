import {
    chipOpenByName,
    chipGetLine,
    lineRequestOutput,
    lineSetValue,
    getLibgpiodVersionString,
    lineRequestEvents,
    lineEventWait,
    lineEventRead,
    StatusEvent,
    StatusError,
    EventTypeFalling
} from '../index'

const chip = chipOpenByName('gpiochip0')
console.log(getLibgpiodVersionString())

const button = chipGetLine(chip, 27)
const led = chipGetLine(chip, 17)

lineRequestEvents(button, 'ButtonExample', 'both')
lineRequestOutput(led, 'ButtonExample', 0)

while (true) {
    const status = lineEventWait(button, 10, 0)
    if (status === StatusEvent) {
        const event = lineEventRead(button)
        console.log(event)

        if (event !== StatusError) {
            lineSetValue(led, event.type === EventTypeFalling ? 0 : 1)
        }
    }
}
