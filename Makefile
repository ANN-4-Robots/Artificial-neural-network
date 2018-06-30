CC := g++ 

SRCDIR := src
BUILDDIR := build
TARGET := bin/neat
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -pedantic -std=c++11 
OGLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
INC := -I inc 

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(OGLFLAGS)"; $(CC) $^ -o $(TARGET) $(OGLFLAGS) 
	@echo " $(RM) -r $(BUILDDIR)"; $(RM) -r $(BUILDDIR)
	./bin/neat

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR)"; $(RM) -r $(BUILDDIR)

.PHONY: clean
