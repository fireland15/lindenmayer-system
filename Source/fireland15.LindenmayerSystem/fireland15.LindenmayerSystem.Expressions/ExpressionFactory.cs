using fireland15.LindenmayerSystem.Expressions.Model;
using fireland15.LindenmayerSystem.Expressions.Model.Nodes;
using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using fireland15.LindenmayerSystem.Expressions.Nodes;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions
{
    internal class ExpressionFactory : IExpressionFactory
    {
        private readonly IExpressionNodeFactory expressionNodeFactory;
        private readonly IExpressionTokenizer expressionTokenizer;
        private readonly IInfixToPostfixConverter infixToPostfixConverter;

        public ExpressionFactory(
            IExpressionNodeFactory expressionNodeFactory, 
            IExpressionTokenizer expressionTokenizer, 
            IInfixToPostfixConverter infixToPostfixConverter)
        {
            this.expressionNodeFactory = expressionNodeFactory;
            this.expressionTokenizer = expressionTokenizer;
            this.infixToPostfixConverter = infixToPostfixConverter;
        }

        public IExpression MakeExpression(string expressionString)
        {
            var infixTokens = expressionTokenizer.Tokenize(expressionString);
            if (infixTokens.Count == 0)
                return null;

            var postfixTokens = infixToPostfixConverter.Convert(infixTokens);

            var nodeStack = new Stack<ExpressionNode>();
            nodeStack.Push(expressionNodeFactory.MakeNode(postfixTokens[0]));

            for (int i = 1; i < postfixTokens.Count; i++)
            {
                var node = expressionNodeFactory.MakeNode(postfixTokens[i]);
                if (node is OperatorNode operatorNode)
                {
                    for (int j = operatorNode.ChildCount - 1; j >= 0; j--)
                    {
                        operatorNode.SetChild(nodeStack.Pop(), j);
                    }
                }
                nodeStack.Push(node);
            }

            return new Expression(nodeStack.Pop());
        }
    }
}
