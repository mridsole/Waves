#include "stdafx.h"
#include "GUISimControlsWindow.h"

#include <stdio.h>
#include <string>

using namespace hwgui;

GUISimControlsWindow::GUISimControlsWindow() :
	playButtonLabel("Start"),
	offlineColor(0.8f, 0.1f, 0.2f, 1.0f),
	onlineColor(0.1f, 0.8f, 0.2f, 1.0f),
	pausedColor(0.1f, 0.2f, 0.8f, 1.0f),
	simHasStarted(false),
	simIsRunning(false),
	timeElapsed(0.f),
	state()
{

}


GUISimControlsWindow::~GUISimControlsWindow()
{
	
}

// if dereferencing of any state variables becomes invalid,
// bad things will happen here
void GUISimControlsWindow::drawGUI(const sf::Vector2u& windowSize) {
	
	bool b = true;
	
	int winFlags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar;

	ImGui::Begin("Simulation Controls", &b, winFlags);

	ImGui::Columns(2, "simCtrlColumns");
	ImGui::Separator();
	ImGui::Text("Controls"); ImGui::NextColumn();
	ImGui::Text("Breakpoints"); ImGui::NextColumn();
	ImGui::Separator();

	ImGui::Spacing();

	if (ImGui::Button(playButtonLabel, ImVec2(80, 20))) {
		
		if (!this->simHasStarted) {

			this->simHasStarted = true;
			this->simIsRunning = true;
			playButtonLabel = "Pause";

		} else if (this->simHasStarted && this->simIsRunning) {

			this->simIsRunning = false;
			playButtonLabel = "Continue";

		} else if (this->simHasStarted && !this->simIsRunning) {

			this->simIsRunning = true;
			playButtonLabel = "Pause";
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("Stop", ImVec2(80, 20))) {

		this->simHasStarted = false;
		this->simIsRunning = false;
		this->timeElapsed = 0.f;
	}

	ImGui::Spacing();

	ImGui::PushItemWidth(120);
	static float simSpeed = 1.f;
	ImGui::SliderFloat(" Speed", &simSpeed, 1.f, 10.f);
	ImGui::PopItemWidth();

	ImGui::Spacing();

	ImColor statusColor;
	std::string statusString;

	if (this->simHasStarted && this->simIsRunning) {

		statusColor = this->onlineColor;
		statusString = "Elapsed: ";
		char buffer[50];
		snprintf(buffer, sizeof(buffer), "%0.3fs", this->timeElapsed);
		statusString.append(buffer);

	} else if (this->simHasStarted && !this->simIsRunning) {

		statusColor = this->pausedColor;
		statusString = "Elapsed: ";
		char buffer[50];
		snprintf(buffer, sizeof(buffer), "%0.3fs", this->timeElapsed);
		statusString.append(buffer);

	} else if (!this->simHasStarted) {

		statusColor = this->offlineColor;
		statusString = "Offline";

		this->playButtonLabel = "Start";
	}

	ImGui::PushStyleColor(ImGuiCol_Button, statusColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, statusColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, statusColor);
	ImGui::Button("", ImVec2(20, 20)); ImGui::SameLine();
	ImGui::PopStyleColor(3);

	ImGui::PushItemWidth(140);
	ImGui::LabelText("", statusString.c_str());

	// breakpoint column
	ImGui::NextColumn();

	ImGui::Spacing();

	static bool stub;
	ImGui::Checkbox(" Enable Breakpoint", &stub);

	ImGui::Spacing();

	static float stub2 = 0.0f;

	// validation for manual entry
	if (stub2 < 0.f) stub2 = 0.f;

	ImGui::PushItemWidth(40);
	ImGui::DragFloat("Stop At", &stub2, 0.01f, 0.0f, 100000.0f);
	

	ImGui::SetWindowSize(ImVec2(400, 120));
	ImGui::SetWindowPos(ImVec2(10, windowSize.y - (ImGui::GetWindowSize().y + 10)));

	ImGui::End();
}
