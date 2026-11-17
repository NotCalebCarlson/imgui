#include "ui.h"
#include "imgui.h"
#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include <ctime>

/*
 * std::atomic
 * load()
 * store()
 *
 * std::mutex
 * std::lock_guard<std::mutex> lock(mtx);
 */

std::string time_progress = "0:0";
bool load_hardware_thread_running = false;
std::mutex mutex_load_hardware;
std::thread thread_load_hardware;
std::atomic<bool> thread_load_hardware_request_stop{false};

void LoadHardwareSpecs() {
    while (!thread_load_hardware_request_stop.load()) {
        // Do stuff
    }
    {
        std::lock_guard<std::mutex> lock(mutex_load_hardware);
        load_hardware_thread_running = false;
    }
}


using namespace ImGui;

void RenderUI() {

    const ImGuiViewport* viewport = GetMainViewport();
    SetNextWindowPos(viewport->WorkPos);
    SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    ImGuiTableFlags table_flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH;

    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 3.0f;
    style.FrameBorderSize = 1.0f;

    Begin("Automatic Updates", nullptr, flags);

    SeparatorText("System Hardware Info");

    {
        std::lock_guard<std::mutex> lock(mutex_load_hardware);
        if (!load_hardware_thread_running && thread_load_hardware.joinable()) {
            thread_load_hardware.join();
        }
        if (Button("Refresh Hardware Specs") && !load_hardware_thread_running) {
            load_hardware_thread_running = true;
            thread_load_hardware_request_stop.store(false);
            thread_load_hardware = std::thread(LoadHardwareSpecs);
        }
    }


    if (BeginTable("Hardware Specs Table", 2, table_flags, ImVec2(400.0f, 0.0f)))
    {
        TableSetupColumn("Item");
        TableSetupColumn("Value");
        TableHeadersRow();

        TableNextColumn();
        Text("Computr Model");
        TableNextColumn();
        Text("Dell Optiplex 7460");
        TableNextColumn();
        Text("Processor");
        TableNextColumn();
        Text("Intel i7 8th gen");
        TableNextColumn();
        Text("Memory");
        TableNextColumn();
        Text("16 GB DDR4");

        TableNextColumn();
        Text("System Drive");
        TableNextColumn();
        Text("256 GB NVME SSD");
        TableNextColumn();
        Text("Wi-Fi Adapter");
        TableNextColumn();
        Text("Yes");
        TableNextColumn();
        Text("Bluetooth");
        TableNextColumn();
        Text("Yes");

        EndTable();
    }

    End();
}

void CleanupUI() {
    thread_load_hardware_request_stop.store(true);
    if (thread_load_hardware.joinable()) {
        thread_load_hardware.join();
    }
}
