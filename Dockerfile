FROM debian:buster

ENV HOME="/home"
ENV PREFIX="$HOME/opt/cross"
ENV TARGET=i386-elf
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

WORKDIR $HOME/src
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
	grub \
	nasm \
	mtools

WORKDIR $HOME/kfs
RUN make

CMD ["tail", "-f", "/dev/null"]