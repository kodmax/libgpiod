import { chipOpenByName, chipGetLine, lineRequestOutput, lineTrigger } from '../index'

const chip = chipOpenByName('gpiochip0')
const line17 = chipGetLine(chip, 17)

lineRequestOutput(line17, "flash", 0)

setInterval(() => {
    lineTrigger(line17, 1, 1000) // 1000 us = 1ms
}, 1000)
