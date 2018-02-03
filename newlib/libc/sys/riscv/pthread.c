#define weak_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((__weak__, __alias__ (#name)));

int __pthread_setcancelstate(int state, int * oldstate)
{
  return 0;
}

weak_alias (__pthread_setcancelstate, pthread_setcancelstate)
