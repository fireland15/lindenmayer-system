using fireland15.LindenmayerSystem.Expressions.Model.Nodes;
using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using System;

namespace fireland15.LindenmayerSystem.Expressions.Nodes
{
    internal class ExpressionNodeFactory : IExpressionNodeFactory
    {
        public ExpressionNode MakeNode(Token token)
        {
            switch (token.Type)
            {
                case TokenType.Operator:
                    {
                        switch (token.Operator)
                        {
                            case Operator.Add:
                                return new BinaryOperatorNode((a, b) => a + b);
                            case Operator.Divide:
                                return new BinaryOperatorNode((a, b) => a / b);
                            case Operator.Equals:
                                return new BinaryOperatorNode((a, b) => a == b ? 1.0f : 0.0f);
                            case Operator.GreaterThan:
                                return new BinaryOperatorNode((a, b) => a > b ? 1.0f : 0.0f);
                            case Operator.GreaterThanOrEqual:
                                return new BinaryOperatorNode((a, b) => a >= b ? 1.0f : 0.0f);
                            case Operator.LessThan:
                                return new BinaryOperatorNode((a, b) => a < b ? 1.0f : 0.0f);
                            case Operator.LessThanOrEqual:
                                return new BinaryOperatorNode((a, b) => a <= b ? 1.0f : 0.0f);
                            case Operator.Multiply:
                                return new BinaryOperatorNode((a, b) => a * b);
                            case Operator.Negate:
                                return new UnaryOperatorNode(a => -a);
                            case Operator.NotEquals:
                                return new BinaryOperatorNode((a, b) => a != b ? 1.0f : 0.0f);
                            case Operator.Subtract:
                                return new BinaryOperatorNode((a, b) => a - b);
                            default:
                                throw new ArgumentOutOfRangeException($"Invalid value '{token.Operator}' for enum {nameof(Operator)}");
                        }
                    }
                case TokenType.Value:
                    return new ValueNode(token.Value.Value);
                case TokenType.Identifier:
                    return new VariableNode(token.Symbol);
                default:
                    throw new ArgumentOutOfRangeException($"Invalid value '{token.Type}' for enum {nameof(TokenType)}");
            }
        }
    }
}
