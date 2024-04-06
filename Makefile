all:
	$(MAKE) -C ./Session02 -j

session2:
	$(MAKE) -C ./Session02 -j

clean:
	$(MAKE) -C ./Session02 clean

.PHONY: all clean