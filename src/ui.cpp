#include "ui.h"
#include "imgui.h"

void RenderUI() {
    // Full-window borderless UI suitable for a driver installer
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("Automatic Updates", nullptr, flags);

    //ImGui::PushFont(g_FontLarge);
    ImGui::SeparatorText("System Hardware Info");
    //ImGui::PopFont();
    //ImGui::Separator();

    //static int counter = 0;

    // if (ImGui::Button("Scan Hardware & Install Drivers", ImVec2(250, 30))) {
    //     counter ++;
    // }

    ImGui::Text("Computr Model:");
    ImGui::Text("Processor:");
    ImGui::Text("Memory (RAM):");
    ImGui::Text("System Drive (C:):");
    ImGui::Text("Wi-Fi Adapter:");
    ImGui::Text("Bluetooth:");

    //ImGui::Text("%d", counter);

    ImGui::End();
}
