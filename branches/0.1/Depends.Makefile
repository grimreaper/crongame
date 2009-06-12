.PHONY: deps deps-freebsd deps-ubuntu deps-gentoo use-apt use-emerge use-ports install
PREFIX ?= /usr/local
deps:
	@echo "Type [p]make <operating system> to start installation."
deps-freebsd: use-ports
deps-ubuntu: use-apt
deps-gentoo: use-emerge
use-apt:
use-emerge:
use-ports:
	make -C /usr/ports/devel/allegro install distclean
install: all
	cp $(NAME) $(PREFIX)/bin