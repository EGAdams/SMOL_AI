# Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic
LDFLAGS = 
DOXYGEN = doxygen

SRCDIR = .
BUILDDIR = build
TARGET = ScoreBoard.test.exe

SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET) $(LDFLAGS)"; $(CXX) $^ -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) -c -o $@ $<"; $(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: docs
docs:
	@echo " Generating documentation..."
	@echo " $(DOXYGEN) doxygen_config"; $(DOXYGEN) doxygen_config

.PHONY: format
format:
	@echo " Formatting code..."
	@echo " clang-format -i $(SOURCES)"; clang-format -i $(SOURCES)

.PHONY: lint
lint:
	@echo " Running linter..."
	@echo " clang-tidy $(SOURCES)"; clang-tidy $(SOURCES)

-include $(DEPS)

# Dependency files
$(BUILDDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " Generating dependency file for $<..."
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILDDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Phony targets
.PHONY: all clean docs format lint

all: $(TARGET)

# End of Makefile.