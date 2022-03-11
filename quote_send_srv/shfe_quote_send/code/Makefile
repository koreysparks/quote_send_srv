
PROJECT = quote_send_tcp
AUTHOR = bsmith
PREFIX = /usr/local
BOOST=$(BOOST_1_53_0)
HOME = -I./ -I$(BOOST) -I$(BASE_JYS)
# =================================


# ==============bin===================
LINK = $(PROJECT)
TARGET = $(PROJECT)
# ===================================


# ===============header====================
HEADERS = $(PROJECT)*.h
# ========================================


# ===============config====================
CC = g++

#CFLAGS = -Wall -D_DEBUG -DLANCE_LINUX
CFLAGS = -Wall -g -ggdb3  -fPIC  -DLANCE_LINUX
LFLAGS = -lpthread -lrt  -ldl \
	 -L$(BASE_JYS) -lbase_jys \
	$(BOOST)/stage/lib_linux64/libboost_thread-mt-d.a \
	$(BOOST)/stage/lib_linux64/libboost_system-mt-d.a \


OBJS = \
	shfe.o			
IMPORTS = \
# ========================================


# ==================compile====================
%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ $(HOME)
	
all : bin

bin : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS) $(IMPORTS)

install : $(TARGET)
		@cp $(TARGET) $(HOME)/bin/
		@ln -s $(HOME)/bin/$(TARGET) $(HOME)/bin/$(LINK)
		
clean:
	@rm -f $(OBJS)
	@rm -f $(TARGET)
	@rm -f $(PROJECT)
