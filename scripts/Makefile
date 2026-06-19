# scripts/Makefile
#
# Builds gpio_test and generates DV-style inspection artifacts:
#   gpio_test.lst   — disassembly interleaved with C++ source
#   gpio_test.map   — symbol table sorted by address (label locations)
#   gpio_test.sections — section/region sizes and addresses

CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -O2 -g
#                                         ^^
#                                         -g — embed debug info
#                                         REQUIRED for source-annotated
#                                         disassembly to work at all

MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_ROOT := $(MAKEFILE_DIR)..

SRC_DIR      := $(PROJECT_ROOT)/src
INCLUDE_DIR  := $(PROJECT_ROOT)/include

CXXFLAGS += -I$(INCLUDE_DIR)

TARGET   := gpio_test
SOURCES  := $(SRC_DIR)/gpio.cpp $(SRC_DIR)/main.cpp

# ──────────────────────────────────────────────
# Primary build
# ──────────────────────────────────────────────
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# ──────────────────────────────────────────────
# Artifact 1 — disassembly with source annotation
# Equivalent to: annotated gate-level netlist
# ──────────────────────────────────────────────
$(TARGET).lst: $(TARGET)
	objdump -S -d $(TARGET) > $(TARGET).lst
#          ^  ^
#          |  -d  disassemble executable sections
#          -S      interleave source lines (requires -g at compile time)

# ──────────────────────────────────────────────
# Artifact 2 — symbol map, sorted by address
# Equivalent to: hierarchical signal/instance name list
# ──────────────────────────────────────────────
$(TARGET).map: $(TARGET)
	nm -C -n $(TARGET) > $(TARGET).map
#     ^  ^
#     |  -n  sort numerically by address — so it reads top-to-bottom
#     -C     demangle C++ names (bcm2837::gpio::init not _ZN7bcm28...)

# ──────────────────────────────────────────────
# Artifact 3 — section/region map
# Equivalent to: floorplan / area report
# ──────────────────────────────────────────────
$(TARGET).sections: $(TARGET)
	@echo "=== Section sizes ===" >  $(TARGET).sections
	size $(TARGET)                >> $(TARGET).sections
	@echo ""                      >> $(TARGET).sections
	@echo "=== Section addresses and sizes (detailed) ===" >> $(TARGET).sections
	readelf -S $(TARGET)          >> $(TARGET).sections

# ──────────────────────────────────────────────
# Convenience target — build binary + all three artifacts
# ──────────────────────────────────────────────
artifacts: $(TARGET) $(TARGET).lst $(TARGET).map $(TARGET).sections
	@echo "Generated:"
	@echo "  $(TARGET)            — the binary"
	@echo "  $(TARGET).lst        — disassembly with source"
	@echo "  $(TARGET).map        — symbol table, address sorted"
	@echo "  $(TARGET).sections   — section/region sizes"

clean:
	rm -f $(TARGET) $(TARGET).lst $(TARGET).map $(TARGET).sections

.PHONY: clean artifacts