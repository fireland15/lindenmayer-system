using fireland15.LindenmayerSystem.Expressions.Model.Nodes;
using fireland15.LindenmayerSystem.Expressions.Model.Tokens;

namespace fireland15.LindenmayerSystem.Expressions.Nodes
{
    public interface IExpressionNodeFactory
    {
        ExpressionNode MakeNode(Token token);
    }
}
