using fireland15.LindenmayerSystem.Expressions.Exceptions;
using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using System;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions
{
    internal class InfixToPostfixConverter : IInfixToPostfixConverter
    {
        public IList<Token> Convert(IList<Token> infixTokens)
        {
            var postfixTokens = new List<Token>();

            if (infixTokens.Count == 0)
                return postfixTokens;

            var opstk = new Stack<Token>();

            for (int i = 0; i < infixTokens.Count; i++)
            {
                var token = infixTokens[i];
                switch (token.Type)
                {
                    case TokenType.Value:
                    case TokenType.Identifier:
                        postfixTokens.Add(token);
                        break;
                    case TokenType.Operator:
                        while (opstk.Count != 0 && TestOperatorPrecedence(token, opstk.Peek()))
                        {
                            postfixTokens.Add(opstk.Pop());
                        }
                        opstk.Push(token);
                        break;
                    case TokenType.LeftParenthesis:
                        opstk.Push(token);
                        break;
                    case TokenType.RightParenthesis:
                        if (opstk.Count == 0)
                            throw new ParseException("Unmatched parenthesis.");
                        while (opstk.Peek().Type != TokenType.LeftParenthesis)
                        {
                            postfixTokens.Add(opstk.Pop());
                            if (opstk.Count == 0)
                                throw new ParseException("Unmatched parenthesis.");
                        }
                        opstk.Pop();
                        break;
                    default:
                        throw new ArgumentOutOfRangeException($"Unexpected value '{token.Type}' for enum {nameof(TokenType)}");
                }
            }

            while (opstk.Count != 0)
            {
                var token = opstk.Pop();
                if (token.Type == TokenType.LeftParenthesis || token.Type == TokenType.RightParenthesis)
                    throw new ParseException("Unmatched parenthesis.");
                postfixTokens.Add(token);
            }

            return postfixTokens;
        }

        private bool TestOperatorPrecedence(Token t1, Token t2)
        {
            if (t2.Type == TokenType.LeftParenthesis)
                return false;

            var t1Details = operatorDetailsMap[t1.Operator.Value];
            var t2Details = operatorDetailsMap[t2.Operator.Value];

            if (t1Details.Associativity == OperatorAssociativity.Left && t1Details.Precedence <= t2Details.Precedence)
                return true;
            if (t1Details.Associativity == OperatorAssociativity.Right && t1Details.Precedence < t2Details.Precedence)
                return true;
            return false;
        }

        private struct OperatorDetails
        {
            public OperatorAssociativity Associativity;
            public int Precedence;
        }

        private static readonly Dictionary<Operator, OperatorDetails> operatorDetailsMap = new Dictionary<Operator, OperatorDetails>
        {
            {
                Operator.Add,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 1
                }
            },
            {
                Operator.Divide,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 2
                }
            },
            {
                Operator.Equals,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 0
                }
            },
            {
                Operator.GreaterThan,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 0
                }
            },
            {
                Operator.GreaterThanOrEqual,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 0
                }
            },
            {
                Operator.LessThan,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 0
                }
            },
            {
                Operator.LessThanOrEqual,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 0
                }
            },
            {
                Operator.Multiply,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 2
                }
            },
            {
                Operator.Negate,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Right,
                    Precedence = 3
                }
            },
            {
                Operator.NotEquals,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 0
                }
            },
            {
                Operator.Subtract,
                new OperatorDetails
                {
                    Associativity = OperatorAssociativity.Left,
                    Precedence = 1
                }
            }
        };
    }
}
