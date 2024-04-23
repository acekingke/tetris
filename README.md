# INSTALL ncurse
in macos
```shell
brew install ncurses
```
It has got message like this:
```
ncurses is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have ncurses first in your PATH, run:
  echo 'export PATH="/opt/homebrew/opt/ncurses/bin:$PATH"' >> ~/.zshrc

For compilers to find ncurses you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/ncurses/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/ncurses/include"

For pkg-config to find ncurses you may need to set:
  export PKG_CONFIG_PATH="/opt/homebrew/opt/ncurses/lib/pkgconfig"
==> Summary
🍺  /opt/homebrew/Cellar/ncurses/6.4: 4,001 files, 9.7MB
==> Running `brew cleanup ncurses`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
```
in Ubuntu:
```shell
sudo apt update
sudo apt install -y libncurses5-dev build-essential
```

# build
```shell
make
```

# run 
```shell
./tetris
```