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

    static int counter = 0;

    if (ImGui::Button("Scan Hardware & Install Drivers", ImVec2(240, 40))) {
        counter ++;
    }

    ImGui::Text("%d", counter);

    ImGui::End();
}
