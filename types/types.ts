import {
    EventTypeFalling,
    EventTypeRising,
    FallingEdge,
    RisingEdge,
    BothEdges,

    StatusSuccess,
    StatusTimeout,
    StatusError,
    StatusEvent
} from "./consts"

export type SSuccess = typeof StatusSuccess
export type SError = typeof StatusError
export type STimeout = typeof StatusTimeout
export type SEvent = typeof StatusEvent
    
export type Edge = typeof FallingEdge | typeof RisingEdge | typeof BothEdges
export type ConsumerId = string

export type EventType = typeof EventTypeFalling | typeof EventTypeRising

export type Event = {
    type: EventType
    nsec: number
    sec: number
}

/**
 * 1 for H (3.3v) and 0 for L (0v)
 */
export type BitValue = 0 | 1

/**
 * External, libgpiod reference.
 */
export type Chip = unknown

/**
 * External, libgpiod reference.
 */
export type Line = unknown
