#include "ui.h"
#include "imgui.h"

void RenderUI() {
    // Full-window borderless UI suitable for a driver installer
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("Driver Installer", nullptr, flags);

    ImGui::Text("System Driver Installer");
    ImGui::Separator();

    if (ImGui::Button("Scan Hardware & Install Drivers", ImVec2(240, 40))) {
        // Your driver installation logic goes here
    }

    ImGui::End();
}
