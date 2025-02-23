#include "plugin.h"

/*
  Everything in this file should have static/private linkage
*/

extern t_pluginHDR plugin_hdr;

#pragma mark stubs
int (*stub_printf)( const char * format, ... );


#pragma mark pubfuncs
int constructor(void){
  stub_printf = plugin_hdr.symmbols[0].symVal;
  return 0; //success
}

void destructor(void){
  //empty
}

void examplefunc(void){
  stub_printf("Hello World\n");
}

#pragma mark public
t_pluginHDR plugin_hdr = {
  .magic = PLUGIN_MAGIC,
  .constructorFunc = constructor,
  .destructorFunc = destructor,
  .cntSymsRequired = 1,
  .cntSymsAvailable = 1,
  .symbols = {
    //required
    {"printf"},

    //available
    {"examplefunc", examplefunc}
  }
};