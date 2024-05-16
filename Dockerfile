FROM debian:buster

RUN apt update && apt install -y \
	build-essential \
	gcc-multilib \
	grub-pc-bin \
	xorriso

WORKDIR /home/kfs

CMD ["tail", "-f", "/dev/null"]
