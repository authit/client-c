Telem Client C
---

Build
---

```bash
make
file ./test-client
```

Docker Build
---

```bash
./script/build
```

Usage
---

First import a public private key pair
```bash
./test-client import \
  ../../keys/crypto/public.pgp \
  ../../keys/crypto/private.pgp
```

Then encode a message
```bash
echo "This is a test message" > test.txt
./test-client encrypt test.txt
rm test.txt
```

Dependencies
---

- libgpgme11-dev
- libgpgme11-error-dev
- libassuan-dev
