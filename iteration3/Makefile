PHOTO_LIB = ./libphoto/lib/libphoto.a
FLASHPHOTO_EXE = ./FlashPhoto/FlashPhoto

all: $(PHOTO_LIB) $(FLASHPHOTO_EXE)

rebuild: clean all

$(PHOTO_LIB):
	$(MAKE) -C ./libphoto all

$(FLASHPHOTO_EXE):
	$(MAKE) -C ./FlashPhoto all

clean:
	$(MAKE) -C ./FlashPhoto clean

cleanall:
	$(MAKE) -C ./FlashPhoto cleanall