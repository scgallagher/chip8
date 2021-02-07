# chip8
On Windows 10 this will only compile with the Cygwin toolchain for some reason.

Before launching for the first time on Windows, you have to start X server:
* startxwin >/dev/null 2>&1 &
* export DISPLAY=:0.0
