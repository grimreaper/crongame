.PHONY: deps deps-freebsd deps-ubuntu deps-gentoo use-apt use-emerge use-ports install root-check
PREFIX ?= /usr/local
deps:
	@echo "Type [p]make <operating system> to start installation."
deps-freebsd: use-ports
deps-ubuntu: use-apt
deps-gentoo: use-emerge
use-apt: root-check
	apt-get install liballegro4.2-dev
use-emerge: root-check
	emerge -av media-libs/allegro
use-ports: root-check
	make -C /usr/ports/devel/allegro install distclean
install: all
	cp $(NAME) $(PREFIX)/bin
root-check:
	@$(SCRIPTDIR)/rootcheck.sh