import { chipOpenByName, chipGetLine, lineRequestOutput, lineSetValue } from '../index'

const chip = chipOpenByName('gpiochip0')
const line17 = chipGetLine(chip, 17)

lineRequestOutput(line17, 'blink17', 1)
let i = 0
setInterval(() => {
    lineSetValue(line17, ++i % 2 ? 1 : 0)
}, 150)
