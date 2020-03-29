using System.Collections.Generic;
using System.Linq;

namespace fireland15.LindenmayerSystem.Expressions.Model.Nodes
{
    public abstract class ExpressionNode
    {
        public abstract float Evaluate(IEvaluationContext context);

        public virtual IEnumerable<ExpressionNode> Descendants => Enumerable.Empty<ExpressionNode>();
    }
}
