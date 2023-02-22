# PROJECT CONFIG

СС=clang++
BASE_CC_FLAGS=-g -std=c++98
LD=clang++
BASE_LD_FLAGS=

PROJECT_NAME=webserv

SRCS=main/main.cpp                             \
	 main/context/Context.cpp                  \
	 main/context/config/Config.cpp            \
	 main/context/project/Project.cpp          \
	 main/server/Server.cpp                    \
	 main/server/worker/Worker.cpp             \
	 main/server/request/Request.cpp           \
	 main/server/response/Response.cpp         \
	 main/tools/exceptions/SocketException.cpp \
	 main/tools/log/handler/handler.cpp        \
	 main/tools/log/log.cpp
INCLUDE_DIRS=main
EXE_NAME=webserv

# TOOLS

DEBUG=$(info [DEBUG] $1)
SILENT=@

# CONSTANTS

BUILD_DIR=build
BUILD_OBJ_DIR=build/obj
BUILD_DEP_DIR=build/dep
BUILD_EXE_DIR=build

# DYNAMIC CONFIG

LOG=$(info [$(PROJECT_NAME)] $1)

OBJS=$(addprefix $(BUILD_OBJ_DIR)/,$(SRCS:.cpp=.o))
EXE=$(BUILD_EXE_DIR)/$(EXE_NAME)
CC_FLAGS=$(BASE_CC_FLAGS) $(addprefix -I,$(INCLUDE_DIRS))
LD_FLAGS=$(BASE_LD_FLAGS)

DEP=$(addprefix $(BUILD_DEP_DIR)/,$(SRCS:.cpp=.d))

# TEMPLATES

define OBJ_TEMPLATE
$(BUILD_OBJ_DIR)/$(1:.cpp=.o): $(1)
	$$(call LOG,Compiling CPP object $$<)
	$$(SILENT) mkdir -p $$(dir $$@)
	$$(SILENT) $$(CC) $$(CC_FLAGS) -c $$< -o $$@ -MMD -MP
endef

# TARGETS

all: $(EXE)

clean:
	$(call LOG,Deleting build)
	$(SILENT) rm -rf $(BUILD_DIR)

fclean: clean
	$(call LOG,Deleting executable)
	$(SILENT) rm -f $(EXE)

re: fclean all

debug:
	$(call DEBUG,src: $(SRCS))
	$(call DEBUG,obj: $(OBJS))

$(EXE): $(OBJS)
	$(call LOG,Linking executable)
	$(SILENT) $(LD) $(LD_FLAGS) $(OBJS) -o $@

$(foreach SRC,$(SRCS),$(eval $(call OBJ_TEMPLATE,$(SRC))))

# FINAL

-include $(DEP)
.PHONY: all clean fclean re debug
