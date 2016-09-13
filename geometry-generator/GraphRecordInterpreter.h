#pragma once

#include "BaseRecordInterpreter.h"
#include "Graph.h"

template <typename TEdgeAttribute, typename TNodeAttribute>
class GraphRecordInterpreter : public BaseRecordInterpreter<Graph<TEdgeAttribute, TNodeAttribute>> {
public:
	virtual void Interpret(Graph<TEdgeAttribute, TNodeAttribute> container) {

	}
};