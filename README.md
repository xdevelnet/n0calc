# n0calc

n0calc is extremely simple but handy GUI calculator. It was created just for fun and improving my GUI creation skills. Used toolkit - GTK3 (probably compatiable with GTK2).

![n0calc preview](https://raw.githubusercontent.com/xdevelnet/filedrop/master/img/n0calc.png)

Calculator evaluates expression at specified format:

`operand1*operand2`

where * is operator, can be '+', '-', '*', '/', operand1 and operand2 are operands.

Digital keyboard is supported. Wrong and incompatiable expressions are handled with informative error message. Round brackets, ^ operator, and other stuff are not supported. White spaces normalization will be added soon.

# How to build

### 1) Build with cmake

Download & install development gtk3 packages using OS package manager.
Download latest (at least 3.2) cmake release. cd to downloaded repository. Then:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### 2) Build manually

Download & install development gtk3 packages using OS package manager.
cd to downloaded repository. Then:
```
$ gcc `pkg-config --cflags gtk+-3.0` -o n0calc main.c `pkg-config --libs gtk+-3.0` -lm
```
