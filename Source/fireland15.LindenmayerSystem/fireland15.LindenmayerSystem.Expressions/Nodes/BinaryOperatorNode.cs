using System;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions.Model.Nodes
{
    internal class BinaryOperatorNode : OperatorNode
    {
        #region Private Fields

        private readonly Func<float, float, float> operation;
        private readonly ExpressionNode[] children = new ExpressionNode[2];

        #endregion

        #region Constructor(s)

        public BinaryOperatorNode(Func<float, float, float> operation)
            : base(2)
        {
            this.operation = operation;
        }

        #endregion

        #region ExpressionNode

        public override float Evaluate(IEvaluationContext context)
        {
            return operation(children[0].Evaluate(context), children[1].Evaluate(context));
        }

        public override void SetChild(ExpressionNode child, int index = 0)
        {
            if (index >= 2)
                throw new ArgumentOutOfRangeException($"Cannot set child expression node at index '{index}'.", nameof(index));
            children[index] = child;
        }

        public override IEnumerable<ExpressionNode> Descendants
        {
            get
            {
                yield return children[0];
                foreach (var x in children[0].Descendants) yield return x;
                yield return children[1];
                foreach (var x in children[1].Descendants) yield return x;
            }
        }

        #endregion
    }
}
