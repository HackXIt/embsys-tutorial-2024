all:
	$(MAKE) -C ./Session02 -j

Session02:
	$(MAKE) -C ./Session02 -j

clean:
	$(MAKE) -C ./Session02 clean

.PHONY: all clean