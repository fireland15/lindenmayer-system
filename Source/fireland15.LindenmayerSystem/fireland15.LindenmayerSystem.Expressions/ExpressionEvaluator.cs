using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using fireland15.LindenmayerSystem.Expressions.Nodes;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions
{
    public static class ExpressionEvaluator
    {
        public static float Evaluate(string str, Dictionary<string, float> variables)
        {
            var expressionNodeFactory = new ExpressionNodeFactory();
            var expressionTokenizer = new ExpressionTokenizer();
            var infixToPostfixConverter = new InfixToPostfixConverter();
            var expressionFactory = new ExpressionFactory(expressionNodeFactory, expressionTokenizer, infixToPostfixConverter);
            var expression = expressionFactory.MakeExpression(str);

            foreach (var (symbol, value) in variables)
            {
                expression.EvaluationContext.GetVariable(symbol).Value = value;
            }

            return expression.Evaluate();
        }
    }
}
