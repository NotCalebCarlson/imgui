CXX       = x86_64-w64-mingw32-g++
IMGUI_DIR = external/imgui
BUILD     = build
OUT       = $(BUILD)/app.exe

CXX_SOURCES = \
	src/main.cpp \
	src/ui.cpp \
	$(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_win32.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_dx11.cpp

CXXFLAGS = -O2 -std=c++17 -Isrc -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
LDFLAGS  = -static -static-libgcc -static-libstdc++ -mwindows
LIBS     = -ld3d11 -ldxgi -ld3dcompiler -lgdi32 -limm32 -luser32 -lkernel32 -lshell32 -ldwmapi

OBJS = $(patsubst %.cpp,$(BUILD)/%.o,$(CXX_SOURCES))

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)


run: $(OUT)
	WINEDEBUG=-all wine $(OUT)

