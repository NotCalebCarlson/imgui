#include "ui.h"
#include "imgui.h"

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

    if (Button("Refresh Hardware Specs")) {
        // TODO: Refresh hardware specs
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



    //Text("%d", counter);

    End();
}
