#pragma once

// callback function prototype
typedef void (*callbackFunc_t) (int id, void *user_p);

// callback function info
struct CallbackFuncInfo
{
  callbackFunc_t callback_p;
  void *user_p;
};
  
// create a session (i.e. register a callback handler)
void sessionCreate(CallbackFuncInfo* funcInfo_p);

// start dispatching
void simpleStart();

// stop dispatching
void simpleStop();
