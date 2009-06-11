.PHONY: deps-freebsd deps-ubuntu deps-gentoo use-apt use-emerge use-ports
deps-freebsd: use-ports
deps-ubuntu: use-apt
deps-gentoo: use-emerge
use-apt:
use-emerge:
use-ports:
	make -C /usr/ports/devel/allegro install distclean
