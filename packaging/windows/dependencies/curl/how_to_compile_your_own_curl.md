#install visual studio.

c:"\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 8.1

cd C:\Users\Krs\Downloads\curl-7.56.1\curl-7.56.1\winbuild

nmake /f Makefile.vc mode=dll MACHINE=x64