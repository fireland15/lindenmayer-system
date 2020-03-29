using fireland15.LindenmayerSystem.Expressions;
using fireland15.LindenmayerSystem.Expressions.Model;
using fireland15.LindenmayerSystem.Expressions.Model.Nodes;
using Moq;
using System.Collections.Generic;
using Xunit;

namespace fireland15.LindenmayerSystem.Test.Expressions
{
    public class ExpressionTests
    {
        [Fact]
        public void EvaluatesRootNode()
        {
            // arrange
            var rootNode = new Mock<ExpressionNode>();
            rootNode
                .Setup(x => x.Evaluate(It.IsAny<IEvaluationContext>()))
                .Returns(10.0f);
            var expression = new Expression(rootNode.Object);

            // act
            var result = expression.Evaluate();

            // assert
            Assert.Equal(10.0f, result);
        }

        [Fact]
        public void ExecutionContextContainsVariables()
        {
            // arrange
            var rootNode = new Mock<ExpressionNode>();
            rootNode
                .SetupGet(x => x.Descendants)
                .Returns(new List<ExpressionNode>
                {
                    new VariableNode("bananas")
                });
            var expression = new Expression(rootNode.Object);

            // act
            var context = expression.EvaluationContext;

            // assert
            Assert.NotNull(context);
            Assert.Single(context.Variables);
            Assert.NotNull(context.GetVariable("bananas"));
        }
    }
}
