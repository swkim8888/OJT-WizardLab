.EXPORT_ALL_VARIABLES:

TARGET			:= diary
TOPDIR			:= $(shell /bin/pwd)
SUBDIRS			:= main memo calendar

##################################

include $(TOPDIR)/Config.mk

all : compile $(OBJS)
	echo "hahahahahah"
	$(CC) $(OBJS) $(addsuffix /built-in.o,$(SUBDIRS)) -o $(TARGET)

include $(TOPDIR)/Rules.mk

