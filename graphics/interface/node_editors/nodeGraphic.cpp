#include "nodeGraphic.h"

NodeGrapchic::NodeGrapchic(){
    /** Definimos el contexto del sistema de nodos **/

    configNode.SettingsFile = "Simple.json";
    m_ContextNode = ax::NodeEditor::CreateEditor(&configNode);/**/
}

NodeGrapchic::~NodeGrapchic(){
}

bool NodeGrapchic::show(){
	ImGui::Text("Control de Nodo");

    ax::NodeEditor::SetCurrentEditor(m_ContextNode);
    ax::NodeEditor::Begin("My Editor", ImVec2(0.0, 0.0f));
    int uniqueId = 1;
    ax::NodeEditor::BeginNode(uniqueId++);
    ImGui::Text("Node A");
    ax::NodeEditor::BeginPin(uniqueId++, ax::NodeEditor::PinKind::Input);
    ImGui::Text("-> In");
    ax::NodeEditor::EndPin();
    ImGui::SameLine();
    ax::NodeEditor::BeginPin(uniqueId++, ax::NodeEditor::PinKind::Output);
    ImGui::Text("Out ->");
    ax::NodeEditor::EndPin();
    ax::NodeEditor::EndNode();
    ax::NodeEditor::End();
	return false;
}
