namespace fireland15.LindenmayerSystem.Expressions.Model.Nodes
{
    internal class ValueNode : ExpressionNode
    {
        #region Private Fields

        private readonly float value;

        #endregion

        #region Constructor(s)

        public ValueNode(float value)
        {
            this.value = value;
        }

        #endregion

        #region ExpressionNode
        
        public override float Evaluate(IEvaluationContext context)
        {
            return value;
        }

        #endregion
    }
}
