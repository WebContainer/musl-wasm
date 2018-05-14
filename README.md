# Notes

# Build

You need an `$LLVM_BINS` build directory correctly built to support WebAssembly.
E.g. https://github.com/groundwater/wasm-c-example

```
cd $MUSL_ROOT
mkdir -p out && cd out
AR=$LLVM_BINS/llvm-ar \
CFLAGS="-O0 -fvisibility=default" \
CC="$LLVM_BINS/llc --target=wasm32-unknown-unknown-wasm" \
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

<!-- Links -->

[1]: https://en.wikipedia.org/wiki/Weak_symbol
