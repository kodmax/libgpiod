import { Chip, Line, ConsumerId, BitValue, SSuccess, SError, SEvent, STimeout, Event, Edge } from './types/types'
import bind from 'bindings'

export * from './types/types'
export * from './types/consts'

const {
    chip_open_by_name,
    chip_open_lookup,
    chip_close,
    chip_get_line,
    line_release,
    line_request_output,
    line_request_input,
    line_get_value,
    line_set_value,
    line_request_rising_edge_events,
    line_request_falling_edge_events,
    line_request_both_edges_events,
    line_event_wait,
    line_event_read,
    line_event_get_fd,
    line_event_read_fd,
    version_string
} = bind('gpiod.node')

/**
 * @brief Open a gpiochip based on the best guess what the path is.
 * @param name f.ex gpiochip0
 * 
 * This routine tries to figure out whether the user passed it the path to the
 * GPIO chip, its name, label or number as a string. Then it tries to open it
 * using one of the gpiod_chip_open** variants.
 */
export const chipOpenLookup = (name: string): Chip | null => {
    return chip_open_lookup(name)
}

/**
 * @brief Open a gpiochip by name.
 * @param name f.ex gpiochip0
 */
export const chipOpenByName = (name: string): Chip | null => {
    return chip_open_by_name(name)
}

/**
 * @brief Close a GPIO chip handle and release all allocated resources.
 * @param chip 
 */
export const chipClose = (chip: Chip): void => {
    chip_close(chip)
}

/**
 * @brief Get the handle to the GPIO line at given offset.
 * @param chip
 * @param offset GPIO line number (f.ex 27)
 */
export const chipGetLine = (chip: Chip, offset: number): Line | null => {
    return chip_get_line(chip, offset)
}

/**
 * @brief Reserve a single line, set the direction to output.
 * @param line
 * @param consumerId an identifier of the client, can be any string indicating your application
 * @param initialValue initial value of the output
 */
export const lineRequestOutput = (line: Line, consumerId: ConsumerId, initialValue: BitValue): SSuccess | SError => {
    return line_request_output(line, consumerId, initialValue)
}

/**
 * @brief Reserve a single line, set the direction to input.
 * @param line 
 * @param consumerId an identifier of the client, can be any string indicating your application
 */
export const lineRequestInput = (line: Line, consumerId: ConsumerId): SSuccess | SError => {
    return line_request_input(line, consumerId)
}

/**
 * @brief Release a previously reserved line.
 * @param line 
 */
export const lineRelease = (line: Line): void => {
    line_release(line)
}

/**
 * @brief Set the value of a single GPIO line.
 * @param line
 * @param value 
 */
export const lineSetValue = (line: Line, value: BitValue): SSuccess | SError => {
    return line_set_value(line, value)
}

/**
 * @brief Read current value of a single GPIO line.
 * @param line
 * @param value 
 */
export const lineGetValue = (line: Line): BitValue | SError => {
    return line_get_value(line)
}


/**
 * @brief Get the API version of the library as a human-readable string.
 */
export const getLibgpiodVersionString = (): string => {
    return version_string()
}

/**
 * @brief Request notifications on a single line.
 * @param line 
 * @param consumerId 
 * @param edge 
 */
export const lineRequestEvents = (line: Line, consumerId: ConsumerId, edge: Edge): SSuccess | SError => {
    switch (edge) {

        case 'falling':
            return line_request_falling_edge_events(line, consumerId)

        case 'rising':
            return line_request_rising_edge_events(line, consumerId)

        case 'both':
            return line_request_both_edges_events(line, consumerId)
    }
}

/**
 * @brief Wait for an event on a single line.
 * @param line 
 * @param timeout 
 */
export const lineEventWait = (line: Line, sec: number, nsec: number): STimeout | SEvent | SError => {
    return line_event_wait(line, sec, nsec)
}

/**
 * @brief Read next pending event from the GPIO line. 
 * @param line 
 * @returns 
 */
export const lineEventRead = (line: Line): Event | SError => {
    const event = line_event_read(line)
    return event[0] === 0
        ? {
            nsec: event[3],
            sec: event[2],
            type: event[1]
        }
        : -1
}

/**
 * @brief Get the event file descriptor.
 * @param line
 * @returns 
 */
export const lineEventGetFD = (line: Line): number | SError => {
    return line_event_get_fd(line)
}

export const lineEventReadFd = (fd: number): Event | SError => {
    const event = line_event_read_fd(fd)
    return event[0] === 0
        ? {
            nsec: event[3],
            sec: event[2],
            type: event[1]
        }
        : -1
}