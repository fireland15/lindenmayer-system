using fireland15.LindenmayerSystem.Expressions;
using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using fireland15.LindenmayerSystem.Expressions.Nodes;
using System.Collections.Generic;
using Xunit;

namespace fireland15.LindenmayerSystem.Test.Expressions.IntegrationTests
{
    public class EndToEndTests
    {
        [Theory]
        [InlineData("1.0", 1.0f)]
        [InlineData("1.0 + 2.0", 3.0f)]
        [InlineData("(1.0 + 2.0) * 5.0", 15.0f)]
        public void EvaluatesCorrectly(string expressionString, float expectedResult)
        {
            // arrange
            var expressionNodeFactory = new ExpressionNodeFactory();
            var expressionTokenizer = new ExpressionTokenizer();
            var infixToPostfixConverter = new InfixToPostfixConverter();
            var expressionFactory = new ExpressionFactory(expressionNodeFactory, expressionTokenizer, infixToPostfixConverter);

            // act
            var expression = expressionFactory.MakeExpression(expressionString);
            var result = expression.Evaluate();

            // assert
            Assert.Equal(expectedResult, result);
        }

        [Fact]
        public void EvaluatesCorrectlyWithAVariable()
        {
            // arrange
            var expressionNodeFactory = new ExpressionNodeFactory();
            var expressionTokenizer = new ExpressionTokenizer();
            var infixToPostfixConverter = new InfixToPostfixConverter();
            var expressionFactory = new ExpressionFactory(expressionNodeFactory, expressionTokenizer, infixToPostfixConverter);

            // act
            var expression = expressionFactory.MakeExpression("bananas");
            expression.EvaluationContext.GetVariable("bananas").Value = 4.0f;
            var result = expression.Evaluate();

            // assert
            Assert.Equal(4.0f, result);
        }

        [Fact]
        public void EvaluatesCorrectlyWithAVariableAndSomeStuff()
        {
            // arrange
            var expressionNodeFactory = new ExpressionNodeFactory();
            var expressionTokenizer = new ExpressionTokenizer();
            var infixToPostfixConverter = new InfixToPostfixConverter();
            var expressionFactory = new ExpressionFactory(expressionNodeFactory, expressionTokenizer, infixToPostfixConverter);

            // act
            var expression = expressionFactory.MakeExpression("(bananas + 1) / 5");
            expression.EvaluationContext.GetVariable("bananas").Value = 4.0f;
            var result = expression.Evaluate();

            // assert
            Assert.Equal(1.0f, result);
        }

        [Fact]
        public void ExpressionEvaluatorWorks()
        {
            // arrange
            var str = "(bananas) + 5 * (apples + carrots)";
            var variables = new Dictionary<string, float>
            {
                { "bananas", 1.0f },
                { "apples", 3.0f },
                { "carrots", 2.0f },
            };

            // act
            var result = ExpressionEvaluator.Evaluate(str, variables);

            // assert
            Assert.Equal(26.0f, result);
        }
    }
}
