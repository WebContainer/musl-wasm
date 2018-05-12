#define a_ll a_ll
static inline int a_ll(volatile int *p);

#define a_sc a_sc
static inline int a_sc(volatile int *p, int v);

#define a_barrier a_barrier
static inline void a_barrier();

#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s);

#define a_ll_p a_ll_p
static inline void *a_ll_p(volatile void *p);

#define a_sc_p a_sc_p
static inline int a_sc_p(volatile int *p, void *v);

#define a_cas_p a_cas_p
static inline void *a_cas_p(volatile void *p, void *t, void *s);

#define a_ctz_64 a_ctz_64
static inline int a_ctz_64(uint64_t x);

#define a_clz_64 a_clz_64
static inline int a_clz_64(uint64_t x);
