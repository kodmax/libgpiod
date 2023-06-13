import { chipOpenByName, chipGetLine, lineRequestOutput, lineSetValue, getLibgpiodVersionString, lineRequestEvents, lineEventWait, SEvent, lineEventRead, SError, EvFalling } from '../index'

const chip = chipOpenByName('gpiochip0')
console.log(getLibgpiodVersionString())

const button = chipGetLine(chip, 27)
const led = chipGetLine(chip, 17)

lineRequestEvents(button, 'ButtonExample', 'Both')
lineRequestOutput(led, 'ButtonExample', 0)

while (true) {
    const status = lineEventWait(button, 10, 0)
    if (status === SEvent) {
        const event = lineEventRead(button)
        console.log(event)

        if (event !== SError) {
            lineSetValue(led, event.type === EvFalling ? 0 : 1)
        }
    }
}
