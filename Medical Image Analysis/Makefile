LIBPHOTO_PATH = ./libphoto
FLASHPHOTO_PATH = ./FlashPhoto
MIA_PATH = ./MIA

PHOTO_LIB = $(LIBPHOTO_PATH)/lib/libphoto.a
FLASHPHOTO_EXE = $(FLASHPHOTO_PATH)/FlashPhoto
MIA_EXE = $(MIA_PATH)/MIA

all: $(PHOTO_LIB) $(FLASHPHOTO_EXE) $(MIA_EXE)

rebuild: clean all

$(PHOTO_LIB):
	$(MAKE) -C $(LIBPHOTO_PATH) all

$(FLASHPHOTO_EXE):
	$(MAKE) -C $(FLASHPHOTO_PATH) all

$(MIA_EXE):
	$(MAKE) -C $(MIA_PATH) all

clean:
	$(MAKE) -C $(FLASHPHOTO_PATH) clean
	$(MAKE) -C $(MIA_PATH) clean

cleanall:
	$(MAKE) -C $(FLASHPHOTO_PATH) cleanall
	$(MAKE) -C $(MIA_PATH) clean
