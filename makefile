all:
	clang vice.c init.c bitboards.c -o vice
# all:
# 	CXXFLAGS = -0g -Wall -Wextra

# 	GCC_CXXFLAGS = -DMESSAGE='"Compiled with GCC"'
# 	CLANG_CXXFLAGS = -DMESSAGE='"Compiled with Clang"'
# 	UNKNOWN_CXXFLAGS = -DMESSAGE='"Compiled with an unknown compiler"'

# 	ifeq ($(CXX), g++)
# 		CXXFLAGS += $(GCC_CXXFLAGS)
# 		gcc vice.c init.c -o vice
# 	else ifeq ($(CXX), clang)
# 		CXXFLAGS += $(CLANG_CXXFLAGS)
# 		clang vice.c init.c -o vice
# 	else
# 		CXXFLAGS += $(UNKNOWN_CXXFLAGS)
# 	endif

	