FROM debian:buster

ENV HOME="/home"
ENV PREFIX="$HOME/opt/cross"
ENV TARGET=i686-elf
ENV PATH="$PREFIX/bin:$PATH"
ENV PATH="$HOME/opt/cross/bin:$PATH"

RUN apt-get update && apt-get install -y \
	wget \
	gcc \
	g++ \
	make \
	bison \
	flex \
	libgmp3-dev \
	libmpc-dev \
	libmpfr-dev \
	texinfo \
	libisl-dev \
	xorriso

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz
RUN tar -xvf binutils-2.41.tar.gz
RUN rm binutils-2.41.tar.gz

RUN wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz
RUN tar -xvf gcc-13.2.0.tar.gz
RUN rm gcc-13.2.0.tar.gz

RUN wget https://ftp.gnu.org/gnu/gdb/gdb-14.2.tar.gz
RUN tar -xvf gdb-14.2.tar.gz
RUN rm gdb-14.2.tar.gz

WORKDIR $HOME/src
RUN mkdir gdb
RUN cd gdb && \
	/gdb-14.2/configure && \
	make && \
	make install
	
RUN mkdir build-binutils
RUN cd build-binutils && \
	/binutils-2.41/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && \
	make && \
	make install

RUN mkdir build-gcc
RUN cd build-gcc && \
	/gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers && \
	make all-gcc && \
	make all-target-libgcc && \
	make install-gcc && \
	make install-target-libgcc

RUN apt-get install -y \
	nasm \
	mtools \
	grub-pc-bin \
	grub-common

WORKDIR /home/kfs

CMD ["tail", "-f", "/dev/null"]