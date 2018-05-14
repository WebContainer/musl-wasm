# Notes

# Build

You need an `$LLVM_BINS` build directory correctly built to support WebAssembly.
E.g. https://github.com/groundwater/wasm-c-example

```
cd $MUSL_ROOT
mkdir -p out && cd out
AR=$LLVM_BINS/llvm-ar \
CFLAGS="-O0 -fvisibility=default" \
CC="$LLVM_BINS/clang --target=wasm32-unknown-unknown-wasm" \
RANLIB=$LLVM_BINS/llvm-ranlib \
../configure --disable-shared
make lib/libc.a
```

Build your app with `-L $MUSL_ROOT/out/lib -l c` to link.

# Weak Symbols

Marking a symbol `__attribute__((weak))`<sup>[1]</sup>:
- Allows that symbol to be _overwritten_ at link time by a strong symbol (the default).
- Does not emit an error if undefined at link time.

We mark any symbols we intend to import from JavaScript as _weak_.

- [`syscall_arch.h`](arch/wasm32/syscall_arch.h)

# Type Stuff

1. Had to modify `TYPEDEF long wchar_t;` to `TYPEDEF int wchar_t;` in [`alltypes.h.in`](arch/wasm32/bits/alltypes.h.in).
    - `int` seem to compile to `i32`
    - `long` seems to also compile to `i32`
    - `long long` compiles to `i64` tho

    Still not sure why we had to make this change.
    I'm assumnig in WASM32 pointers are 32-bit.

- https://stackoverflow.com/a/18901123

# Floating Point Issues

Currently getting this error on compiling `printf`.

```
wasm-ld: error: __lockfile.o: undefined symbol: a_cas
wasm-ld: error: __lockfile.o: undefined symbol: a_ll
wasm-ld: error: __lockfile.o: undefined symbol: a_sc
wasm-ld: error: __lock.o: undefined symbol: a_cas
wasm-ld: error: __lock.o: undefined symbol: a_ll
wasm-ld: error: __lock.o: undefined symbol: a_sc
wasm-ld: error: frexpl.o: undefined symbol: __netf2
wasm-ld: error: frexpl.o: undefined symbol: __multf3
wasm-ld: error: vfprintf.o: undefined symbol: __extenddftf2
wasm-ld: error: vfprintf.o: undefined symbol: __trunctfsf2
wasm-ld: error: vfprintf.o: undefined symbol: __trunctfdf2
wasm-ld: error: vfprintf.o: undefined symbol: __subtf3
wasm-ld: error: vfprintf.o: undefined symbol: __unordtf2
wasm-ld: error: vfprintf.o: undefined symbol: __addtf3
wasm-ld: error: vfprintf.o: undefined symbol: __netf2
wasm-ld: error: vfprintf.o: undefined symbol: __multf3
wasm-ld: error: vfprintf.o: undefined symbol: __fixtfsi
wasm-ld: error: vfprintf.o: undefined symbol: __floatsitf
wasm-ld: error: vfprintf.o: undefined symbol: __fixunstfsi
wasm-ld: error: vfprintf.o: undefined symbol: __floatunsitf
```

- It looks like these are float point routines, possibly provided by the compiler, but we disable builtins.
- https://gcc.gnu.org/onlinedocs/gccint/Soft-float-library-routines.html
- https://embeddedartistry.com/blog/2017/10/9/r1q7pksku2q3gww9rpqef0dnskphtc


<!-- Links -->

[1]: https://en.wikipedia.org/wiki/Weak_symbol
