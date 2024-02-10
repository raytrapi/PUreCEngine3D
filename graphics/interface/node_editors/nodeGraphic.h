#ifndef __NODE_GRAPHIC
#define __NODE_GRAPHIC

#include "../src/interfaceControl.h"
#include <../../../vendors/imgui-node-editor/imgui_node_editor.h>

class NodeGrapchic: public InterfaceControl {
	ax::NodeEditor::Config configNode;
	ax::NodeEditor::EditorContext* m_ContextNode = nullptr;
public:
	NodeGrapchic();
	~NodeGrapchic();
	bool show();
};

#endif // !__NODE_GRAPHIC
