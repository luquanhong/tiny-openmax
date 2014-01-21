

TINY_INC_DIR :=
TINY_SRC_FILES := utils/log.c \
				test/testcast-log.c
				
TINY_OBJ_DIR := obj

CFLAG :=  -Iutils

LDFLAG := -Wl,--rpath-link=.,


#

OBJ := $(patsubst  %.c, ${TINY_OBJ_DIR}/%.o, $(TINY_SRC_FILES) )

LIBUTILS_OBJ := $(TINY_OBJ_DIR)/utils/log.o

$(warning "show obj $(OBJ) ")
all: mkobj $(OBJ) test


libtinyutils: $(LIBUTILS_OBJ)
	gcc  -shared  -fPIC -o libtinyutils.so  $(LIBUTILS_OBJ)


${TINY_OBJ_DIR}/%.o : %.c
	gcc $(CFLAG) -c $< -o $@


test: libtinyutils
	gcc $(CFLAG)  -L. libtinyutils.so -o testcast-log $(TINY_OBJ_DIR)/test/testcast-log.o 
	#-L. -ltinyutils 


mkobj:
	mkdir -p $(dir $(OBJ))

clean:
	 rm -rf $(TINY_OBJ_DIR)

