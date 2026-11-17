# Default target builds for Windows 11; use `make linux` to test natively
TARGET ?= windows

IMGUI_DIR = external/imgui
GLFW_DIR  = external/glfw

# Your application + ImGui core + ImGui GLFW/OpenGL3 backends
CXX_SOURCES = \
	src/main.cpp \
	$(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_demo.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

# Core GLFW C files shared by all desktop platforms
GLFW_C_SOURCES = \
	$(GLFW_DIR)/src/context.c \
	$(GLFW_DIR)/src/init.c \
	$(GLFW_DIR)/src/input.c \
	$(GLFW_DIR)/src/monitor.c \
	$(GLFW_DIR)/src/platform.c \
	$(GLFW_DIR)/src/vulkan.c \
	$(GLFW_DIR)/src/window.c \
	$(GLFW_DIR)/src/egl_context.c \
	$(GLFW_DIR)/src/osmesa_context.c \
	$(GLFW_DIR)/src/null_init.c \
	$(GLFW_DIR)/src/null_monitor.c \
	$(GLFW_DIR)/src/null_window.c \
	$(GLFW_DIR)/src/null_joystick.c

INCLUDES = -Isrc -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(GLFW_DIR)/include

ifeq ($(TARGET), windows)
	CC       = x86_64-w64-mingw32-gcc
	CXX      = x86_64-w64-mingw32-g++
	BUILD    = build/windows
	OUT      = $(BUILD)/app.exe
	CFLAGS   = -O2 -D_GLFW_WIN32 $(INCLUDES)
	CXXFLAGS = -O2 -std=c++17 $(INCLUDES)
	# -static bundles libgcc/libstdc++ so Windows 11 won't ask for MinGW DLLs
	# -mwindows hides the background command prompt window on Windows
	LDFLAGS  = -static -static-libgcc -static-libstdc++ -mwindows
	LIBS     = -lopengl32 -lgdi32 -limm32 -luser32 -lkernel32 -lshell32
	GLFW_C_SOURCES += \
		$(GLFW_DIR)/src/win32_init.c \
		$(GLFW_DIR)/src/win32_joystick.c \
		$(GLFW_DIR)/src/win32_module.c \
		$(GLFW_DIR)/src/win32_monitor.c \
		$(GLFW_DIR)/src/win32_time.c \
		$(GLFW_DIR)/src/win32_thread.c \
		$(GLFW_DIR)/src/win32_window.c \
		$(GLFW_DIR)/src/wgl_context.c
else
	CC       = gcc
	CXX      = g++
	BUILD    = build/linux
	OUT      = $(BUILD)/app
	CFLAGS   = -O2 -D_GLFW_X11 $(INCLUDES)
	CXXFLAGS = -O2 -std=c++17 $(INCLUDES)
	LDFLAGS  =
	LIBS     = -lGL -lX11 -ldl -lpthread
	GLFW_C_SOURCES += \
		$(GLFW_DIR)/src/x11_init.c \
		$(GLFW_DIR)/src/x11_monitor.c \
		$(GLFW_DIR)/src/x11_window.c \
		$(GLFW_DIR)/src/xkb_unicode.c \
		$(GLFW_DIR)/src/posix_module.c \
		$(GLFW_DIR)/src/posix_time.c \
		$(GLFW_DIR)/src/posix_thread.c \
		$(GLFW_DIR)/src/posix_poll.c \
		$(GLFW_DIR)/src/glx_context.c \
		$(GLFW_DIR)/src/linux_joystick.c
endif

OBJS = $(patsubst %.cpp,$(BUILD)/%.o,$(CXX_SOURCES)) \
       $(patsubst %.c,$(BUILD)/%.o,$(GLFW_C_SOURCES))

.PHONY: all windows linux clean

all: $(OUT)

windows:
	$(MAKE) TARGET=windows

linux:
	$(MAKE) TARGET=linux

$(OUT): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
