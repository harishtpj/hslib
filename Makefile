LIB_NAME = hs
HEADER_BUNDLE = hs.h
PREFIX = hs_

CC = gcc
CFLAGS = -Wall -Wextra -O3 -fPIC -Iinclude
AR = ar rcs

INC_DIR = include
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib
DIST_DIR = dist

# Files
HEADERS = $(wildcard $(INC_DIR)/*.h)
# If you have separate .c files, they go here. 
# If you are 100% hybrid/header-only, we create a wrapper.
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Output Targets
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).so
BUNDLE_PATH = $(DIST_DIR)/$(HEADER_BUNDLE)

.PHONY: all clean bundle static dynamic

all: bundle static dynamic

bundle: $(DIST_DIR)
	@echo "Bundling headers into $(BUNDLE_PATH)..."
	@echo "/* hslib by Harish Kumar - Single Header Version */" > $(BUNDLE_PATH)
	@echo "#ifndef HS_AMALGAMATED_H" >> $(BUNDLE_PATH)
	@echo "#define HS_AMALGAMATED_H" >> $(BUNDLE_PATH)
	@for f in $(HEADERS); do \
		echo "\n/* Module: $$f */" >> $(BUNDLE_PATH); \
		sed '/#ifndef HS_.*_H/,/#endif \/\* HS_.*_H \*\//d' $$f >> $(BUNDLE_PATH); \
	done
	@echo "\n#endif" >> $(BUNDLE_PATH)

static: $(LIB_DIR) $(OBJECTS)
	@echo "Creating Static Library $(STATIC_LIB)..."
	$(AR) $(STATIC_LIB) $(OBJECTS)

dynamic: $(LIB_DIR) $(OBJECTS)
	@echo "Creating Dynamic Library $(DYNAMIC_LIB)..."
	$(CC) -shared -o $(DYNAMIC_LIB) $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR) $(LIB_DIR) $(DIST_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(DIST_DIR)
	@echo "Cleaned up all build artifacts."
