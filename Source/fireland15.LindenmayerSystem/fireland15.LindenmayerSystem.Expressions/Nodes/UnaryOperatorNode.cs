using System;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions.Model.Nodes
{
    internal class UnaryOperatorNode : OperatorNode
    {
        #region Private Fields

        private readonly Func<float, float> operation;
        private ExpressionNode child;

        #endregion

        #region Constructor(s)

        public UnaryOperatorNode(Func<float, float> operation)
            : base(1)
        {
            this.operation = operation;
        }

        #endregion

        #region ExpressionNode
        
        public override IEnumerable<ExpressionNode> Descendants
        {
            get
            {
                yield return child;
                foreach (var x in child.Descendants) yield return x;
            }
        }

        public override float Evaluate(IEvaluationContext context)
        {
            return operation(child.Evaluate(context));
        }

        public override void SetChild(ExpressionNode child, int index = 0)
        {
            this.child = child;
        }

        #endregion
    }
}
