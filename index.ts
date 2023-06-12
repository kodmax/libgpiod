import bind from 'bindings'

const libgpiod = bind('gpiod.node')


console.log(libgpiod.hello())
