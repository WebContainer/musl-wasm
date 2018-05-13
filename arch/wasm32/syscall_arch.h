#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) 0, __SYSCALL_LL_E((x))

// #ifdef __thumb__

// /* Avoid use of r7 in asm constraints when producing thumb code,
//  * since it's reserved as frame pointer and might not be supported. */
// #define __ASM____R7__
// #define __asm_syscall(...) do { \
// 	__asm__ __volatile__ ( "mov %1,r7 ; mov r7,%2 ; svc 0 ; mov r7,%1" \
// 	: "=r"(r0), "=&r"((int){0}) : __VA_ARGS__ : "memory"); \
// 	return r0; \
// 	} while (0)

// #else

// #define __ASM____R7__ __asm__("r7")
// #define __asm_syscall(...) do { \
// 	__asm__ __volatile__ ( "svc 0" \
// 	: "=r"(r0) : __VA_ARGS__ : "memory"); \
// 	return r0; \
// 	} while (0)
// #endif

/* For thumb2, we can allow 8-bit immediate syscall numbers, saving a
 * register in the above dance around r7. Does not work for thumb1 where
 * only movs, not mov, supports immediates, and we can't use movs because
 * it doesn't support high regs. */
// #ifdef __thumb2__
// #define R7_OPERAND "rI"(r7)
// #else
// #define R7_OPERAND "r"(r7)
// #endif

extern long __syscall0(long n);
extern long __syscall1(long n, long a);
extern long __syscall2(long n, long a, long b);
extern long __syscall3(long n, long a, long b, long c);
extern long __syscall4(long n, long a, long b, long c, long d);
extern long __syscall5(long n, long a, long b, long c, long d, long e);
extern long __syscall6(long n, long a, long b, long c, long d, long e, long f);

// #define VDSO_USEFUL
// #define VDSO_CGT_SYM "__vdso_clock_gettime"
// #define VDSO_CGT_VER "LINUX_2.6"

// #define SYSCALL_FADVISE_6_ARG
