MAKE = make
SRC = src

all: 
	$(MAKE) --directory=$(SRC) $@

clean:
	$(MAKE) clean --directory=$(SRC) $@

