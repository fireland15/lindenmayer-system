using fireland15.LindenmayerSystem.Expressions.Exceptions;
using System;

namespace fireland15.LindenmayerSystem.Expressions.Model.Nodes
{
    internal class VariableNode : ExpressionNode
    {
        #region Properties

        public string Symbol { get; }

        #endregion

        #region Constructor(s)

        public VariableNode(string symbol)
        {
            Symbol = symbol;
        }

        #endregion
        
        #region ExpressionNode
        
        public override float Evaluate(IEvaluationContext context)
        {
            var variable = context.GetVariable(Symbol);
            if (!variable.IsAssigned)
                throw new InvalidOperationException($"Expected variable '{Symbol}' to be set.");
            return variable.Value.Value;
        }

        #endregion
    }
}
