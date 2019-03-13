// C-style API, with a callback

#pragma once

// callback function type
typedef void (*simple_callback) (int id, void *closure);

// register a callback
// returns the handle (>=0)
int simple_register(simple_callback callback, void *closure);

// unregister the callback associated with the specified handle
// note: do not call this function from a callback, it will deadlock
void simple_unregister(int handle);

// start dispatching
void simple_start();

// stop dispatching
void simple_stop();
