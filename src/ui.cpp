#include "ui.h"
#include "imgui.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "safe_thread.hpp"

using namespace ImGui;
using namespace std::chrono_literals;

struct HardwareSpecs {
    int counter = 0;
};

void T_RefreshSpecs(SafeThread<HardwareSpecs>* thread)
{
    while (!thread->MasterRequestingStop())
    {
        {
            auto data = thread->Lock();
            data->counter += 1;
        }
        std::this_thread::sleep_for(1s);
    }
}

HardwareSpecs hardware_data{};
SafeThread<HardwareSpecs> thread_hardware_specs(hardware_data, T_RefreshSpecs);

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

    if (Button("Refresh Hardware Specs"))
    {
        thread_hardware_specs.Start();
    }
    thread_hardware_specs.SoftJoin();
    SameLine();
    if (Button("Stop Early")) {
        thread_hardware_specs.RequestStop();
        std::cout << __cplusplus << std::endl;
    }

    {
        auto data = thread_hardware_specs.Lock();
        Text("%d", data->counter);
    }

    if (BeginTable("Hardware Specs Table", 2, table_flags))
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

}
