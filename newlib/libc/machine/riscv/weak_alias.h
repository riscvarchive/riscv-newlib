#ifndef __WEAK_ALIAS_H_
#define __WEAK_ALIAS_H_

#define weak_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((__weak__, __alias__ (#name)));

#endif /* __WEAK_ALIAS_H_ */
