
#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdint.h>
#include <stddef.h>

#define PLUGIN_MAGIC 'moduplgn'

typedef int (*f_init)(void);
typedef void (*f_deiniti)(void);

typedef struct {
  const char *symName;
  void *symVal;
} t_symbols;

typedef struct{
  uint64_t    magic;  //PLUGIN_MAGIC
  f_init      constructorFunc;
  f_deiniti   destructorFunc;
  /*
    idx into symbols array. symName is defined, but symVal should be provided from modulOS
    list is zeroTerminated
  */
  uint32_t    cntSymsRequired;
  /*
    idx into symbols array. symName and symVal are defined and can be used by modulOS after initializer was called
    list is zeroTerminated
  */
  uint32_t    cntSymsAvailable;
  /*
    First requires syms,
    then available syms
  */
  t_symbols   symbols[];
} t_pluginHDR;


#endif  //PLUGIN_H

