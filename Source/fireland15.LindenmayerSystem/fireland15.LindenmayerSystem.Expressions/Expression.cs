using fireland15.LindenmayerSystem.Expressions.Model.Nodes;
using System;
using System.Linq;

namespace fireland15.LindenmayerSystem.Expressions.Model
{
    internal class Expression : IExpression
    {
        private readonly ExpressionNode rootNode;

        public IEvaluationContext EvaluationContext { get; }

        public Expression(ExpressionNode rootNode)
        {
            this.rootNode = rootNode;
            EvaluationContext = MakeEvaluationContext(rootNode);
        }
        
        public float Evaluate()
        {
            ValidateContext();
            return rootNode.Evaluate(EvaluationContext);
        }

        private void ValidateContext()
        {
            foreach (var variable in EvaluationContext.Variables)
            {
                if (!variable.IsAssigned)
                    throw new InvalidOperationException($"Variable value unassigned. Variable '{variable.Symbol}' was not assigned a value.");
            }
        }

        private IEvaluationContext MakeEvaluationContext(ExpressionNode rootNode) 
        {
            var variableMap = rootNode.Descendants
                .Append(rootNode)
                .OfType<VariableNode>()
                .Select(x => x.Symbol)
                .ToDictionary(
                    symbol => symbol,
                    symbol => new Variable(symbol));

            return new EvaluationContext(variableMap);
        }
    }
}
