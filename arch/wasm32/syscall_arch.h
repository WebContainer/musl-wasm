#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) 0, __SYSCALL_LL_E((x))

// https://en.wikipedia.org/wiki/Weak_symbol
long __attribute__((weak)) __syscall0(long n);
long __attribute__((weak)) __syscall1(long n, long a);
long __attribute__((weak)) __syscall2(long n, long a, long b);
long __attribute__((weak)) __syscall3(long n, long a, long b, long c);
long __attribute__((weak)) __syscall4(long n, long a, long b, long c, long d);
long __attribute__((weak)) __syscall5(long n, long a, long b, long c, long d, long e);
long __attribute__((weak)) __syscall6(long n, long a, long b, long c, long d, long e, long f);
