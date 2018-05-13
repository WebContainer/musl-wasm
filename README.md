# Notes

```
cd $MUSL_ROOT
mkdir -p out && cd out
CC="$CLANG --target=wasm32-unknown-unknown-wasm" ../configure --disable-shared
make lib/libc.a # this will make an incorrect archive
find . -name \*.o | xargs wasm-ld -o lib/libc.a  --allow-undefined-file=../external-symbols
```
