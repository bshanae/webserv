# PROJECT CONFIG

СС=clang++
BASE_CC_FLAGS=-g -std=c++98
LD=clang++
BASE_LD_FLAGS=

PROJECT_NAME=webserv

SRCS=main/src/main.cpp                                                        \
	 main/src/config/Config.cpp                                               \
	 main/src/config/LogConfig.cpp                                            \
	 main/src/config/ServerConfig.cpp                                         \
	 main/src/config/CGIConfig.cpp                                            \
	 main/src/config/MediaConfig.cpp                                          \
	 main/src/config/utils.cpp                                                \
	 main/src/server/core/coreServer/CoreServer.cpp                           \
	 main/src/server/core/socketControllers/SocketController.cpp              \
	 main/src/server/core/socketControllers/ServerSocketController.cpp        \
	 main/src/server/core/socketControllers/ClientSocketController.cpp        \
	 main/src/server/core/messages/Request.cpp                                \
     main/src/server/core/messages/Response.cpp                               \
     main/src/server/app/Server/Server.cpp                                    \
	 main/src/server/app/locationProcessor/LocationProcessor.cpp              \
	 main/src/server/app/requestProcessors/RequestProcessor.cpp               \
	 main/src/server/app/requestProcessors/GetRequestProcessor.cpp            \
	 main/src/server/app/requestProcessors/HeadRequestProcessor.cpp           \
	 main/src/server/app/requestProcessors/PostRequestProcessor.cpp           \
	 main/src/server/app/project/Project.cpp                                  \
	 main/src/server/app/project/IndexGenerator.cpp                           \
	 main/src/server/app/cgi/CGIExecutor.cpp                                  \
	 main/src/log/log.cpp                                                     \
	 main/src/log/logStream/LogStream.cpp                                     \
	 main/src/log/logModifier/LogModifier.cpp 							 	  \
	 main/src/utils/sys/sys.cpp                                               \
     main/src/common/HeaderName.cpp                                           \
     main/src/common/RequestMethod.cpp                                        \
     main/src/common/StatusCode.cpp                                           \
     main/src/common/MediaType.cpp                                            \
     main/src/common/WebAddress.cpp                                           \
     main/src/common/exceptions/WebException.cpp                              \
	 main/src/common/Location.cpp                                             \
	 main/src/utils/sys/Process.cpp                                           \
	 main/src/utils/sys/Pipe.cpp                                              \
	 main/src/utils/sys/FDescriptor.cpp                                       \
	 main/src/utils/sys/FDStream.cpp                                          \
	 main/src/utils/sys/sys.path.cpp                                          \
	 main/src/utils/algo/str.cpp									          \
	 main/src/utils/io/io.cpp										          \
	 main/src/utils/exceptions/SocketException.cpp                            \
     main/src/utils/exceptions/FileException.cpp                              \
     main/src/utils/exceptions/InvalidArgumentException.cpp                   \
     main/src/utils/exceptions/InvalidOperationException.cpp                  \
     main/src/utils/exceptions/InvalidStateException.cpp                      \
     main/src/utils/exceptions/SystemException.cpp                            \
     main/src/utils/exceptions/ParsingException.cpp
INCLUDE_DIRS=main/src
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
