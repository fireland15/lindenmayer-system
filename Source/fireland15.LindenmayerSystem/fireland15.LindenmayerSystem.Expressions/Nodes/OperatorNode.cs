namespace fireland15.LindenmayerSystem.Expressions.Model.Nodes
{
    internal abstract class OperatorNode : ExpressionNode
    {
        #region Properties

        public int ChildCount { get; }

        #endregion

        #region Constructor(s)

        protected OperatorNode(int childCount)
        {
            ChildCount = childCount;
        }

        #endregion

        public abstract void SetChild(ExpressionNode child, int index = 0);
    }
}
