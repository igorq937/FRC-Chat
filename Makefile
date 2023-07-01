CC = gcc -std=c11
LDFLAGS = 
BLDDIR = .
INCDIR = $(BLDDIR)/inc
SRCDIR = $(BLDDIR)/src
OBJDIR = $(BLDDIR)/obj
CFLAGS = -c -Wall -Wextra -pedantic -I$(INCDIR)
SRCC = $(wildcard $(SRCDIR)/*.c)
OBJC = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCC))
OBJ = $(OBJC)
EXE = bin

all: clean $(EXE)
    
$(EXE) : $(OBJ) 
	$(CC) $(OBJDIR)/*.o -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	-rm -f ./$(OBJDIR)/*.o $(EXE)