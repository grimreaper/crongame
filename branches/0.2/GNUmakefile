.PHONY: first ubuntu debian gentoo use-apt use-emerge
first:
	@echo "Run 'make <operating system>' to fetch pmake and then install missing deps"
ubuntu: use-apt
	pmake deps-ubuntu
debian: ubuntu #we treat them the same for now
gentoo: use-emerge
	pmake deps-gentoo
freebsd:
	make deps-freebsd

use-apt:
	@echo "installing pmake"
	@apt-get pmake
use-emerge:
	@echo "installing pmake"
	@emerge pmake