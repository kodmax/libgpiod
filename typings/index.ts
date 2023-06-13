import { BothEdges, EvFalling, EvRising, FallingEdge, RisingEdge, SError, SEvent, SSuccess, STimeout } from "../consts"

export type SSuccess = typeof SSuccess
export type SError = typeof SError
export type STimeout = typeof STimeout
export type SEvent = typeof SEvent
    
export type Edge = typeof FallingEdge | typeof RisingEdge | typeof BothEdges
export type ConsumerId = string

export type Timespec = {
    nanosec: number
    sec: number
}

export type EvFalling = typeof EvFalling
export type EvRising = typeof EvRising

export type EventType = EvRising | EvFalling

export type Event = {
    type: EventType
    ts: number
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
