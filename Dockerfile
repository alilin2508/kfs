FROM debian:latest

RUN dpkg --add-architecture i386
RUN apt upgrade && apt update && apt install -y \
	build-essential \
	gcc \
	grub-pc-bin \
	xorriso

RUN apt install -y gcc-multilib

WORKDIR /home/kfs

CMD ["tail", "-f", "/dev/null"]
